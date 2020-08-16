#ifndef VOIDFUNSTRUCTWITHANONYMOUSSTRUCTFIELDFACTORY_H
#define VOIDFUNSTRUCTWITHANONYMOUSSTRUCTFIELDFACTORY_H

#include <FunctionFactory.h>
#include <voidFunStructWithAnonymousStructField.h>

class VoidFunStructWithAnonymousStructFieldFactory : public FunctionFactory<int, std::tuple<struct topAnonymousStructField>, std::tuple<EasyMock_Matcher>>
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

#endif /* VOIDFUNSTRUCTWITHANONYMOUSSTRUCTFIELDFACTORY_H */

