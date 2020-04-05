#ifndef VOIDFUNUNIONWITHFIRSTANONYMOUSUNIONFIELDFACTORY_H
#define VOIDFUNUNIONWITHFIRSTANONYMOUSUNIONFIELDFACTORY_H

#include <FunctionFactory.h>
#include <voidFunUnionWithFirstAnonymousUnionField.h>

class VoidFunUnionWithFirstAnonymousUnionFieldFactory : public FunctionFactory<int, std::tuple<union topAnonymousFirstUnionField>, std::tuple<EasyMock_Matcher>>
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

#endif /* VOIDFUNUNIONWITHFIRSTANONYMOUSUNIONFIELDFACTORY_H */

