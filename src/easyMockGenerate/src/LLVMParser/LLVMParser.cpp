#include "LLVMParser.h"
#include "StructType.h"
#include "UnionType.h"

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

#include <Function.h>
#include <TypeItf.h>
#include <CType.h>

class FunctionDeclASTVisitor : public clang::RecursiveASTVisitor<FunctionDeclASTVisitor>
{
private:
  typedef std::unordered_map<std::string, ComposableType *> structKnownTypeMap;
public:

  explicit FunctionDeclASTVisitor(clang::SourceManager& sm, ElementToMock::Vector& elem)
  : m_sourceManager(sm), m_elem(elem), m_context(nullptr) { }

  virtual bool VisitFunctionDecl(clang::FunctionDecl* func)
  {
    if (m_sourceManager.isWrittenInMainFile(func->getSourceRange().getBegin()))
    {
      std::string funName = func->getNameInfo().getName().getAsString();

      ReturnValue rv = getFunctionReturnValue(func);
      Parameter::Vector param = getFunctionParameters(func);
      m_elem.push_back(new Function(funName, rv, param));
    }
    return true;
  }

  void setAstContext(const clang::ASTContext &ctx)
  {
    m_context = &ctx;
  }
private:
  clang::SourceManager& m_sourceManager;
  ElementToMock::Vector& m_elem;
  const clang::ASTContext *m_context;

  enum ContainerType {
    STRUCT,
    UNION
  };

  ReturnValue getFunctionReturnValue(clang::FunctionDecl* func)
  {
    ReturnValue rv;
    const clang::Type* clangType = func->getReturnType().getTypePtr();
    structKnownTypeMap structKnownType;
    TypeItf *type = getEasyMocktype(*clangType, structKnownType);
    rv.setPointer(clangType->isPointerType());
    rv.setType(type);
    type = nullptr; //We lost ownership
    return rv;
  }

  Parameter::Vector getFunctionParameters(clang::FunctionDecl* func)
  {
    Parameter::Vector vectParam;
    unsigned nbParam = func->getNumParams();

    for(unsigned paramIdx = 0; paramIdx < nbParam; paramIdx++)
    {
      const clang::ParmVarDecl *param = func->getParamDecl(paramIdx);
      const clang::Type* paramType = param->getType().getTypePtr();
      structKnownTypeMap structKnownType;
      TypeItf *type = getEasyMocktype(*paramType, structKnownType);
      vectParam.push_back(new Parameter(type, param->getNameAsString(), paramType->isPointerType()));
    }

    return vectParam;
  }

  TypeItf* getEasyMocktype(const clang::Type &clangType, structKnownTypeMap &structKnownType)
  {
    TypeItf *type = nullptr;
    if(clangType.isBuiltinType())
    {
      type = getFromBuiltinType(clangType);
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
    else
    {
      std::fprintf(stderr, "Clang type unexpected here. Contact the owner for bug fixing\n\r");
      clangType.dump();
      assert(false);
    }

    return type;
  }

  CType* getFromBuiltinType(const clang::Type &type)
  {
    CType *returnedType = nullptr;

    if(type.isVoidType())
    {
      returnedType = new CType(CTYPE_VOID);
    }
    else if(type.isCharType())
    {
      returnedType = new CType(CTYPE_CHAR);
    }
    else if(isShortType(type))
    {
      returnedType = new CType(CTYPE_SHORT);
    }
    else if(isLongType(type))
    {
      returnedType = new CType(CTYPE_LONG);
    }
    else if(isIntType(type))
    {
      returnedType = new CType(CTYPE_INT);
    }
    else if(isLongLongType(type))
    {
      returnedType = new CType(CTYPE_LONG_LONG);
    }
    else if(isDoubleType(type))
    {
      returnedType = new CType(CTYPE_DOUBLE);
    }
    else if(isLongDoubleType(type))
    {
      returnedType = new CType(CTYPE_LONG_DOUBLE);
    }
    else if(isFloatType(type))
    {
      returnedType = new CType(CTYPE_FLOAT);
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

    const clang::TypedefType* TDT = type.getAs<clang::TypedefType>();
    clang::TypedefNameDecl* TD_RD = nullptr;
    std::string typedDefName("");
    if(TDT != nullptr)
    {
      TD_RD = TDT->getDecl();
      typedDefName = TD_RD->getNameAsString();
    }

    if(structKnownType.find(typedDefName) != structKnownType.end())
    {
      return structKnownType[typedDefName];
    }
    if(structKnownType.find(typeName) != structKnownType.end())
    {
      return structKnownType[typeName];
    }

    bool isEmbeddedInOtherType = false;
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
    if(typedDefName.compare("") != 0)
    {
      structKnownType[typedDefName] = sType;
    }
    else
    {
      structKnownType[typeName] = sType;
    }
    for (clang::FieldDecl *FD :
          RD->fields()) {
      const clang::Type *typePtr = FD->getType().getTypePtr();
      TypeItf *type = getEasyMocktype(*typePtr, structKnownType);
      bool isRecursiveType = structKnownType.find(type->getName()) != structKnownType.end();
      uint64_t arraySize = getArraySize(*typePtr);
      ComposableField::attributes attrib =
        {.isPointer            = typePtr->isPointerType(),
         .isArray              = typePtr->isArrayType(),
         .arraySize            = arraySize,
         .isRecursiveTypeField = isRecursiveType
        };
      std::string fName = FD->getNameAsString();
      ComposableField *sf = new ComposableField(type, fName, attrib);
      sType->addStructField(sf);
    }
    structKnownType.erase(typeName);
    return sType;
  }

  TypeItf* getFromPointerType(const clang::Type &type, structKnownTypeMap &structKnownType)
  {
    const clang::Type &pointeeType = *type.getPointeeType().getTypePtr();
    TypeItf *rv = getEasyMocktype(pointeeType, structKnownType);

    return rv;
  }

  TypeItf* getFromArrayType(const clang::Type &type, structKnownTypeMap &structKnownType)
  {
    const clang::ArrayType &arrayType = *type.getAsArrayTypeUnsafe();
    const clang::Type &arrayElem = *arrayType.getElementType().getTypePtr();

    TypeItf *rv = getEasyMocktype(arrayElem, structKnownType);

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
};

class FunctionDeclASTConsumer : public clang::ASTConsumer
{
public:
  // override the constructor in order to pass CI

  explicit FunctionDeclASTConsumer(clang::CompilerInstance& ci, ElementToMock::Vector& elem)
  : clang::ASTConsumer(), m_visitor(ci.getSourceManager(), elem) { }

  virtual void HandleTranslationUnit(clang::ASTContext& astContext)
  {
    m_visitor.setAstContext(astContext);
    m_visitor.TraverseDecl(astContext.getTranslationUnitDecl());
  }
private:
  FunctionDeclASTVisitor m_visitor; // doesn't have to be private
};

class FunctionDeclFrontendAction : public clang::ASTFrontendAction
{
public:
  FunctionDeclFrontendAction(ElementToMock::Vector& elem) :
  clang::ASTFrontendAction(), m_elem(elem)
  {
  }

  virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance& CI, clang::StringRef file)
  {
    return std::make_unique<FunctionDeclASTConsumer>(CI, m_elem); // pass CI pointer to ASTConsumer
  }
private:
  ElementToMock::Vector& m_elem;
};

std::unique_ptr<clang::tooling::FrontendActionFactory> newFunctionDeclFrontendAction(ElementToMock::Vector& elem) {
  class FunctionDeclFrontendActionFactory : public clang::tooling::FrontendActionFactory {
  public:
    FunctionDeclFrontendActionFactory(ElementToMock::Vector& elem) :
    clang::tooling::FrontendActionFactory(), m_elem(elem)
    {
    }
    clang::FrontendAction *create() override { return new FunctionDeclFrontendAction(m_elem); }
  private:
    ElementToMock::Vector& m_elem;
  };

  return std::unique_ptr<clang::tooling::FrontendActionFactory>(
      new FunctionDeclFrontendActionFactory(elem));
}

LLVMParser::LLVMParser() : CodeParserItf()
{
}

LLVMParser::LLVMParser(std::string& filename, std::string& flags)  : CodeParserItf(filename, flags)
{
}

CodeParser_errCode LLVMParser::getElementToStub(ElementToMock::Vector& elem) const
{
  //std::string dir = boost::filesystem::path(m_filename).parent_path().string();
  std::string dir = ".";
  llvm::Twine twineDir(dir);
  //clang::tooling::FixedCompilationDatabase db(twineDir, {"-I/usr//lib/llvm-7/lib/clang/7.0.0/include/"});
  clang::tooling::FixedCompilationDatabase db(twineDir, {"-I/usr//lib/gcc/x86_64-linux-gnu/7/include/"});
  std::vector<std::string> arRef({m_filename});
  clang::tooling::ClangTool tool(db, arRef);
  tool.run(newFunctionDeclFrontendAction(elem).get());
  return cp_OK;
}

LLVMParser::~LLVMParser() { }

