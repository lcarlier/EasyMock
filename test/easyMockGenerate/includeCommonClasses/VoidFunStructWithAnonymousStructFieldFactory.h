#ifndef VOIDFUNSTRUCTWITHANONYMOUSSTRUCTFIELDFACTORY_H
#define VOIDFUNSTRUCTWITHANONYMOUSSTRUCTFIELDFACTORY_H

#include <FunctionFactory.h>
#include <voidFunStructWithAnonymousStructField.h>

class VoidFunStructWithAnonymousStructFieldFactory : public FunctionFactory<void, std::tuple<struct topAnonymousStructField>, std::tuple<EasyMock_Matcher>>
{
public:
  FunctionDeclaration functionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  std::string getMatcherFunctionName() override;
  std::string getFieldWrongName() override;
  std::string getSubFieldWrongName() override;
  std::string getSubFieldWrongTypeName() override;
  std::string getSubComposableTypeType() override;

  void setupTestCase(EasyMockTestCase::TestCase tc) override;

};

class VoidFunStructWithAnonymousStructFieldGenerateTypeFactory : public VoidFunStructWithAnonymousStructFieldFactory
{
public:
  VoidFunStructWithAnonymousStructFieldGenerateTypeFactory() { m_generate_types = true; }
};

#endif /* VOIDFUNSTRUCTWITHANONYMOUSSTRUCTFIELDFACTORY_H */
