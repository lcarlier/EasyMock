#ifndef EASYMOCK_VOIDFUNSTRUCTCOMPLETEFIELDFACTORY_H
#define EASYMOCK_VOIDFUNSTRUCTCOMPLETEFIELDFACTORY_H

#include <FunctionFactory.h>
#include <easyMock.h>
#include <voidFunStructCompleteField.h>

class VoidFunStructCompleteFieldFactory : public FunctionFactory<void, std::tuple<struct forwardStruct*>, std::tuple<EasyMock_Matcher>>
{
public:
  FunctionDeclaration functionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;

};

class VoidFunStructCompleteFieldGenerateTypeFactory : public VoidFunStructCompleteFieldFactory
{
public:
  VoidFunStructCompleteFieldGenerateTypeFactory() { m_generate_types = true; }
};

#endif //EASYMOCK_VOIDFUNSTRUCTCOMPLETEFIELDFACTORY_H
