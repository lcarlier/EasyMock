#ifndef VOIDFUNTYPEDEFFACTORY_H
#define VOIDFUNTYPEDEFFACTORY_H

#include <FunctionFactory.h>
#include <voidFunTypeDef.h>

class VoidFunTypeDefFactory: public FunctionFactory<void, std::tuple<MyType1, MyType2, MyType3>, std::tuple<EasyMock_Matcher, EasyMock_Matcher, EasyMock_Matcher>>
{
public:
  ElementToMockList functionFactoryArray() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;

};

#endif /* VOIDFUNTYPEDEFFACTORY_H */

