#ifndef VOIDFUNSTRUCTWITHEMBEDDEDANONYMOUSSTRUCTFACTORY_H
#define VOIDFUNSTRUCTWITHEMBEDDEDANONYMOUSSTRUCTFACTORY_H

#include <FunctionFactory.h>
#include <voidFunStructWithEmbeddedAnonymousStruct.h>

class VoidFunStructWithEmbeddedAnonymousStructFactory : public FunctionFactory<void, std::tuple<struct topEmbeddedAnonymous>, std::tuple<EasyMock_Matcher>>
{
public:
  std::shared_ptr<FunctionDeclaration> functionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  std::string getMatcherFunctionName() override;
  std::string getFieldWrongName() override;
  std::string getSubFieldWrongName() override;
  std::string getSubFieldWrongTypeName() override;
  std::string getSubComposableTypeType() override;

  void setupTestCase(EasyMockTestCase::TestCase tc) override;

};

class VoidFunStructWithEmbeddedAnonymousStructGenerateTypeFactory : public VoidFunStructWithEmbeddedAnonymousStructFactory
{
public:
  VoidFunStructWithEmbeddedAnonymousStructGenerateTypeFactory() { m_generate_types = true; }
};

#endif /* VOIDFUNSTRUCTWITHEMBEDDEDANONYMOUSSTRUCTFACTORY_H */
