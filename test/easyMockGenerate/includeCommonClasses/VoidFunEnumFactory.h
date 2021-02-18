#ifndef VOIDFUNENUMFACTORY_H
#define VOIDFUNENUMFACTORY_H

#include <FunctionFactory.h>
#include <easyMock.h>

#include <voidFunEnum.h>

class VoidFunEnumFactory : public FunctionFactory<void, std::tuple<void*>, std::tuple<EasyMock_Matcher>>
{
public:
  ElementToMockList functionFactoryArray() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;

};

class VoidFunEnumGenerateTypeFactory : public VoidFunEnumFactory{
  VoidFunEnumGenerateTypeFactory() { m_generate_types = true; }
};

#endif /* VOIDFUNENUMFACTORY_H */

