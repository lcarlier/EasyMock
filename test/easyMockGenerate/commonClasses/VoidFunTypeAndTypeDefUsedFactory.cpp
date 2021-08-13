#include <VoidFunTypeAndTypeDefUsedFactory.h>

#include <FunctionDeclaration.h>
#include <StructType.h>
#include <ComposableField.h>
#include <TypedefType.h>
#include <Pointer.h>

ElementToMockList VoidFunTypeAndTypeDefUsedFactory::functionFactoryArray()
{
  ElementToMockList returnedList;

  StructType s{"notTypedefUsed", false};
  s.addField(new ComposableField{CTYPE_INT, "a"});
  {
    TypedefType *t = new TypedefType{"typedefUsed", new Pointer{s.clone()}};
    FunctionDeclaration *fd = new FunctionDeclaration("voidFunTypeDefUsed", VoidReturnValue(), Parameter::Vector({new Parameter{t, "t"}}));
    returnedList.push_back(fd);
  }
  {
    FunctionDeclaration *fd = new FunctionDeclaration(functionGetFunctionName(), VoidReturnValue(), Parameter::Vector({new Parameter(s.clone(), "s")}));
    returnedList.push_back(fd);
  }
  return returnedList;
}

std::string VoidFunTypeAndTypeDefUsedFactory::functionGetFunctionName()
{
  return std::string("voidFunTypeAndTypeDefUsed");
}

std::string VoidFunTypeAndTypeDefUsedFactory::getFilename()
{
  return "voidFunTypeAndTypeDefUsed.h";
}
