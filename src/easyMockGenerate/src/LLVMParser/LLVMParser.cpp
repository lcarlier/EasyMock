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

#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendActions.h>
#include <clang/Tooling/CompilationDatabase.h>
#include <clang/Tooling/Tooling.h>

#include <boost/algorithm/string.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <boost/filesystem/path.hpp>
#include <unordered_map>
#include <string>
#include <sstream>

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

  ReturnValue getFunctionReturnValue(const clang::FunctionDecl* func)
  {
    const std::string funName = getFunctionName(func);
    const clang::QualType &rvQualType = func->getReturnType();
    structKnownTypeMap structKnownType;

    TypeItf *type = getEasyMocktype(rvQualType, structKnownType);
    ReturnValue rv(type);
    std::string declString = getDeclareString(func->getBeginLoc(), func->getEndLoc());
    size_t funNamePos = declString.find(funName);
    if(funNamePos != std::string::npos)
    {
      declString.erase(declString.begin() + funNamePos, declString.end());
    }
    while(declString.back() == ' ')
    {
      declString.pop_back();
    }
    eraseInString(declString, "inline ");
    eraseInString(declString, "extern ");
    setDeclaratorDeclareString(rvQualType, &rv, declString);
    type = nullptr; //We lost the ownership

    return rv;
  }

  Parameter::Vector getFunctionParameters(const clang::FunctionDecl* func)
  {
    Parameter::Vector vectParam;
    unsigned nbParam = func->getNumParams();
    std::string funcDecl = getDeclareString(func->getBeginLoc(), func->getEndLoc());

    for(unsigned paramIdx = 0; paramIdx < nbParam; paramIdx++)
    {
      const clang::ParmVarDecl *param = func->getParamDecl(paramIdx);
      const clang::QualType paramQualType = param->getType();

      structKnownTypeMap structKnownType;
      const std::string paramName = param->getNameAsString();
      TypeItf *type = getEasyMocktype(paramQualType, structKnownType);

      Parameter *p = new Parameter(type, paramName);
      type = nullptr; //We lost the ownership
      setDeclaratorDeclareString(paramQualType, p, getDeclareString(param->getBeginLoc(), param->getEndLoc()));
      vectParam.push_back(p);
      p = nullptr; //We lost the ownership
    }

    return vectParam;
  }

  std::string getDeclareString(const clang::SourceLocation& startLoc, const clang::SourceLocation& endLoc)
  {
    clang::CharSourceRange sourceRange = clang::Lexer::getAsCharRange(startLoc, *m_SM, *m_LO);
    sourceRange.setEnd(endLoc);
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
      while(!declareString.empty() && declareString.back() != ' ' &&
              declareString.back() != '*' &&
              declareString.back() != ')')
      {
        declareString.pop_back();
      }
    }
    while(!declareString.empty() &&
            (declareString.back() == ' '  ||
           declareString.back() == '\n' ||
           declareString.back() == '\t' ||
           declareString.back() == '\r')
            )
    {
      declareString.pop_back();
    }

    return declareString;
  }

  TypeItf* getEasyMocktype(const clang::QualType &clangQualType, structKnownTypeMap &structKnownType)
  {
    const clang::Type &clangType = *clangQualType.getTypePtr();
    const std::string& nakedDeclString = clangQualType.getAsString();
    TypeItf *type = nullptr;
    if(clangType.isBuiltinType())
    {
      type = getFromBuiltinType(clangType, nakedDeclString);
    }
    else if(clangType.isStructureType())
    {
      type = getFromStructType(clangType, structKnownType);
    }
    else if(clangType.isPointerType())
    {
      type = getFromPointerType(clangType, structKnownType);
    }
    else if (clangType.isArrayType())
    {
      type = getFromArrayType(clangType, structKnownType);
    }
    else if (clangType.isUnionType())
    {
      type = getFromUnionType(clangType, structKnownType);
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
    type->setConst(clangQualType.isLocalConstQualified());

    clang::RecordDecl *recDecl = clangType.getAsRecordDecl();
    if(recDecl)
    {
      type->setImplicit(recDecl->isImplicit());
    }

    return type;
  }

  CType* getFromBuiltinType(const clang::Type &type, const std::string& nakedDeclString)
  {
    CType *returnedType = nullptr;

    const std::string typedefName= getTypedefName(type);
    if(type.isVoidType())
    {
      returnedType = new CType(CTYPE_VOID, typedefName);
    }
    else if(type.isCharType())
    {
#if IS_CHAR_DEFAULT_UNSIGNED
      if(type.isUnsignedIntegerType() && nakedDeclString.compare("unsigned char") == 0)
      {
        returnedType = new CType(CTYPE_UCHAR, typedefName);
      }
      else
#endif
      {
        returnedType = new CType(CTYPE_CHAR, typedefName);
      }
    }
    else if(isShortType(type))
    {
      returnedType = new CType(CTYPE_SHORT, typedefName);
    }
    else if(isLongType(type))
    {
      returnedType = new CType(CTYPE_LONG, typedefName);
    }
    else if(isIntType(type))
    {
      returnedType = new CType(CTYPE_INT, typedefName);
    }
    else if(isLongLongType(type))
    {
      returnedType = new CType(CTYPE_LONG_LONG, typedefName);
    }
    else if(isDoubleType(type))
    {
      returnedType = new CType(CTYPE_DOUBLE, typedefName);
    }
    else if(isLongDoubleType(type))
    {
      returnedType = new CType(CTYPE_LONG_DOUBLE, typedefName);
    }
    else if(isFloatType(type))
    {
      returnedType = new CType(CTYPE_FLOAT, typedefName);
    }
    else if(isBoolType(type))
    {
      returnedType = new CType(CTYPE_INT, typedefName);
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
      returnedType->setUnsigned(true);
    }

    return returnedType;
  }

  TypeItf* getFromStructType(const clang::Type &type, structKnownTypeMap &structKnownType)
  {
    return getFromContainerType(type, STRUCT, structKnownType);
  }

  TypeItf* getFromUnionType(const clang::Type &type, structKnownTypeMap &structKnownType)
  {
    return getFromContainerType(type, UNION, structKnownType);
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

    TypeItf *rvType = getEasyMocktype(rvQualType, structKnownType);
    ReturnValue rv(rvType);
    rvType = nullptr; //We lost the ownership

    unsigned nbParams = fp->getNumParams();
    Parameter::Vector vectParam;
    for(unsigned paramIdx = 0; paramIdx < nbParams; paramIdx++)
    {
      const clang::QualType& paramQualType = fp->getParamType(paramIdx);
      TypeItf *paramType = getEasyMocktype(paramQualType, structKnownType);

      Parameter *p = new Parameter(paramType, "");
      paramType = nullptr; //We lost the ownership
      vectParam.push_back(p);
      p = nullptr; //We lost the ownership
    }
    FunctionType *f = new FunctionType("", rv, vectParam);

    return f;
  }

  TypeItf* getFromEnumType(const clang::Type &type, structKnownTypeMap &structKnownType)
  {
    const clang::EnumType *ET = type.getAs<clang::EnumType>();
    const clang::EnumDecl *ED = ET->getDecl();

    const std::string name = ED->getNameAsString();
    const std::string typedefName= getTypedefName(type);

    return new Enum(name, typedefName);
  }

  TypeItf* getFromContainerType(const clang::Type &type, ContainerType contType, structKnownTypeMap &structKnownType)
  {
    const clang::RecordType *RT = nullptr;
    switch(contType)
    {
      case STRUCT:
        RT = type.getAsStructureType();
        break;
      case UNION:
        RT = type.getAsUnionType();
        break;
    }

    clang::RecordDecl* RD = RT->getDecl();
    std::string typeName = RD->getNameAsString();
    std::string typedDefName = getTypedefName(type);

    if(structKnownType.find(typedDefName) != structKnownType.end())
    {
      return structKnownType.at(typedDefName).clone();
    }
    if(structKnownType.find(typeName) != structKnownType.end())
    {
      return structKnownType.at(typeName).clone();
    }

    bool isEmbeddedInOtherType = false;
    const clang::TypedefType* TDT = type.getAs<clang::TypedefType>();
    clang::TypedefNameDecl* TD_RD = nullptr;
    if(TDT != nullptr)
    {
      TD_RD = TDT->getDecl();
    }
    if(TD_RD != nullptr)
    {
      //isTopLevelDeclInObjCContainer seems to be equivalent to isEmbeddedInDeclarator for typedef
      isEmbeddedInOtherType = TD_RD->isTopLevelDeclInObjCContainer();
    }
    else
    {
      isEmbeddedInOtherType = RD->isEmbeddedInDeclarator();
    }

    ComposableType *sType = nullptr;
    switch(contType)
    {
      case STRUCT:
        sType = new StructType(typeName, typedDefName, isEmbeddedInOtherType);
        break;
      case UNION:
        sType = new UnionType(typeName, typedDefName, isEmbeddedInOtherType);
    }
    if(!typedDefName.empty())
    {
      structKnownType.insert({typedDefName,IncompleteType(*sType)});
    }
    if(!typeName.empty())
    {
      structKnownType.insert({typeName, IncompleteType(*sType)});
    }
    for (clang::FieldDecl *FD :
          RD->fields()) {
      const clang::QualType &qualType = FD->getType();
      const clang::Type *typePtr = qualType.getTypePtr();
      TypeItf *type = getEasyMocktype(qualType, structKnownType);

      int64_t arraySize = getArraySize(*typePtr);
      if(!typePtr->isArrayType())
      {
          arraySize = -1;
      }
      ComposableField::attributes attrib =
      {
       .arraySize            = arraySize
      };
      std::string fName = FD->getNameAsString();
      ComposableField *sf = new ComposableField(type, fName, attrib);
      setDeclaratorDeclareString(qualType, sf, getDeclareString(FD->getBeginLoc(), FD->getEndLoc()));
      sType->addField(sf);
    }
    if(!typedDefName.empty())
    {
      structKnownType.erase(typedDefName);
    }
    if(!typeName.empty())
    {
      structKnownType.erase(typeName);
    }

    return sType;
  }

  TypeItf* getFromPointerType(const clang::Type &type, structKnownTypeMap &structKnownType)
  {
    const clang::QualType &pointeeQualType = type.getPointeeType();
    TypeItf *rv = getEasyMocktype(pointeeQualType, structKnownType);

    std::string typedDefName = getTypedefName(type);

    return new Pointer(rv, typedDefName, false);
  }

  TypeItf* getFromArrayType(const clang::Type &type, structKnownTypeMap &structKnownType)
  {
    const clang::ArrayType &arrayType = *type.getAsArrayTypeUnsafe();
    const clang::QualType &arrayElemQualType = arrayType.getElementType();

    TypeItf *rv = getEasyMocktype(arrayElemQualType, structKnownType);

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
    std::string definition("");
    id = getTokenString(p_macroIdentifierTok);
    if(id.empty())
    {
      return;
    }
    unsigned numToken = p_macroDirective->getMacroInfo()->getNumTokens();
    for(unsigned i = 0; i < numToken; i++)
    {
      std::string strToAdd;
      const clang::Token& tok = p_macroDirective->getMacroInfo()->getReplacementToken(i);
      strToAdd = getTokenString(tok);
      if(strToAdd.empty())
      {
        return;
      }
      if(!definition.empty())
      {
        definition.push_back(' ');
      }
      definition.append(strToAdd);
    }
    if(m_ctxt.hasMacroDefine(id))
    {
      fprintf(stderr, "Warning: Redifining %s\n", id.c_str());
    }
    m_ctxt.addMacroDefine(id, definition);
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
    clang::IdentifierInfo* identifierInfo;
    if((identifierInfo = tok.getIdentifierInfo()) != nullptr && identifierInfo->getBuiltinID() == 0)
    {
      return identifierInfo->getName().str();
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

