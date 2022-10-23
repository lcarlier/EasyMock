#ifndef VOIDFUNUNIONWITHANONYMOUSUNIONFIELDFACTORY_H
#define VOIDFUNUNIONWITHANONYMOUSUNIONFIELDFACTORY_H

#include <FunctionFactory.h>
#include <voidFunUnionWithAnonymousUnionField.h>

class VoidFunUnionWithAnonymousUnionFieldFactory : public FunctionFactory<void, std::tuple<union topAnonymousUnionField>, std::tuple<EasyMock_Matcher>>
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

class VoidFunUnionWithAnonymousUnionFieldGenerateTypeFactory : public VoidFunUnionWithAnonymousUnionFieldFactory
{
public:
  VoidFunUnionWithAnonymousUnionFieldGenerateTypeFactory() { m_generate_types = true; }
};

#endif /* VOIDFUNUNIONWITHANONYMOUSUNIONFIELDFACTORY_H */
