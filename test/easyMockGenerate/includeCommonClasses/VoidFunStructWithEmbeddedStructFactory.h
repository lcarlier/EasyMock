#ifndef VOIDFUNSTRUCTWITHEMBEDDEDSTRUCTFACTORY_H
#define VOIDFUNSTRUCTWITHEMBEDDEDSTRUCTFACTORY_H

#include <FunctionFactory.h>
#include <voidFunStructWithEmbeddedStruct.h>

class VoidFunStructWithEmbeddedStructFactory : public FunctionFactory<void, std::tuple<struct topEmbedded>, std::tuple<EasyMock_Matcher>>
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

class VoidFunStructWithEmbeddedStructGenerateTypeFactory : public VoidFunStructWithEmbeddedStructFactory
{
public:
  VoidFunStructWithEmbeddedStructGenerateTypeFactory() { m_generate_types = true; }
};

#endif /* VOIDFUNSTRUCTWITHEMBEDDEDSTRUCTFACTORY_H */

