#ifndef VOIDFUNSTRUCTWITHFIRSTANONYMOUSSTRUCTFIELDFACTORY_H
#define VOIDFUNSTRUCTWITHFIRSTANONYMOUSSTRUCTFIELDFACTORY_H

#include <FunctionFactory.h>
#include <voidFunStructWithFirstAnonymousStructField.h>

class VoidFunStructWithFirstAnonymousStructFieldFactory : public FunctionFactory<void, std::tuple<struct topAnonymousFirstStructField>, std::tuple<EasyMock_Matcher>>
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

#endif /* VOIDFUNSTRUCTWITHFIRSTANONYMOUSSTRUCTFIELDFACTORY_H */

