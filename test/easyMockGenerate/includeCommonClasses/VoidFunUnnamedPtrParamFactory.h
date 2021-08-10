#ifndef EASYMOCK_VOIDFUNUNNAMEDPTRPARAMFACTORY_H
#define EASYMOCK_VOIDFUNUNNAMEDPTRPARAMFACTORY_H

#include <FunctionFactory.h>
#include <voidFunUnnamedPtrParam.h>

class VoidFunUnnamedPtrParamFactory : public FunctionFactory<void, std::tuple<int, const char *, int>, std::tuple<EasyMock_Matcher, EasyMock_Matcher, EasyMock_Matcher>>
    {
    public:
      ElementToMockList functionFactoryArray() override;
      std::string functionGetFunctionName() override;
      std::string getFilename() override;

    };

class VoidFunUnnamedPtrParamGenerateTypeFactory : public VoidFunUnnamedPtrParamFactory
    {
    public:
      VoidFunUnnamedPtrParamGenerateTypeFactory() { m_generate_types = true; }
    };

#endif //EASYMOCK_VOIDFUNUNNAMEDPTRPARAMFACTORY_H
