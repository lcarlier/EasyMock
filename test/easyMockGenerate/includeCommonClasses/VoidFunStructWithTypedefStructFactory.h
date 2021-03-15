#ifndef VOIDFUNSTRUCTWITHTYPEDEFSTRUCTFACTORY_H
#define VOIDFUNSTRUCTWITHTYPEDEFSTRUCTFACTORY_H

#include <FunctionFactory.h>
#include <voidFunStructWithTypedefStruct.h>

class VoidFunStructWithTypedefStructFactory : public FunctionFactory<void, std::tuple<t_struct>, std::tuple<EasyMock_Matcher>>
{
public:
  FunctionDeclaration functionFactory() override;
  FunctionDeclaration* newFunctionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  std::string getMatcherFunctionName() override;
  std::string getFieldWrongName() override;
  std::string getSubFieldWrongName() override;
  std::string getSubFieldWrongTypeName() override;
  std::string getSubComposableTypeType() override;

  void setupTestCase(EasyMockTestCase::TestCase tc) override;

};

class VoidFunStructWithTypedefStructGenerateTypeFactory : public VoidFunStructWithTypedefStructFactory
{
public:
  VoidFunStructWithTypedefStructGenerateTypeFactory() { m_generate_types = true; }
};

#endif /* VOIDFUNSTRUCTWITHTYPEDEFSTRUCT_H */
