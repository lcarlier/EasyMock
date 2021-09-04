#ifndef EASYMOCK_VOIDFUNSTRUCTWITHOUTSIDEDECLAREDANONYMOUSTYPESTRUCTFIELDFACTORY_H
#define EASYMOCK_VOIDFUNSTRUCTWITHOUTSIDEDECLAREDANONYMOUSTYPESTRUCTFIELDFACTORY_H

#include <FunctionFactory.h>
#include <voidFunStructWithOutsideDeclaredAnonymousTypeStructField.h>

class VoidFunStructWithOutsideDeclaredAnonymousTypeStructFieldFactory : public FunctionFactory<void, std::tuple<struct structWithOutsideAnonymousDeclaredStruct>, std::tuple<EasyMock_Matcher>>
{
public:
  ElementToMockList functionFactoryArray() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;

};

class VoidFunStructWithOutsideDeclaredAnonymousTypeStructFieldGenerateTypeFactory : public VoidFunStructWithOutsideDeclaredAnonymousTypeStructFieldFactory
{
public:
  VoidFunStructWithOutsideDeclaredAnonymousTypeStructFieldGenerateTypeFactory() { m_generate_types = true; }
};

#endif //EASYMOCK_VOIDFUNSTRUCTWITHOUTSIDEDECLAREDANONYMOUSTYPESTRUCTFIELDFACTORY_H
