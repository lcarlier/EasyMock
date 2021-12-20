#ifndef VOIDFUNUNIONWITHEMBEDDEDANONYMOUSUNIONFACTORY_H
#define VOIDFUNUNIONWITHEMBEDDEDANONYMOUSUNIONFACTORY_H

#include <FunctionFactory.h>
#include <voidFunUnionWithEmbeddedAnonymousUnion.h>

class VoidFunUnionWithEmbeddedAnonymousUnionFactory : public FunctionFactory<void, std::tuple<union topEmbeddedAnonymousUnion>, std::tuple<EasyMock_Matcher>>
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

class VoidFunUnionWithEmbeddedAnonymousUnionGenerateTypeFactory : public VoidFunUnionWithEmbeddedAnonymousUnionFactory
{
public:
  VoidFunUnionWithEmbeddedAnonymousUnionGenerateTypeFactory() { m_generate_types = true; }
};

#endif /* VOIDFUNUNIONWITHEMBEDDEDANONYMOUSUNIONFACTORY_H */
