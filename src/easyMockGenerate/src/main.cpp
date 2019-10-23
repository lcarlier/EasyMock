#include <CodeGeneratorCTemplate.h>
#include "CodeParserCLang.h"
#include "MainCodeGenerator.h"
#include "Function.h"

class OneFun : public CodeParserItf
{
public:
  OneFun():CodeParserItf(){}
  CodeParser_errCode getElementToStub(ElementToMock::Vector& elem) const
  {
    ElementToMock *f  = new Function("function", VoidReturnValue(), {});
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
