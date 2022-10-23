#include <VoidFunTypeDefFactory.h>

#include <EasyMock_CType.h>
#include <FunctionDeclaration.h>
#include <Pointer.h>
#include <ConstQualifiedType.h>
#include <TypedefType.h>

ElementToMockList VoidFunTypeDefFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  auto cIntType = std::make_shared<ConstQualifiedType>( std::make_shared<CType>(CTYPE_INT) );
  auto p = std::make_shared<TypedefType>( "CMyType1", std::make_shared<Pointer>(std::move(cIntType)));
  {
    auto intType = std::make_shared<TypedefType>( "MyType1", std::make_shared<CType>(CTYPE_INT) );
    auto floatType1 = std::make_shared<TypedefType>( "MyType2", std::make_shared<CType>(CTYPE_FLOAT) );
    auto floatType2 = std::make_shared<TypedefType>( "MyType3", std::make_shared<CType>(CTYPE_FLOAT) );
    auto myType4Type = std::make_shared<Pointer>(std::make_shared<ConstQualifiedType>(std::make_shared<TypedefType>("MyType4", std::make_shared<CType>(CTYPE_SHORT))));
    Parameter::Vector pv{};
    pv.emplace_back(Parameter(std::move(intType), "p1"));
    pv.emplace_back(Parameter(std::move(floatType1), "p2"));
    pv.emplace_back(Parameter(std::move(floatType2), "p3"));
    pv.emplace_back(Parameter(p, "p4")); //!! dont move this one! it is used by the second function !!
    pv.emplace_back(Parameter(std::move(myType4Type), "p5"));
    auto fd = std::make_shared<FunctionDeclaration>(functionGetFunctionName(), VoidReturnValue(false), std::move(pv));
    returnedList.push_back(std::move(fd));
  }

  {
    ReturnValue rv(p);
    auto fd = std::make_shared<FunctionDeclaration>("ptypedefFunVoid", std::move(rv), Parameter::Vector {});
    returnedList.push_back(std::move(fd));
  }
  return returnedList;
}

std::string VoidFunTypeDefFactory::functionGetFunctionName()
{
  return std::string("voidFunTypeDef");
}

std::string VoidFunTypeDefFactory::getFilename()
{
  return "voidFunTypeDef.h";
}
