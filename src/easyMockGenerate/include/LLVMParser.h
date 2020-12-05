/*! \file
 * \brief Contains the implementation of the parser using LLVM.
 */
#ifndef LLVMPARSER_H
#define LLVMPARSER_H

#include "CodeParserItf.h"

/*!
 * \brief The implementation of the parser using LLVM.
 *
 * Each function is parsed accordingly by the callback function
 * FunctionDeclASTVisitor::VisitFunctionDecl(clang::FunctionDecl*).
 */
class LLVMParser : public CodeParserItf
{
public:
  LLVMParser();
  LLVMParser(std::string &filename, ParserExtraArgs& flags);
  CodeParser_errCode getElementToMockContext(ElementToMockContext& p_ctxt) const override;
  virtual ~LLVMParser();
private:
};

#endif /* LLVMPARSER_H */

