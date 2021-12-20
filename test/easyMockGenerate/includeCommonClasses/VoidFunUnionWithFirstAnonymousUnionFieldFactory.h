#ifndef VOIDFUNUNIONWITHFIRSTANONYMOUSUNIONFIELDFACTORY_H
#define VOIDFUNUNIONWITHFIRSTANONYMOUSUNIONFIELDFACTORY_H

#include <FunctionFactory.h>
#include <voidFunUnionWithFirstAnonymousUnionField.h>

class VoidFunUnionWithFirstAnonymousUnionFieldFactory : public FunctionFactory<void, std::tuple<union topAnonymousFirstUnionField>, std::tuple<EasyMock_Matcher>>
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

class VoidFunUnionWithFirstAnonymousUnionFieldGenerateTypeFactory : public VoidFunUnionWithFirstAnonymousUnionFieldFactory
{
public:
  VoidFunUnionWithFirstAnonymousUnionFieldGenerateTypeFactory() { m_generate_types = true; }
};

#endif /* VOIDFUNUNIONWITHFIRSTANONYMOUSUNIONFIELDFACTORY_H */
