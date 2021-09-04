#ifndef EASYMOCK_VOIDFUNALIASEDFUNFACTORY_H
#define EASYMOCK_VOIDFUNALIASEDFUNFACTORY_H

#include <FunctionFactory.h>
#include <voidFunAliasedFun.h>

class VoidFunAliasedFunFactory : public FunctionFactory<void, std::tuple<>, std::tuple<>>
{
public:
  ElementToMockList functionFactoryArray() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  ElementToMockContext::MacroDefinitionList getDefinedMacroList() override;
};

class VoidFunAliasedFunGenerateTypeFactory : public VoidFunAliasedFunFactory
{
public:
  VoidFunAliasedFunGenerateTypeFactory() { m_generate_types = true; }
};

#endif //EASYMOCK_VOIDFUNALIASEDFUNFACTORY_H
