#include <LLVMParser.h>

#include <ElementToMockContext.h>
#include <StructType.h>
#include <UnionType.h>
#include <FunctionDeclaration.h>
#include <FunctionType.h>
#include <TypeItf.h>
#include <EasyMock_CType.h>
#include <Pointer.h>
#include <Enum.h>
#include <IncompleteType.h>
#include <ComposableField.h>
#include <ComposableBitfield.h>
#include <ConstQualifiedType.h>
#include <TypedefType.h>

#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendActions.h>
#include <clang/Tooling/CompilationDatabase.h>
#include <clang/Tooling/Tooling.h>

#include <boost/algorithm/string.hpp>

#include <string>
#include <vector>
#include <unordered_map>
#include <regex>

namespace
{
std::string trim(const std::string &s) {
  static std::regex removeSpaceRegex{"^[[:space:]]*|[[:space:]]*$"};
  return std::regex_replace(s, removeSpaceRegex, "");
}
}

/*!
 * \brief An implementation of a LLVM clang::RecursiveASTVisitor<FunctionDeclASTVisitor>
 */
class FunctionDeclASTVisitor : public clang::RecursiveASTVisitor<FunctionDeclASTVisitor>
{
private:
  typedef std::unordered_map<std::string, const IncompleteType> structKnownTypeMap;
public:

  explicit FunctionDeclASTVisitor(clang::SourceManager& sm, ElementToMockContext& ctxt)
  : m_sourceManager(sm), m_ctxt(ctxt), m_context(nullptr)
  {
    (void)m_sourceManager;
  }

  /*!
   * \brief Parses a single function.
   *
   * This function adds a new ElementToMock object to the list of ElementVector
   * which is returned by the parser.
   */
  bool VisitFunctionDecl(clang::FunctionDecl* func)
  {
    FunctionDeclaration* f = getFunctionDeclaration(func);
    m_ctxt.addElementToMock(f);

    return true;
  }

  FunctionDeclaration* getFunctionDeclaration(const clang::FunctionDecl* func)
  {
    const std::string funName = getFunctionName(func);
    bool isInline = func->isInlined();

    ReturnValue rv = getFunctionReturnValue(func);
    Parameter::Vector param = getFunctionParameters(func);
    FunctionDeclaration *f = new FunctionDeclaration(funName, rv, param);
    f->setVariadic(func->isVariadic());
    f->setInlined(isInline);
    setFunctionAttribute(func, f);

    return f;
  }

  void setAstContext(const clang::ASTContext &ctx)
  {
    m_context = &ctx;
    m_SM = &ctx.getSourceManager();
    m_LO = &ctx.getLangOpts();
  }
private:
  clang::SourceManager& m_sourceManager;
  ElementToMockContext& m_ctxt;
  const clang::ASTContext *m_context;
  const clang::SourceManager *m_SM;
  const clang::LangOptions *m_LO;

  enum ContainerType {
    STRUCT,
    UNION
  };

  void setFunctionAttribute(const clang::FunctionDecl* clangFunc, FunctionDeclaration* easyMockFun)
  {
    for(const auto& attr : clangFunc->attrs())
    {
      const clang::IdentifierInfo* identifierInfo = attr->getAttrName();
      if(!identifierInfo)
      {
        fprintf(stderr, "Warning: couldn't get the identifier info for an attribute.\n"
                        "         The mock will be missing a function attribute.");
        attr->getRange().dump(*m_SM);
        continue;
      }
      std::string attrName = identifierInfo->getName().str();
      FunctionAttribute::ParametersList parametersList = getFunAttrParamList(clangFunc, attr);
      FunctionAttribute functionAttribute{std::move(attrName), std::move(parametersList)};

      easyMockFun->addAttribute(std::move(functionAttribute));
    }
  }

  FunctionAttribute::ParametersList getFormatAttrParamList(const clang::FormatAttr *formatAttr)
  {
    FunctionAttribute::ParametersList parametersList{};
    parametersList.emplace_back(formatAttr->getType()->getName().str());
    parametersList.emplace_back(std::to_string(formatAttr->getFormatIdx()));
    parametersList.emplace_back(std::to_string(formatAttr->getFirstArg()));
    return parametersList;
  }

  FunctionAttribute::ParametersList getSectionAttrParamList(const clang::SectionAttr *sectionAttr)
  {
    FunctionAttribute::ParametersList parametersList{};
    parametersList.emplace_back(sectionAttr->getName().str());
    return parametersList;
  }

  FunctionAttribute::ParametersList getFunAttrParamList(const clang::FunctionDecl* clangFunc, const clang::Attr *attr)
  {
    FunctionAttribute::ParametersList parametersList{};
    /*
     * Clang defines a specific class for each possible function attribute.
     * Currently, only the following are supported:
     * - format
     * - section
     *
     * The fallback case attempt to parse the string to determine the attribute name
     * and its parameter. If something more precise is needed, a new else case must be added
     * to the code.
     * This fallback case works for the majority of the case we have seen so far.
     */
    const clang::FormatAttr *formatAttr = attr->getKind() == clang::attr::Kind::Format ? clangFunc->getAttr<clang::FormatAttr>() : nullptr;
    const clang::SectionAttr *sectionAttr = attr->getKind() == clang::attr::Kind::Section ? clangFunc->getAttr<clang::SectionAttr>() : nullptr;
    if(formatAttr)
    {
      parametersList = getFormatAttrParamList(formatAttr);
    }
    else if(sectionAttr)
    {
      parametersList = getSectionAttrParamList(sectionAttr);
    }
    else
    {
      clang::SourceRange sourceRange = attr->getRange();
      clang::SourceLocation sourceBegin = sourceRange.getBegin();
      clang::SourceLocation sourceEnd = sourceRange.getEnd();
      if(sourceBegin.isMacroID())
      {
        sourceBegin = m_SM->getSpellingLoc(sourceBegin);
      }
      if(sourceEnd.isMacroID())
      {
        sourceEnd = m_SM->getSpellingLoc(sourceEnd);
      }
      clang::CharSourceRange charSourceRange{};
      charSourceRange.setBegin(sourceBegin);
      charSourceRange.setEnd(sourceEnd);
      clang::StringRef attributeStringRef = clang::Lexer::getSourceText(charSourceRange, *m_SM, *m_LO);
      std::string attributeString = attributeStringRef.str();
      size_t curPos = attributeString.find_first_of('(');
      while(curPos != std::string::npos)
      {
        curPos += 1;
        size_t commaPos = attributeString.find_first_of(',', curPos);
        if(commaPos != std::string::npos)
        {
          size_t paramLen = commaPos - curPos;
          std::string curParam = attributeString.substr(curPos,paramLen);
          curPos += paramLen; //Put the position on the comma
          curParam = trim(curParam);
          parametersList.push_back(curParam);
        }
        else
        {
          std::string curParam = attributeString.substr(curPos);
          curParam = trim(curParam);
          parametersList.push_back(curParam);
          curPos = std::string::npos;
        }
      }
    }
    return parametersList;
  }

  ReturnValue getFunctionReturnValue(const clang::FunctionDecl* func)
  {
    const std::string funName = getFunctionName(func);
    const clang::QualType &rvQualType = func->getReturnType();
    structKnownTypeMap structKnownType;

    TypeItf *type = getEasyMocktype(rvQualType, structKnownType, false);
    ReturnValue rv(type);

    clang::SourceLocation beginSourceLocation = func->getBeginLoc();
    std::string declString = getDeclareString(beginSourceLocation, func->getEndLoc(), false);
    size_t funNamePos = declString.find(funName);
    if(funNamePos != std::string::npos)
    {
      declString.erase(declString.begin() + funNamePos, declString.end());
    }
    while(!declString.empty() && declString.back() == ' ')
    {
      declString.pop_back();
    }
    /*
     * Loop through all the function attributes and determine whether they are declared using a macro.
     * If they are declared using a macro, just remove the macro call from the declString.
     */
    for(const auto& attr : func->attrs())
    {
      clang::SourceLocation sourceBegin = attr->getLocation();
      if(sourceBegin.isMacroID())
      {
        clang::CharSourceRange charSourceRange = m_SM->getImmediateExpansionRange(sourceBegin);
        clang::StringRef attributeStringRef = clang::Lexer::getSourceText(charSourceRange, *m_SM, *m_LO);
        std::string macroStr = attributeStringRef.str();
        /*
         * If the immediateExpansionRange is empty, try to get it after getting the immediateMacroCallerLoc.
         *
         * The assumption is that whenever a macro is defining 2 function attributes e.g.
         * #define __section(S) __attribute__ ((section(#S)))
         * #define __cold       __attribute__((cold))
         * #define __multiAttr  __section(.multiAttr.text) __cold
         *
         * Then it is needed to go on the immediateMacroCallerLoc.
         *
         * This isn't working in all the cases though. Not sure why...
         */
        if(macroStr.empty())
        {
          sourceBegin = m_SM->getImmediateMacroCallerLoc(sourceBegin);
          charSourceRange = m_SM->getImmediateExpansionRange(sourceBegin);
          attributeStringRef = clang::Lexer::getSourceText(charSourceRange, *m_SM, *m_LO);
          macroStr = attributeStringRef.str();
        }
        /*
         * It is needed to escape "(" and ")" in case there are some so that they are not taken as group inside the
         * std::regex
         */
        static std::regex leftParentRegex{"\\("};
        static std::regex rightParentRegex{"\\)"};
        macroStr = std::regex_replace(macroStr, leftParentRegex, "\\(");
        macroStr = std::regex_replace(macroStr, rightParentRegex, "\\)");
        declString = std::regex_replace(declString, std::regex{macroStr}, "");
      }
    }
    static std::regex removeAttrRegex{"__attribute__[[:space:]]*\\([[:space:]]*\\(.*\\)[[:space:]]*\\)"};
    declString = std::regex_replace(declString, removeAttrRegex, "");
    eraseInString(declString, "inline ");
    eraseInString(declString, "extern ");
    declString = trim(declString);
    setDeclaratorDeclareString(rvQualType, &rv, declString);
    type = nullptr; //We lost the ownership

    return rv;
  }

  Parameter::Vector getFunctionParameters(const clang::FunctionDecl* func)
  {
    Parameter::Vector vectParam;
    unsigned nbParam = func->getNumParams();
    std::string funcDecl = getDeclareString(func->getBeginLoc(), func->getEndLoc(), false);

    for(unsigned paramIdx = 0; paramIdx < nbParam; paramIdx++)
    {
      const clang::ParmVarDecl *param = func->getParamDecl(paramIdx);
      const clang::QualType paramQualType = param->getType();

      structKnownTypeMap structKnownType;
      const std::string paramName = param->getNameAsString();
      TypeItf *type = getEasyMocktype(paramQualType, structKnownType, false);

      Parameter *p = new Parameter(type, paramName);
      type = nullptr; //We lost the ownership
      clang::SourceLocation beginLoc = param->getBeginLoc();
      std::string declareString = getDeclareString(std::move(beginLoc), param->getEndLoc(), false);
      setDeclaratorDeclareString(paramQualType, p, declareString);
      vectParam.push_back(p);
      p = nullptr; //We lost the ownership
    }

    return vectParam;
  }

  std::string getDeclareString(const clang::SourceLocation& startLoc, const clang::SourceLocation& endLoc, bool fieldDecl)
  {
    clang::CharSourceRange sourceRange = clang::Lexer::getAsCharRange(startLoc, *m_SM, *m_LO);
    /*
     * Get the end location with an offset of 1 because otherwise the * might be missed in case
     * that the parameter doesn't have any name.
     *
     * See VoidFunUnnamedPtrParam test for reproduction scenario.
     */
    sourceRange.setEnd(endLoc.getLocWithOffset(1));
    clang::StringRef strRef = clang::Lexer::getSourceText(sourceRange, *m_SM, *m_LO);
    std::string declareString = strRef.str();
    /*
     * When a declaration is inlined, we ignore the whole declaration in this way
     */
    size_t bracketPos = declareString.find_first_of('{', 0);
    if(bracketPos != std::string::npos)
    {
      declareString.erase(declareString.begin() + bracketPos, declareString.end());
    }
    else
    {
      if(fieldDecl)
      {
        auto trimToFirstInstanceOf = [&declareString](char charToTest)
        {
          size_t commaPos = declareString.find_first_of(charToTest, 0);
          if (commaPos != std::string::npos)
          {
            declareString.erase(declareString.begin() + commaPos, declareString.end());
            declareString = trim(declareString);
          }
        };
        trimToFirstInstanceOf(',');
        trimToFirstInstanceOf('[');
      }
      while(!declareString.empty() &&
              declareString.back() != ' ' &&
              declareString.back() != '\n' &&
              declareString.back() != '\r' &&
              declareString.back() != '\t' &&
              declareString.back() != '*' &&
              declareString.back() != ')')
      {
        declareString.pop_back();
      }
    }
    declareString = trim(declareString);

    return declareString;
  }

  TypeItf* getEasyMocktype(const clang::QualType &clangQualType, structKnownTypeMap &structKnownType, bool isEmbeddedInOtherType)
  {
    const clang::Type &clangType = *clangQualType.getTypePtr();
    const std::string& nakedDeclString = clangQualType.getCanonicalType().getAsString();
    TypeItf *type = nullptr;
    if(clangType.isBuiltinType())
    {
      type = getFromBuiltinType(clangType, nakedDeclString);
    }
    else if(clangType.isStructureType())
    {
      type = getFromStructType(clangType, structKnownType, isEmbeddedInOtherType);
    }
    else if(clangType.isPointerType())
    {
      type = getFromPointerType(clangType, structKnownType, isEmbeddedInOtherType);
    }
    else if (clangType.isArrayType())
    {
      type = getFromArrayType(clangType, structKnownType, isEmbeddedInOtherType);
    }
    else if (clangType.isUnionType())
    {
      type = getFromUnionType(clangType, structKnownType, isEmbeddedInOtherType);
    }
    else if (clangType.isFunctionProtoType())
    {
      type = getFromFunctionPrototype(clangType, structKnownType);
    }
    else if (clangType.isEnumeralType())
    {
      type = getFromEnumType(clangType, structKnownType);
    }
    else
    {
      std::fprintf(stderr, "Clang type unexpected here. Contact the owner for bug fixing\n\r");
      clangType.dump();
      assert(false);
    }
    if(clangQualType.isLocalConstQualified())
    {
      type = new ConstQualifiedType(type);
    }

    clang::RecordDecl *recDecl = clangType.getAsRecordDecl();
    if(recDecl)
    {
      type->setImplicit(recDecl->isImplicit());
    }

    return type;
  }

  TypeItf* getFromBuiltinType(const clang::Type &type, const std::string& nakedDeclString)
  {
    CType *cType = nullptr;

    if(type.isVoidType())
    {
      cType = new CType(CTYPE_VOID);
    }
    else if(type.isCharType())
    {
#if IS_CHAR_DEFAULT_UNSIGNED
      if(type.isUnsignedIntegerType() && nakedDeclString.compare("unsigned char") == 0)
      {
        cType = new CType(CTYPE_UCHAR);
      }
      else
#endif
      {
        cType = new CType(CTYPE_CHAR);
      }
    }
    else if(isShortType(type))
    {
      cType = new CType(CTYPE_SHORT);
    }
    else if(isLongType(type))
    {
      cType = new CType(CTYPE_LONG);
    }
    else if(isIntType(type))
    {
      cType = new CType(CTYPE_INT);
    }
    else if(isLongLongType(type))
    {
      cType = new CType(CTYPE_LONG_LONG);
    }
    else if(isDoubleType(type))
    {
      cType = new CType(CTYPE_DOUBLE);
    }
    else if(isLongDoubleType(type))
    {
      cType = new CType(CTYPE_LONG_DOUBLE);
    }
    else if(isFloatType(type))
    {
      cType = new CType(CTYPE_FLOAT);
    }
    else if(isBoolType(type))
    {
      cType = new CType(CTYPE_INT);
    }
    else if(isInt128Type(type))
    {
      cType = new CType(CTYPE_INT128);
    }
    else
    {
      std::fprintf(stderr, "Clang type unexpected here for CTYPE. Contact the owner for bug fixing\n\r");
      type.dump();
      assert(false);
    }

    //Unsigned
    if(type.isUnsignedIntegerType())
    {
      cType->setUnsigned(true);
    }
    const std::string typedefName = getTypedefName(type);
    TypeItf* returnedType = cType;
    if(!typedefName.empty())
    {
      returnedType = new TypedefType(typedefName, returnedType);
    }

    return returnedType;
  }

  TypeItf* getFromStructType(const clang::Type &type, structKnownTypeMap &structKnownType, bool isEmbeddedInOtherType)
  {
    return getFromContainerType(type, STRUCT, structKnownType, isEmbeddedInOtherType);
  }

  TypeItf* getFromUnionType(const clang::Type &type, structKnownTypeMap &structKnownType, bool isEmbeddedInOtherType)
  {
    return getFromContainerType(type, UNION, structKnownType, isEmbeddedInOtherType);
  }

  /*
   * This function awfully looks alike with the getFunctionDeclaration
   * and getFunctionParameters(). However the objects used are a little
   * different as well as the API. Therefore we need to re-implement the same
   * kind of logic.
   */
  TypeItf* getFromFunctionPrototype(const clang::Type &type, structKnownTypeMap &structKnownType)
  {
    const clang::FunctionProtoType *fp = type.getAs<clang::FunctionProtoType>();

    const clang::QualType &rvQualType = fp->getReturnType();

    TypeItf *rvType = getEasyMocktype(rvQualType, structKnownType, false);
    ReturnValue rv(rvType);
    rvType = nullptr; //We lost the ownership

    unsigned nbParams = fp->getNumParams();
    Parameter::Vector vectParam;
    for(unsigned paramIdx = 0; paramIdx < nbParams; paramIdx++)
    {
      const clang::QualType& paramQualType = fp->getParamType(paramIdx);
      TypeItf *paramType = getEasyMocktype(paramQualType, structKnownType, false);

      Parameter *p = new Parameter(paramType, "");
      paramType = nullptr; //We lost the ownership
      vectParam.push_back(p);
      p = nullptr; //We lost the ownership
    }
    FunctionType *f = new FunctionType(rv, vectParam);

    return f;
  }

  TypeItf* getFromEnumType(const clang::Type &type, structKnownTypeMap &structKnownType)
  {
    const clang::EnumType *ET = type.getAs<clang::EnumType>();
    const clang::EnumDecl *ED = ET->getDecl();

    const std::string name = ED->getNameAsString();

    Enum* enumType = new Enum(name);
    for(const auto enumConstantDeclaration : ED->enumerators())
    {
      int64_t enumValue = enumConstantDeclaration->getInitVal().getExtValue();
      const std::string enumName = enumConstantDeclaration->getNameAsString();
      enumType->addEnumValue(enumValue, enumName);
    }
    const std::string typedefName = getTypedefName(type);
    TypeItf *toReturn = enumType;
    if(!typedefName.empty())
    {
      toReturn = new TypedefType(typedefName, toReturn);
    }
    return toReturn;
  }

  TypeItf* getFromContainerType(const clang::Type &p_type, ContainerType contType, structKnownTypeMap &structKnownType, bool p_isEmbeddedInOtherType)
  {
    const clang::RecordType *RT = nullptr;
    switch(contType)
    {
      case STRUCT:
        RT = p_type.getAsStructureType();
        break;
      case UNION:
        RT = p_type.getAsUnionType();
        break;
    }

    clang::RecordDecl* RD = RT->getDecl();
    std::string typeName = RD->getNameAsString();
    std::string typedDefName = getTypedefName(p_type);

    if(structKnownType.find(typedDefName) != structKnownType.end())
    {
      return structKnownType.at(typedDefName).clone();
    }
    if(structKnownType.find(typeName) != structKnownType.end())
    {
      return structKnownType.at(typeName).clone();
    }

    const clang::TypedefType* TDT = p_type.getAs<clang::TypedefType>();
    clang::TypedefNameDecl* TD_RD = nullptr;
    if(TDT != nullptr)
    {
      TD_RD = TDT->getDecl();
    }
    bool isBeingDefined = false;
    if(TD_RD != nullptr)
    {
      //isTopLevelDeclInObjCContainer seems to be equivalent to isEmbeddedInDeclarator for typedef
      isBeingDefined = TD_RD->isTopLevelDeclInObjCContainer();
    }
    else
    {
      isBeingDefined = RD->isEmbeddedInDeclarator();
    }
    bool isEmbeddedInOtherType = p_isEmbeddedInOtherType && isBeingDefined;

    ComposableType *sType = nullptr;
    IncompleteType::Type incType = IncompleteType::Type::STRUCT;
    switch(contType)
    {
      case STRUCT:
        sType = new StructType(typeName, isEmbeddedInOtherType);
        incType = IncompleteType::Type::STRUCT;
        break;
      case UNION:
        sType = new UnionType(typeName, isEmbeddedInOtherType);
        incType = IncompleteType::Type::UNION;
    }
    if(!typedDefName.empty())
    {
      structKnownType.insert({typedDefName,IncompleteType(*sType, incType)});
    }
    if(!typeName.empty())
    {
      structKnownType.insert({typeName, IncompleteType(*sType, incType)});
    }
    for (clang::FieldDecl *FD :
          RD->fields()) {
      const clang::QualType &qualType = FD->getType();
      const clang::Type *typePtr = qualType.getTypePtr();
      std::string fName = FD->getNameAsString();
      TypeItf *fieldType = getEasyMocktype(qualType, structKnownType, true);

      ComposableFieldItf *sf = nullptr;
      if(FD->isBitField())
      {
        TypedefType *typedefFieldType = fieldType->asTypedefType();
        if(!fieldType->isCType() && (typedefFieldType && !typedefFieldType->getMostDefinedTypee()->isCType()))
        {
          fprintf(stderr, "Type must be CType for bitfields");
          typePtr->dump();
          assert(false);
        }
        unsigned bitWidth = FD->getBitWidthValue(*m_context);
        assert(bitWidth < 256);
        if(typedefFieldType)
        {
          sf = new ComposableBitfield(typedefFieldType, fName, static_cast<uint8_t>(bitWidth));
        }
        else
        {
          CType* cTypePtr = fieldType->asCType();
          assert(cTypePtr);
          sf = new ComposableBitfield(cTypePtr, fName, static_cast<uint8_t>(bitWidth));
        }
      }
      else
      {
        int64_t arraySize = getArraySize(*typePtr);
        if(!typePtr->isArrayType())
        {
            arraySize = -1;
        }
        sf = new ComposableField(fieldType, fName, { .arraySize = arraySize });
        setDeclaratorDeclareString(qualType, sf, getDeclareString(FD->getBeginLoc(), FD->getEndLoc(), true));
      }
      sType->addField(sf);
    }
    TypeItf* toReturn = sType;
    if(!typedDefName.empty())
    {
      toReturn = new TypedefType(typedDefName, toReturn);
      structKnownType.erase(typedDefName);
    }
    if(!typeName.empty())
    {
      structKnownType.erase(typeName);
    }

    return toReturn;
  }

  TypeItf* getFromPointerType(const clang::Type &type, structKnownTypeMap &structKnownType, bool isEmbeddedInOtherType)
  {
    const clang::QualType &pointeeQualType = type.getPointeeType();
    TypeItf *rv = getEasyMocktype(pointeeQualType, structKnownType, isEmbeddedInOtherType);

    TypeItf *returnedTyped = new Pointer(rv);
    std::string typedDefName = getTypedefName(type);
    if(!typedDefName.empty())
    {
      returnedTyped = new TypedefType(typedDefName, returnedTyped);
    }

    return returnedTyped;
  }

  TypeItf* getFromArrayType(const clang::Type &type, structKnownTypeMap &structKnownType, bool isEmbeddedInOtherType)
  {
    const clang::ArrayType &arrayType = *type.getAsArrayTypeUnsafe();
    const clang::QualType &arrayElemQualType = arrayType.getElementType();

    TypeItf *rv = getEasyMocktype(arrayElemQualType, structKnownType, isEmbeddedInOtherType);

    return rv;
  }

  bool isShortType(const clang::Type &type)
  {
    const clang::BuiltinType *bt = type.getAs<clang::BuiltinType>();

    clang::BuiltinType::Kind kind = bt->getKind();
    return kind == clang::BuiltinType::Short ||
            kind == clang::BuiltinType::UShort;
  }

  bool isDoubleType(const clang::Type &type)
  {
    const clang::BuiltinType *bt = type.getAs<clang::BuiltinType>();

    clang::BuiltinType::Kind kind = bt->getKind();
    return kind == clang::BuiltinType::Double;
  }

  bool isLongType(const clang::Type &type)
  {
    const clang::BuiltinType *bt = type.getAs<clang::BuiltinType>();

    clang::BuiltinType::Kind kind = bt->getKind();
    return kind == clang::BuiltinType::Long ||
            kind == clang::BuiltinType::ULong;
  }

  bool isIntType(const clang::Type &type)
  {
    const clang::BuiltinType *bt = type.getAs<clang::BuiltinType>();

    clang::BuiltinType::Kind kind = bt->getKind();
    return kind == clang::BuiltinType::Int ||
            kind == clang::BuiltinType::UInt;
  }

  bool isFloatType(const clang::Type &type)
  {
    const clang::BuiltinType *bt = type.getAs<clang::BuiltinType>();

    clang::BuiltinType::Kind kind = bt->getKind();
    return kind == clang::BuiltinType::Float;
  }

  bool isLongLongType(const clang::Type &type)
  {
    const clang::BuiltinType *bt = type.getAs<clang::BuiltinType>();

    clang::BuiltinType::Kind kind = bt->getKind();
    return kind == clang::BuiltinType::LongLong ||
            kind == clang::BuiltinType::ULongLong;
  }

  bool isLongDoubleType(const clang::Type &type)
  {
    const clang::BuiltinType *bt = type.getAs<clang::BuiltinType>();

    clang::BuiltinType::Kind kind = bt->getKind();
    return kind == clang::BuiltinType::LongDouble;
  }

  bool isFunctionType(const clang::QualType &clangQualType)
  {
    const clang::Type &type = *clangQualType.getTypePtr();
    if (type.isPointerType())
    {
      const clang::QualType &pointeeType = type.getPointeeType();
      return isFunctionType(pointeeType);
    }
    return type.isFunctionProtoType();
  }

  bool isBoolType(const clang::Type &type)
  {
    const clang::BuiltinType *bt = type.getAs<clang::BuiltinType>();

    clang::BuiltinType::Kind kind = bt->getKind();
    return kind == clang::BuiltinType::Bool;
  }

  bool isInt128Type(const clang::Type &type)
  {
    const clang::BuiltinType *bt = type.getAs<clang::BuiltinType>();

    clang::BuiltinType::Kind kind = bt->getKind();
    return kind == clang::BuiltinType::UInt128 ||
            kind == clang::BuiltinType::Int128;
  }

  uint64_t getArraySize(const clang::Type &type)
  {
    const clang::ConstantArrayType *constArrType = m_context->getAsConstantArrayType(type.getCanonicalTypeInternal());
    int64_t size = 0;
    if(constArrType)
    {
      llvm::APInt sizeMod = constArrType->getSize();
      size = sizeMod.getSExtValue();
    }
    return size;
  }

  void setDeclaratorDeclareString(const clang::QualType &clangQualType, Declarator* decl, const std::string &newString)
  {
    bool isFuncType = isFunctionType(clangQualType);
    if(!isFuncType || (isFuncType && decl->getType()->isTypedDef()))
    {
      decl->setDeclareString(newString);
    }
  }

  std::string getFunctionName(const clang::FunctionDecl *func)
  {
    return func->getNameInfo().getName().getAsString();
  }

  void eraseInString(std::string &string,const std::string& toErase)
  {
    size_t pos = string.find(toErase);
    if(pos != std::string::npos)
    {
        string.erase(pos, toErase.length());
    }
  }

  std::string getTypedefName(const clang::Type &type)
  {
    const clang::TypedefType* TDT = type.getAs<clang::TypedefType>();
    clang::TypedefNameDecl* TD_RD = nullptr;
    std::string typedDefName("");
    if(TDT != nullptr)
    {
      TD_RD = TDT->getDecl();
      typedDefName = TD_RD->getNameAsString();
    }
    return typedDefName;
  }
};

class FunctionDeclASTConsumer : public clang::ASTConsumer
{
public:
  // override the constructor in order to pass CI

  explicit FunctionDeclASTConsumer(clang::CompilerInstance& ci, ElementToMockContext& ctxt)
  : clang::ASTConsumer(), m_visitor(ci.getSourceManager(), ctxt) { }

  virtual void HandleTranslationUnit(clang::ASTContext& astContext) override
  {
    m_visitor.setAstContext(astContext);
    m_visitor.TraverseDecl(astContext.getTranslationUnitDecl());
  }
private:
  FunctionDeclASTVisitor m_visitor; // doesn't have to be private
};

/*!
 * \brief Implements the logic to add the macro to the ::ElementToMockContext
 * when parsing the header file.
 *
 * This function overrides MacroDefined and MacroUndefined. Those function are called
 * by the LLVM library when a macro is defined and undefined.
 */
class MacroBrowser : public clang::PPCallbacks
{
public:
  MacroBrowser(ElementToMockContext& p_ctxt, clang::SourceManager& p_sm) : m_ctxt(p_ctxt), m_sm(p_sm)
  {
    (void)m_sm;
  }

  void MacroDefined (const clang::Token &p_macroIdentifierTok, const clang::MacroDirective *p_macroDirective) override
  {
    std::string id;
    MacroDefinition::ParameterList parameters{};
    std::string definition("");
    id = getTokenString(p_macroIdentifierTok);
    if(id.empty())
    {
      return;
    }
    const clang::MacroInfo* macroInfo = p_macroDirective->getMacroInfo();
    if(macroInfo->isFunctionLike())
    {
      const auto &params = macroInfo->params();
      for(const auto &param: params)
      {
        const std::string& paramStr = param->getName().str();
        if(paramStr.compare("__VA_ARGS__") == 0)
        {
          parameters.emplace_back("...");
        }
        else
        {
          parameters.emplace_back(paramStr);
        }
      }
    }
    unsigned numToken = macroInfo->getNumTokens();
    for(unsigned i = 0; i < numToken; i++)
    {
      std::string strToAdd;
      const clang::Token& tok = macroInfo->getReplacementToken(i);
      strToAdd = getTokenString(tok);
      if(!definition.empty())
      {
        definition.push_back(' ');
      }
      definition.append(strToAdd);
    }
    if(m_ctxt.hasMacroDefine(id))
    {
      fprintf(stderr, "Warning: Redefining %s\n", id.c_str());
    }
    m_ctxt.addMacroDefine(std::move(id), std::move(parameters), std::move(definition));
  }

  virtual void MacroUndefined(const clang::Token &p_macroIdentifierTok, const clang::MacroDefinition &p_macroDefinition, const clang::MacroDirective *p_macroDirective) override
  {
    std::string id = getTokenString(p_macroIdentifierTok);
    if(!m_ctxt.hasMacroDefine(id))
    {
      fprintf(stderr, "Warning: Undefining %s while it was not defined\n", id.c_str());
      return;
    }
    m_ctxt.deleteMacroDefine(id);
  }
private:
  ElementToMockContext& m_ctxt;
  clang::SourceManager& m_sm;

  std::string getTokenString(const clang::Token &tok)
  {
    const clang::IdentifierInfo* identifierInfo = tok.getIdentifierInfo();
    const clang::tok::TokenKind& tokenKind = tok.getKind();
    if(identifierInfo != nullptr)
    {
      return std::string(identifierInfo->getName().str());
    }
    const char* punctuationSpelling = getPunctuatorSpelling(tokenKind);
    if(punctuationSpelling)
    {
      return std::string(punctuationSpelling);
    }
    if(isLiteral(tokenKind))
    {
      const char* lit = tok.getLiteralData();
      auto length = tok.getLength();
      return std::string{lit, length};
    }
    return std::string("");
  }
};

class FunctionDeclFrontendAction : public clang::ASTFrontendAction
{
public:
  FunctionDeclFrontendAction(ElementToMockContext& ctxt) :
  clang::ASTFrontendAction(), m_ctxt(ctxt)
  {
  }

  virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance& CI, clang::StringRef file) override
  {
    clang::Preprocessor& PP = CI.getPreprocessor();
    clang::SourceManager& sm = CI.getSourceManager();
    PP.addPPCallbacks(std::make_unique<MacroBrowser>(m_ctxt, sm));
    return std::make_unique<FunctionDeclASTConsumer>(CI, m_ctxt);
  }
private:
  ElementToMockContext& m_ctxt;
};

std::unique_ptr<clang::tooling::FrontendActionFactory> newFunctionDeclFrontendAction(ElementToMockContext& ctxt) {
  class FunctionDeclFrontendActionFactory : public clang::tooling::FrontendActionFactory {
  public:
    FunctionDeclFrontendActionFactory(ElementToMockContext& ctxt) :
    clang::tooling::FrontendActionFactory(), m_ctxt(ctxt)
    {
    }
    std::unique_ptr<clang::FrontendAction> create() override { return std::make_unique<FunctionDeclFrontendAction>(m_ctxt); }
  private:
    ElementToMockContext& m_ctxt;
  };

  return std::unique_ptr<clang::tooling::FrontendActionFactory>(
      new FunctionDeclFrontendActionFactory(ctxt));
}

LLVMParser::LLVMParser() : CodeParserItf()
{
}

LLVMParser::LLVMParser(std::string& filename, ParserExtraArgs& flags)  : CodeParserItf(filename, flags)
{
}

CodeParser_errCode LLVMParser::getElementToMockContext(ElementToMockContext& p_ctxt) const
{
  std::string dir = ".";
  llvm::Twine twineDir(dir);
  //Place holder variable to add default hardcoded arguments to the tool if we need to
  std::vector<std::string> LLVMExtraArgs({});
  for(const std::string& extraArg: m_flags)
  {
    LLVMExtraArgs.emplace_back(extraArg);
  }
  /*
   * C_IMPLICIT_INCLUDE_DIRECTORY is passed at the compile command line
   * and contains the default include path of the compiler
   */
  const std::string cImplicitIncludeDirectories = C_IMPLICIT_INCLUDE_DIRECTORIES;
  std::string token;
  std::istringstream cImplicitIncludeDirectoriesStream(cImplicitIncludeDirectories);
  while (std::getline(cImplicitIncludeDirectoriesStream, token, ':'))
  {
    std::string toAdd("-I");
    toAdd.append(token);
    LLVMExtraArgs.emplace_back(toAdd);
  }
  clang::tooling::FixedCompilationDatabase db(twineDir, LLVMExtraArgs);
  std::vector<std::string> arRef({m_filename});
  clang::tooling::ClangTool tool(db, arRef);
  tool.run(newFunctionDeclFrontendAction(p_ctxt).get());
  return cp_OK;
}

LLVMParser::~LLVMParser() { }
