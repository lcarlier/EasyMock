#include <VoidFunTypeAndTypeDefUsedFactory.h>

#include <FunctionDeclaration.h>
#include <StructType.h>
#include <ComposableField.h>
#include <TypedefType.h>
#include <Pointer.h>

ElementToMockList VoidFunTypeAndTypeDefUsedFactory::functionFactoryArray()
{
  auto getNotTypedefUsed=[]()
  {
    auto s = std::make_shared<StructType>("notTypedefUsed", false);
    s->addField(ComposableField{CTYPE_INT, "a"});

    return s;
  };
  ElementToMockList returnedList;

  {
    auto t = std::make_shared<TypedefType>("typedefUsed", std::make_shared<Pointer>(getNotTypedefUsed()));
    Parameter::Vector pv{};
    pv.emplace_back(Parameter{std::move(t), "t"});
    FunctionDeclaration fd("voidFunTypeDefUsed", VoidReturnValue(), std::move(pv));
    returnedList.push_back(std::move(fd));
  }
  {
    Parameter::Vector pv{};
    pv.emplace_back(Parameter(getNotTypedefUsed(), "s"));
    FunctionDeclaration fd(functionGetFunctionName(), VoidReturnValue(), std::move(pv));
    returnedList.push_back(std::move(fd));
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
