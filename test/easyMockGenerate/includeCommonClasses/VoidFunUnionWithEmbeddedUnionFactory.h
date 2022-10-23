#ifndef VOIDFUNUNIONWITHEMBEDDEDUNIONFACTORY_H
#define VOIDFUNUNIONWITHEMBEDDEDUNIONFACTORY_H

#include <FunctionFactory.h>
#include <voidFunUnionWithEmbeddedUnion.h>

class VoidFunUnionWithEmbeddedUnionFactory : public FunctionFactory<void, std::tuple<union topEmbeddedUnion>, std::tuple<EasyMock_Matcher>>
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

class VoidFunUnionWithEmbeddedUnionGenerateTypeFactory : public VoidFunUnionWithEmbeddedUnionFactory
{
public:
  VoidFunUnionWithEmbeddedUnionGenerateTypeFactory() { m_generate_types = true; }
};

#endif /* VOIDFUNUNIONWITHEMBEDDEDUNIONFACTORY_H */
