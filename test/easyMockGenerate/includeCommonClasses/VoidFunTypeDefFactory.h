#ifndef VOIDFUNTYPEDEFFACTORY_H
#define VOIDFUNTYPEDEFFACTORY_H

#include <FunctionFactory.h>
#include <voidFunTypeDef.h>

class VoidFunTypeDefFactory: public FunctionFactory<void, std::tuple<MyType1, MyType2, MyType3, CMyType1, const MyType4*>, std::tuple<EasyMock_Matcher, EasyMock_Matcher, EasyMock_Matcher, EasyMock_Matcher, EasyMock_Matcher>>
{
public:
  ElementToMockList functionFactoryArray() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;

};

class VoidFunTypeDefGenerateTypeFactory : public VoidFunTypeDefFactory
{
public:
  VoidFunTypeDefGenerateTypeFactory() { m_generate_types = true; }
};

#endif /* VOIDFUNTYPEDEFFACTORY_H */

