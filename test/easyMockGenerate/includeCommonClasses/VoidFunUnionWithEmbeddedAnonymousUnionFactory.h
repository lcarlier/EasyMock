#ifndef VOIDFUNUNIONWITHEMBEDDEDANONYMOUSUNIONFACTORY_H
#define VOIDFUNUNIONWITHEMBEDDEDANONYMOUSUNIONFACTORY_H

#include <FunctionFactory.h>
#include <voidFunUnionWithEmbeddedAnonymousUnion.h>

class VoidFunUnionWithEmbeddedAnonymousUnionFactory : public FunctionFactory<int, std::tuple<union topEmbeddedAnonymousUnion>, std::tuple<EasyMock_Matcher>>
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

#endif /* VOIDFUNUNIONWITHEMBEDDEDANONYMOUSUNIONFACTORY_H */

