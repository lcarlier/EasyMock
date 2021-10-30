#ifndef EASYMOCK_VOIDFUNSTRUCTFORWARDDECLANDEMPTYSTRUCTFACTORY_H
#define EASYMOCK_VOIDFUNSTRUCTFORWARDDECLANDEMPTYSTRUCTFACTORY_H

#include <FunctionFactory.h>
#include <voidFunStructForwardDeclAndEmptyStruct.h>

class VoidFunStructForwardDeclAndEmptyStructFactory : public FunctionFactory<void, std::tuple<struct funStructForwardDecl*, struct funStructEmptyStruct>, std::tuple<EasyMock_Matcher, EasyMock_Matcher>>
{
public:
  ElementToMockList functionFactoryArray() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;

};

class VoidFunStructForwardDeclAndEmptyStructGenerateTypeFactory : public VoidFunStructForwardDeclAndEmptyStructFactory
{
public:
  VoidFunStructForwardDeclAndEmptyStructGenerateTypeFactory() { m_generate_types = true; }
};

#endif //EASYMOCK_VOIDFUNSTRUCTFORWARDDECLANDEMPTYSTRUCTFACTORY_H
