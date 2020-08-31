#ifndef VOIDFUNENUMFACTORY_H
#define VOIDFUNENUMFACTORY_H

#include <FunctionFactory.h>
#include <easyMock.h>

#include <voidFunEnum.h>

class VoidFunEnumFactory : public FunctionFactory<int, std::tuple<void*>, std::tuple<EasyMock_Matcher>>
{
public:
  ElementToMockList functionFactoryArray() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;

};

#endif /* VOIDFUNENUMFACTORY_H */
