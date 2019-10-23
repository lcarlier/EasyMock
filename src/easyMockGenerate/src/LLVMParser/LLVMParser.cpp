#include "LLVMParser.h"
#include "StructType.h"

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
#include <Function.h>
#include <TypeItf.h>
#include <CType.h>

class FunctionDeclASTVisitor : public clang::RecursiveASTVisitor<FunctionDeclASTVisitor>
{
public:

  explicit FunctionDeclASTVisitor(clang::SourceManager& sm, ElementToMock::Vector& elem)
  : m_sourceManager(sm), m_elem(elem) { }

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
private:
  clang::SourceManager& m_sourceManager;
  ElementToMock::Vector& m_elem;

  ReturnValue getFunctionReturnValue(clang::FunctionDecl* func)
  {
    ReturnValue rv;
    const clang::Type* clangType = func->getReturnType().getTypePtr();
    TypeItf *type = getEasyMocktype(*clangType);
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
      TypeItf *type = getEasyMocktype(*paramType);
      vectParam.push_back(new Parameter(type, param->getNameAsString()));
    }

    return vectParam;
  }

  CType* getFromBuiltinType(const clang::Type &type)
  {
    CType *returnedType = new CType();

    if(type.isVoidType())
    {
      returnedType->setCType(CTYPE_VOID);
    }
    else if(type.isCharType())
    {
      returnedType->setCType(CTYPE_CHAR);
    }
    else if(isShortType(type))
    {
      returnedType->setCType(CTYPE_SHORT);
    }
    else if(isLongType(type))
    {
      returnedType->setCType(CTYPE_LONG);
    }
    else if(isIntType(type))
    {
      returnedType->setCType(CTYPE_INT);
    }
    else if(isLongLongType(type))
    {
      returnedType->setCType(CTYPE_LONG_LONG);
    }
    else if(isDoubleType(type))
    {
      returnedType->setCType(CTYPE_DOUBLE);
    }
    else if(isLongDoubleType(type))
    {
      returnedType->setCType(CTYPE_LONG_DOUBLE);
    }
    else if(isFloatType(type))
    {
      returnedType->setCType(CTYPE_FLOAT);
    }

    //Unsigned
    if(type.isUnsignedIntegerType())
    {
      returnedType->setUnsigned(true);
    }

    return returnedType;
  }

  TypeItf* getFromStructType(const clang::Type &type)
  {
    const clang::RecordType *RT = type.getAsStructureType();
    StructType *sType = new StructType(RT->getDecl()->getNameAsString());
    for (clang::FieldDecl *FD :
          type.getAsStructureType()->getDecl()->fields()) {
      const clang::Type *typePtr = FD->getType().getTypePtr();
      TypeItf *type = getEasyMocktype(*typePtr);
      StructField *sf = new StructField(type, FD->getNameAsString());
      sType->addStructField(sf);
    }
    return sType;
  }

  TypeItf* getEasyMocktype(const clang::Type &clangType)
  {
    TypeItf *type = nullptr;
    if(clangType.isBuiltinType())
    {
      type = getFromBuiltinType(clangType);
    }
    else if(clangType.isStructureType())
    {
      type = getFromStructType(clangType);
    }

    return type;
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
};

class FunctionDeclASTConsumer : public clang::ASTConsumer
{
public:
  // override the constructor in order to pass CI

  explicit FunctionDeclASTConsumer(clang::CompilerInstance& ci, ElementToMock::Vector& elem)
  : clang::ASTConsumer(), m_visitor(ci.getSourceManager(), elem) { }

  virtual void HandleTranslationUnit(clang::ASTContext& astContext)
  {
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
  std::string dir = boost::filesystem::path(m_filename).parent_path().string();
  llvm::Twine twineDir(dir);
  clang::tooling::FixedCompilationDatabase db(twineDir, m_flags);
  std::vector<std::string> arRef({m_filename});
  clang::tooling::ClangTool tool(db, arRef);
  tool.run(newFunctionDeclFrontendAction(elem).get());
  return cp_OK;
}

LLVMParser::~LLVMParser() { }

