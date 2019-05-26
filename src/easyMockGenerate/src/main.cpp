#include "CodeGeneratorCTemplate.h"
#include "CodeParserCLang.h"
#include "MainCodeGenerator.h"

class OneFun : public CodeParserItf
{
public:
  OneFun():CodeParserItf(){}
  CodeParser_errCode getElementToStub(ElementToMockVector& elem) const
  {
    Function *f = new Function("function", "void", {});
    elem.push_back(f);

    return cp_OK;
  }
};

int main(int argc, char *argv[])
{
  OneFun of;
  CodeGeneratorCTemplate cg;
  MainCodeGenerator cp("myHeader.h", of, cg);
  cp.generateCode("out");

  return 0;
}
