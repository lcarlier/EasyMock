#include <VoidFunStructWithOutsideDeclaredAnonymousTypeStructFieldFactory.h>

#include <FunctionDeclaration.h>
#include <StructType.h>
#include <ComposableField.h>
#include <TypedefType.h>
#include <EasyMock_CType.h>
#include <Pointer.h>

ElementToMockList VoidFunStructWithOutsideDeclaredAnonymousTypeStructFieldFactory::functionFactoryArray()
{
  auto getSwo=[]()
  {
    auto ul = std::make_shared<CType>(CTYPE_ULONG);
    auto sval_t = std::make_shared<TypedefType>("sval_t", ul);
    auto structAnonymous_val_t = std::make_shared<StructType>("", false);
    structAnonymous_val_t->addField(ComposableField{std::move(sval_t), "val"});
    auto val_t = std::make_shared<TypedefType>("val_t", structAnonymous_val_t);

    auto innerAnonymousStruct = std::make_shared<StructType>("", true);
    innerAnonymousStruct->addField(ComposableField{std::make_shared<Pointer>(val_t), "o"});
    auto swo = std::make_shared<StructType>("structWithOutsideAnonymousDeclaredStruct", false);
    swo->addField(ComposableField{std::move(innerAnonymousStruct), ""});

    return swo;
  };
  ElementToMockList returnedList;
  {
    Parameter::Vector pv{};
    pv.emplace_back(Parameter{getSwo(), "s"});
    auto f = std::make_shared<FunctionDeclaration>(functionGetFunctionName(), VoidReturnValue(), std::move(pv));
    returnedList.push_back(std::move(f));
  }
  {
    auto f = std::make_shared<FunctionDeclaration>("structWithOutsideAnonymousDeclaredStructFunVoid", ReturnValue(getSwo()),
                                                     Parameter::Vector {});
    returnedList.push_back(std::move(f));
  }
  return returnedList;
}

std::string VoidFunStructWithOutsideDeclaredAnonymousTypeStructFieldFactory::functionGetFunctionName()
{
  return std::string("voidFunStructWithOutsideDeclaredAnonymousTypeStructField");
}

std::string VoidFunStructWithOutsideDeclaredAnonymousTypeStructFieldFactory::getFilename()
{
  return "voidFunStructWithOutsideDeclaredAnonymousTypeStructField.h";
}
