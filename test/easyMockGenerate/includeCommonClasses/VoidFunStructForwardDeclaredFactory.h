#ifndef VOIDFUNSTRUCTFORWARDDECLAREDFACTORY_H
#define VOIDFUNSTRUCTFORWARDDECLAREDFACTORY_H

#include <FunctionFactory.h>
#include <easyMock.h>

#include <voidFunStructForwardDeclared.h>

class VoidFunStructForwardDeclaredFactory : public FunctionFactory<void, std::tuple<struct forwardDeclaredChild>, std::tuple<EasyMock_Matcher>>
{
public:
  ElementToMockList functionFactoryArray() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;

};

class VoidFunStructForwardDeclaredGenerateTypeFactory : public VoidFunStructForwardDeclaredFactory
{
public:
  VoidFunStructForwardDeclaredGenerateTypeFactory() { m_generate_types = true; }
};

#endif /* VOIDFUNSTRUCTFORWARDDECLAREDFACTORY_H */

