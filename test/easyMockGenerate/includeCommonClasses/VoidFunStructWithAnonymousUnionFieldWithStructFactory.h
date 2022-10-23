#ifndef EASYMOCK_VOIDFUNSTRUCTWITHANONYMOUSUNIONFIELDWITHSTRUCTFACTORY_H
#define EASYMOCK_VOIDFUNSTRUCTWITHANONYMOUSUNIONFIELDWITHSTRUCTFACTORY_H

#include <FunctionFactory.h>
#include <voidFunStructWithAnonymousUnionFieldWithStruct.h>

class VoidFunStructWithAnonymousUnionFieldWithStructFactory : public FunctionFactory<void, std::tuple<structWithUnionFieldWithStruct>, std::tuple<EasyMock_Matcher>>
{
public:
  std::shared_ptr<FunctionDeclaration> functionFactory() override;
  ElementToMockList functionFactoryArray() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;

  void setupTestCase(EasyMockTestCase::TestCase tc) override;
  std::string getMatcherFunctionName() override;
  std::string getFieldWrongName() override;
  std::string getSubComposableTypeType() override;
  std::string getSubFieldWrongTypeName() override;
  std::string getSubFieldWrongName() override;
};

class VoidFunStructWithAnonymousUnionFieldWithStructGenerateTypeFactory : public VoidFunStructWithAnonymousUnionFieldWithStructFactory
{
public:
  VoidFunStructWithAnonymousUnionFieldWithStructGenerateTypeFactory() { m_generate_types = true; }
};

#endif //EASYMOCK_VOIDFUNSTRUCTWITHANONYMOUSUNIONFIELDWITHSTRUCTFACTORY_H
