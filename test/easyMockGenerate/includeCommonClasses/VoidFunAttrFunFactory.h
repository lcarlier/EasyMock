#ifndef EASYMOCK_VOIDFUNATTRFUNFACTORY_H
#define EASYMOCK_VOIDFUNATTRFUNFACTORY_H

#include <FunctionFactory.h>
#include <voidFunAttrFun.h>

class VoidFunAttrFunFactory : public FunctionFactory<void, std::tuple<struct s2*>, std::tuple<EasyMock_Matcher>>
{
public:
ElementToMockList functionFactoryArray() override;
std::string functionGetFunctionName() override;
std::string getFilename() override;

};

class VoidFunAttrFunGenerateTypeFactory : public VoidFunAttrFunFactory
{
public:
  VoidFunAttrFunGenerateTypeFactory() { m_generate_types = true; }
};

#endif //EASYMOCK_VOIDFUNATTRFUNFACTORY_H
