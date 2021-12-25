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

#include <boost/filesystem.hpp>

#include <string>
#include <vector>
#include <unordered_map>
#include <regex>
#include <memory>
#include <optional>
#include <sstream>

namespace
{
std::string trim(const std::string &s) {
  std::string rs{s};
  while(!rs.empty() && std::isspace(rs.front()))
  {
    rs.erase(0, 1);
  }
  while(!rs.empty() && std::isspace(rs.back()))
  {
    rs.pop_back();
  }
  return rs;
}
}

struct ParserConfig
{
  const MockOnlyList& mockOnlyList;
  const IgnoreTypeFieldList& ignoreTypeFieldList;
  const boost::filesystem::path& mainFile;
  const IgnoreFunList& ignoreFunList;
  bool parseIncludedFunctions;
};

/*!
 * \brief An implementation of a LLVM clang::RecursiveASTVisitor<FunctionDeclASTVisitor>
 */
class FunctionDeclASTVisitor : public clang::RecursiveASTVisitor<FunctionDeclASTVisitor>
{
private:
  using structKnownTypeMap = std::unordered_map<std::string, std::shared_ptr<IncompleteType>>;
public:

  explicit FunctionDeclASTVisitor(clang::SourceManager& sm, ElementToMockContext& ctxt, const ParserConfig& parserConfig)
  : m_sourceManager(sm),
  m_ctxt(ctxt),
  m_context(nullptr),
  m_mockOnlyList{parserConfig.mockOnlyList},
  m_ignoreTypeFieldList{parserConfig.ignoreTypeFieldList},
  m_mainFile{parserConfig.mainFile},
  m_ignoreFunList{parserConfig.ignoreFunList},
  m_parseIncludedFunctions{parserConfig.parseIncludedFunctions}
  {
    (void)m_sourceManager;
    m_cachedStruct.clear();
  }

  /*!
   * \brief Parses a single function.
   *
   * This function adds a new ElementToMock object to the list of ElementVector
   * which is returned by the parser.
   */
  bool VisitFunctionDecl(clang::FunctionDecl* func)
  {
    auto f = getFunctionDeclaration(func);
    if(f)
    {
      f->cacheHash();
      m_ctxt.addElementToMock(std::move(*f));
    }

    return true;
  }

  std::optional<FunctionDeclaration> getFunctionDeclaration(const clang::FunctionDecl* func)
  {
    const std::string funName = getFunctionName(func);
    if(!m_mockOnlyList.empty() && std::find(std::begin(m_mockOnlyList), std::end(m_mockOnlyList), funName) == std::end(m_mockOnlyList))
    {
      return std::nullopt;
    }
    if(!m_ignoreFunList.empty() && std::find(std::begin(m_ignoreFunList), std::end(m_ignoreFunList), funName) != std::end(m_ignoreFunList))
    {
      return std::nullopt;
    }
    std::string originFileFullInfo = func->getLocation().printToString(*m_SM);
    size_t posColumn = originFileFullInfo.find_first_of(':');
    std::string originFile = originFileFullInfo.substr(0,posColumn);
    boost::filesystem::path originCanon = boost::filesystem::canonical(originFile);

    bool isFromMainFile = m_mainFile == originCanon;
    if(!m_parseIncludedFunctions && !isFromMainFile)
    {
      return std::nullopt;
    }

    ReturnValue rv = getFunctionReturnValue(func);
    Parameter::Vector param = getFunctionParameters(func);
    FunctionDeclaration f(funName, std::move(rv), std::move(param));
    bool isInline = func->isInlined();
    bool doesThisDeclHasABody = func->doesThisDeclarationHaveABody();
    bool isStatic = func->isStatic();
    f.setVariadic(func->isVariadic());
    f.setInlined(isInline);
    f.setIsStatic(isStatic);
    f.setDoesThisDeclarationHasABody(doesThisDeclHasABody);
    f.setOriginFile(originFileFullInfo);
    setFunctionAttribute(func, f);
    return std::make_optional<FunctionDeclaration>(std::move(f));
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
  const MockOnlyList& m_mockOnlyList;
  const IgnoreTypeFieldList& m_ignoreTypeFieldList;
  std::unordered_map<std::string, std::shared_ptr<TypeItf>> m_cachedStruct;
  const boost::filesystem::path& m_mainFile;
  const IgnoreFunList& m_ignoreFunList;
  bool m_parseIncludedFunctions;

  enum ContainerType {
    STRUCT,
    UNION
  };

  void setFunctionAttribute(const clang::FunctionDecl* clangFunc, FunctionDeclaration& easyMockFun)
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

      easyMockFun.addAttribute(std::move(functionAttribute));
    }
    if(clangFunc->isNoReturn())
    {
      std::string noreturn{"noreturn"};
      easyMockFun.addAttribute(std::move(noreturn));
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

  void removeFromString(std::string &declString, std::string macroStr, bool hasParameter)
  {
    /*
     * It is needed to escape "(" and ")" in case there are some so that they are not taken as group inside the
     * std::regex
     */
    static std::regex leftParentRegex{"\\("};
    static std::regex rightParentRegex{"\\)"};
    macroStr = std::regex_replace(macroStr, leftParentRegex, "\\(");
    macroStr = std::regex_replace(macroStr, rightParentRegex, "\\)");
    /*
     * The macro string doesn't contain any parameter. Matching any parameter is added by hand.
     */
    if(hasParameter)
    {
      macroStr.append("\\(.*\\)");
    }
    declString = std::regex_replace(declString, std::regex{macroStr}, "");
  }

  void removeAttr(std::string &declString, const clang::Attr* attr)
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
      removeFromString(declString, std::move(macroStr), false);
    }
  }

  ReturnValue getFunctionReturnValue(const clang::FunctionDecl* func)
  {
    const std::string funName = getFunctionName(func);
    const clang::QualType &rvQualType = func->getReturnType();
    structKnownTypeMap structKnownType;

    auto type = getEasyMocktype(rvQualType, structKnownType, false);
    ReturnValue rv(std::move(type));

    /*
     * clang::QualType doesn't have any SourceRange information. The source range is approximated by taking
     * the very beginning of the function declaration and the beginning position of the function name.
     */
    clang::SourceLocation beginSourceLocation = func->getBeginLoc();
    clang::SourceLocation startOfFunNameLocation = func->getNameInfo().getBeginLoc();
    std::string declString = getDeclareString(beginSourceLocation, startOfFunNameLocation, false);
    /*
     * Loop through all the function attributes and determine whether they are declared using a macro.
     * If they are declared using a macro, just remove the macro call from the declString.
     */
    for(const auto& attr : func->attrs())
    {
      removeAttr(declString, attr);
    }
    static std::regex removeAttrRegex{"__attribute__[[:space:]]*\\([[:space:]]*\\(.*\\)[[:space:]]*\\)"};

    /*
     * Loop through all the token of the declaration and verifies if it expands to __attribute((<something>)).
     * If so, remove the token.
     * This is needed because some attribute like "noreturn" aren't part of the function attribute list for
     * LLVM.
     */
    clang::SourceLocation itrSource = beginSourceLocation;
    while(m_SM->isBeforeInTranslationUnit(itrSource,startOfFunNameLocation))
    {
      //itrSource = clang::Lexer::GetBeginningOfToken(itrSource, *m_SM, *m_LO);
      clang::Token rawToken;
      clang::Lexer::getRawToken(itrSource, rawToken, *m_SM, *m_LO, true);

      clang::CharSourceRange dumpSourceRange = clang::Lexer::getAsCharRange(rawToken.getLocation(), *m_SM, *m_LO);
      dumpSourceRange.setEnd(rawToken.getEndLoc());
      clang::StringRef dumpStrRef = clang::Lexer::getSourceText(dumpSourceRange, *m_SM, *m_LO);
      const std::string currentTokenStr{dumpStrRef.str()};
      if(m_ctxt.hasMacroDefine(currentTokenStr))
      {
        const MacroDefinition& md = m_ctxt.getMacroDefinition(currentTokenStr);
        std::string macroStr = md.getDefinition();
        std::smatch match;
        if(macroStr.empty() || std::regex_match(macroStr, match, removeAttrRegex))
        {
          removeFromString(declString, std::move(currentTokenStr), md.hasParameters());
        }
      }
      itrSource = itrSource.getLocWithOffset(currentTokenStr.length());
    }

    declString = std::regex_replace(declString, removeAttrRegex, "");
    eraseInString(declString, "inline ");
    eraseInString(declString, "extern ");
    eraseInString(declString, "static ");
    declString = trim(declString);
    setDeclaratorDeclareString(rvQualType, &rv, declString);

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
      std::shared_ptr<TypeItf> type = getEasyMocktype(paramQualType, structKnownType, false);

      Parameter p{std::move(type), paramName};
      clang::SourceLocation beginLoc = param->getBeginLoc();
      const TypeItf* parameterRawType = p.getType()->getRawType();
      /*
       * Get the declared string if this is a macro, typedef or an implicit type. Else it is possible that
       * the declared string we try to parse misses some information while the default one coming from the
       * framework is correct.
       *
       * See VoidFunUnnamedPtrParam test for reproduction scenario.
       * See VoidFunEnumFactory (unnamed param) test for reproduction scenario.
       */
      if(beginLoc.isMacroID() || parameterRawType->isImplicit())
      {
        std::string declareString = getDeclareString(beginLoc, param->getEndLoc(), false);
        setDeclaratorDeclareString(paramQualType, &p, declareString);
      }
      vectParam.push_back(std::move(p));
    }

    return vectParam;
  }

  std::string removeComments(std::string declareString)
  {
    static std::regex oneLineCommentRegex{"//.*\n"};
    declareString = std::regex_replace(declareString, oneLineCommentRegex, "");
    for(auto& c : declareString)
    {
      if(c == '\n')
      {
        c = ' ';
      }
    }
    static std::regex commentRegex{"/\\*.*\\*/"};
    declareString = std::regex_replace(declareString, commentRegex, "");

    return declareString;
  }

  std::string getDeclareString(const clang::SourceLocation& startLoc, const clang::SourceLocation& endLoc, bool fieldDecl)
  {
    clang::CharSourceRange charSourceRange = clang::Lexer::getAsCharRange(startLoc, *m_SM, *m_LO);
    charSourceRange.setEnd(endLoc);
    clang::StringRef strRef = clang::Lexer::getSourceText(charSourceRange, *m_SM, *m_LO);
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
    declareString = removeComments(std::move(declareString));
    declareString = trim(std::move(declareString));

    return declareString;
  }

  std::shared_ptr<TypeItf> getEasyMocktype(const clang::QualType &clangQualType, structKnownTypeMap &structKnownType, bool isEmbeddedInOtherType)
  {
    const clang::Type &clangType = *clangQualType.getTypePtr();
    const std::string& nakedDeclString = clangQualType.getCanonicalType().getAsString();
    std::shared_ptr<TypeItf> type;
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
      type = std::make_shared<ConstQualifiedType>(std::move(type));
    }

    clang::RecordDecl *recDecl = clangType.getAsRecordDecl();
    if(recDecl)
    {
      type->setImplicit(recDecl->isImplicit());
    }

    return type;
  }

  std::shared_ptr<TypeItf> getFromBuiltinType(const clang::Type &type, const std::string& nakedDeclString)
  {
    std::shared_ptr<CType> cType = nullptr;

    if(type.isVoidType())
    {
      cType = std::make_shared<CType>(CTYPE_VOID);
    }
    else if(type.isCharType())
    {
#if IS_CHAR_DEFAULT_UNSIGNED
      if(type.isUnsignedIntegerType() && nakedDeclString.compare("unsigned char") == 0)
      {
        cType = std::make_shared<CType>(CTYPE_UCHAR);
      }
      else
#endif
      {
        cType = std::make_shared<CType>(CTYPE_CHAR);
      }
    }
    else if(isShortType(type))
    {
      cType = std::make_shared<CType>(CTYPE_SHORT);
    }
    else if(isLongType(type))
    {
      cType = std::make_shared<CType>(CTYPE_LONG);
    }
    else if(isIntType(type))
    {
      cType = std::make_shared<CType>(CTYPE_INT);
    }
    else if(isLongLongType(type))
    {
      cType = std::make_shared<CType>(CTYPE_LONG_LONG);
    }
    else if(isDoubleType(type))
    {
      cType = std::make_shared<CType>(CTYPE_DOUBLE);
    }
    else if(isLongDoubleType(type))
    {
      cType = std::make_shared<CType>(CTYPE_LONG_DOUBLE);
    }
    else if(isFloatType(type))
    {
      cType = std::make_shared<CType>(CTYPE_FLOAT);
    }
    else if(isBoolType(type))
    {
      cType = std::make_shared<CType>(CTYPE_INT);
    }
    else if(isInt128Type(type))
    {
      cType = std::make_shared<CType>(CTYPE_INT128);
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
    std::shared_ptr<TypeItf> returnedType = cType;
    if(!typedefName.empty())
    {
      returnedType = std::make_shared<TypedefType>(typedefName, std::move(returnedType));
    }

    return returnedType;
  }

  std::shared_ptr<TypeItf> getFromStructType(const clang::Type &type, structKnownTypeMap &structKnownType, bool isEmbeddedInOtherType)
  {
    return getFromContainerType(type, STRUCT, structKnownType, isEmbeddedInOtherType);
  }

  std::shared_ptr<TypeItf> getFromUnionType(const clang::Type &type, structKnownTypeMap &structKnownType, bool isEmbeddedInOtherType)
  {
    return getFromContainerType(type, UNION, structKnownType, isEmbeddedInOtherType);
  }

  /*
   * This function awfully looks alike with the getFunctionDeclaration
   * and getFunctionParameters(). However, the objects used are a little
   * different as well as the API. Therefore, we need to re-implement the same
   * kind of logic.
   */
  std::shared_ptr<TypeItf> getFromFunctionPrototype(const clang::Type &type, structKnownTypeMap &structKnownType)
  {
    const clang::FunctionProtoType *fp = type.getAs<clang::FunctionProtoType>();

    const clang::QualType &rvQualType = fp->getReturnType();

    std::shared_ptr<TypeItf> rvType = getEasyMocktype(rvQualType, structKnownType, false);
    ReturnValue rv(std::move(rvType));

    unsigned nbParams = fp->getNumParams();
    Parameter::Vector vectParam;
    for(unsigned paramIdx = 0; paramIdx < nbParams; paramIdx++)
    {
      const clang::QualType& paramQualType = fp->getParamType(paramIdx);
      auto paramType = getEasyMocktype(paramQualType, structKnownType, false);

      Parameter p = Parameter{std::move(paramType), ""};
      vectParam.push_back(std::move(p));
    }
    auto f = std::make_shared<FunctionType>(std::move(rv), std::move(vectParam));

    return f;
  }

  std::shared_ptr<TypeItf> getFromEnumType(const clang::Type &type, structKnownTypeMap &structKnownType)
  {
    const clang::EnumType *ET = type.getAs<clang::EnumType>();
    const clang::EnumDecl *ED = ET->getDecl();

    const std::string name = ED->getNameAsString();

    std::shared_ptr<Enum> enumType = std::make_shared<Enum>(name);
    for(const auto enumConstantDeclaration : ED->enumerators())
    {
      int64_t enumValue = enumConstantDeclaration->getInitVal().getExtValue();
      const std::string enumName = enumConstantDeclaration->getNameAsString();
      enumType->addEnumValue(enumValue, enumName);
    }
    const std::string typedefName = getTypedefName(type);
    std::shared_ptr<TypeItf> toReturn = enumType;
    if(!typedefName.empty())
    {
      toReturn = std::make_shared<TypedefType>(typedefName, std::move(toReturn));
    }
    return toReturn;
  }

  std::shared_ptr<TypeItf> getFromContainerType(const clang::Type &p_type, ContainerType contType, structKnownTypeMap &structKnownType, bool p_isEmbeddedInOtherType)
  {
    const clang::RecordType *RT = nullptr;
    std::string contTypeDecl;
    switch(contType)
    {
      case STRUCT:
        RT = p_type.getAsStructureType();
        contTypeDecl.append("struct ");
        break;
      case UNION:
        RT = p_type.getAsUnionType();
        contTypeDecl.append("union ");
        break;
    }

    clang::RecordDecl* RD = RT->getDecl();
    std::string typeName = RD->getNameAsString();
    std::string typedDefName = getTypedefName(p_type);

    if(structKnownType.find(typedDefName) != structKnownType.end())
    {
      return structKnownType.at(typedDefName);
    }
    if(structKnownType.find(typeName) != structKnownType.end())
    {
      return structKnownType.at(typeName);
    }

    std::string declToCheck = typeName + std::string{"_"} + typedDefName;
    if(declToCheck.compare("_") != 0)
    {
      if(m_cachedStruct.find(declToCheck) != m_cachedStruct.end())
      {
        return m_cachedStruct[declToCheck];
      }
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

    std::shared_ptr<ComposableType> sType = nullptr;
    IncompleteType::Type incType = IncompleteType::Type::STRUCT;
    switch(contType)
    {
      case STRUCT:
        sType = std::make_shared<StructType>(typeName, isEmbeddedInOtherType);
        incType = IncompleteType::Type::STRUCT;
        break;
      case UNION:
        sType = std::make_shared<UnionType>(typeName, isEmbeddedInOtherType);
        incType = IncompleteType::Type::UNION;
    }
    if(!typedDefName.empty())
    {
      structKnownType.insert({typedDefName,std::make_shared<IncompleteType>(*sType, incType)});
    }
    if(!typeName.empty())
    {
      structKnownType.insert({typeName, std::make_shared<IncompleteType>(*sType, incType)});
    }

    // If the type doesn't have a complete definition, it is forward declared.
    sType->setForwardDecl(!RD->isCompleteDefinition());

    if(m_ignoreTypeFieldList.find(typeName) == m_ignoreTypeFieldList.end())
    {
      for (clang::FieldDecl *FD:
          RD->fields())
      {
        const clang::QualType &qualType = FD->getType();
        const clang::Type *typePtr = qualType.getTypePtr();
        std::string fName = FD->getNameAsString();
        auto fieldType = getEasyMocktype(qualType, structKnownType, true);

        if (FD->isBitField())
        {
          TypedefType *typedefFieldType = fieldType->asTypedefType();
          if (!fieldType->isCType() && (typedefFieldType && !typedefFieldType->getMostDefinedTypee()->isCType()))
          {
            fprintf(stderr, "Type must be CType for bitfields");
            typePtr->dump();
            assert(false);
          }
          unsigned bitWidth = FD->getBitWidthValue(*m_context);
          assert(bitWidth < 256);
          sType->addField(ComposableBitfield{std::move(fieldType), fName, static_cast<uint8_t>(bitWidth)});
        } else
        {
          int64_t arraySize = getArraySize(*typePtr);
          if (!typePtr->isArrayType())
          {
            arraySize = -1;
          }
          ComposableField sf{std::move(fieldType), fName, {.arraySize = arraySize}};
          setDeclaratorDeclareString(qualType, &sf, getDeclareString(FD->getBeginLoc(), FD->getEndLoc(), true));
          sType->addField(std::move(sf));
        }
      }
    }
    std::shared_ptr<TypeItf> toReturn = sType;
    if(!typedDefName.empty())
    {
      toReturn = std::make_shared<TypedefType>(typedDefName, std::move(toReturn));
      structKnownType.erase(typedDefName);
    }
    if(!typeName.empty())
    {
      structKnownType.erase(typeName);
    }

    if(declToCheck.compare("_") != 0)
    {
      if(m_cachedStruct.find(declToCheck) == m_cachedStruct.end())
      {
        m_cachedStruct.insert({declToCheck, toReturn});
      }
    }

    return toReturn;
  }

  std::shared_ptr<TypeItf> getFromPointerType(const clang::Type &type, structKnownTypeMap &structKnownType, bool isEmbeddedInOtherType)
  {
    const clang::QualType &pointeeQualType = type.getPointeeType();
    auto rv = getEasyMocktype(pointeeQualType, structKnownType, isEmbeddedInOtherType);

    std::shared_ptr<TypeItf> returnedTyped = std::make_shared<Pointer>(std::move(rv));
    std::string typedDefName = getTypedefName(type);
    if(!typedDefName.empty())
    {
      returnedTyped = std::make_shared<TypedefType>(typedDefName, std::move(returnedTyped));
    }

    return returnedTyped;
  }

  std::shared_ptr<TypeItf> getFromArrayType(const clang::Type &type, structKnownTypeMap &structKnownType, bool isEmbeddedInOtherType)
  {
    const clang::ArrayType &arrayType = *type.getAsArrayTypeUnsafe();
    const clang::QualType &arrayElemQualType = arrayType.getElementType();

    auto rv = getEasyMocktype(arrayElemQualType, structKnownType, isEmbeddedInOtherType);

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

  FunctionDeclASTConsumer(clang::CompilerInstance& ci, ElementToMockContext& ctxt, const ParserConfig& parserConfig)
  : clang::ASTConsumer(), m_visitor(ci.getSourceManager(), ctxt, parserConfig) { }

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
    std::string sourceLocation = p_macroIdentifierTok.getLocation().printToString(m_sm);
    m_ctxt.addMacroDefine(std::move(id), std::move(parameters), std::move(definition), std::move(sourceLocation));
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
  FunctionDeclFrontendAction(ElementToMockContext& ctxt, const ParserConfig& parserConfig) :
  clang::ASTFrontendAction(), m_ctxt(ctxt), m_parserConfig{parserConfig}
  {
  }

  virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance& CI, clang::StringRef file) override
  {
    clang::Preprocessor& PP = CI.getPreprocessor();
    clang::SourceManager& sm = CI.getSourceManager();
    PP.addPPCallbacks(std::make_unique<MacroBrowser>(m_ctxt, sm));
    return std::make_unique<FunctionDeclASTConsumer>(CI, m_ctxt, m_parserConfig);
  }
private:
  ElementToMockContext& m_ctxt;
  const ParserConfig& m_parserConfig;
};

std::unique_ptr<clang::tooling::FrontendActionFactory> newFunctionDeclFrontendAction(ElementToMockContext& ctxt, const ParserConfig& parserConfig) {
  class FunctionDeclFrontendActionFactory : public clang::tooling::FrontendActionFactory {
  public:
    FunctionDeclFrontendActionFactory(ElementToMockContext& ctxt, const ParserConfig& parserConfig) :
    clang::tooling::FrontendActionFactory(), m_ctxt(ctxt), m_parserConfig{parserConfig}
    {
    }
    std::unique_ptr<clang::FrontendAction> create() override { return std::make_unique<FunctionDeclFrontendAction>(m_ctxt, m_parserConfig); }
  private:
    ElementToMockContext& m_ctxt;
    const ParserConfig& m_parserConfig;
  };

  return std::unique_ptr<clang::tooling::FrontendActionFactory>(
      new FunctionDeclFrontendActionFactory(ctxt, parserConfig));
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
  boost::filesystem::path fullPath = boost::filesystem::canonical(m_filename);
  std::vector<std::string> arRef({fullPath.string()});
  clang::tooling::ClangTool tool(db, arRef);
  ParserConfig parserConfig
    {
      m_mockOnlyList,
      m_ignoreTypeFieldList,
      fullPath,
      m_ignoreFunList,
      m_parseIncludedFunctions
    };
  tool.run(newFunctionDeclFrontendAction(p_ctxt, parserConfig).get());
  return cp_OK;
}

LLVMParser::~LLVMParser() { }
