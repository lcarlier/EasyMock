#ifndef VOIDFUNUNIONWITHANONYMOUSUNIONFIELDFACTORY_H
#define VOIDFUNUNIONWITHANONYMOUSUNIONFIELDFACTORY_H

#include <FunctionFactory.h>
#include <voidFunUnionWithAnonymousUnionField.h>

class VoidFunUnionWithAnonymousUnionFieldFactory : public FunctionFactory<int, std::tuple<union topAnonymousUnionField>, std::tuple<EasyMock_Matcher>>
{
public:
  Function functionFactory() override;
  Function* newFunctionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  std::string getMatcherFunctionName() override;
  std::string getFieldWrongName() override;
  std::string getSubFieldWrongName() override;
  std::string getSubFieldWrongTypeName() override;
  std::string getSubComposableTypeType() override;

  void setupTestCase(EasyMockTestCase::TestCase tc) override;

};

#endif /* VOIDFUNUNIONWITHANONYMOUSUNIONFIELDFACTORY_H */

