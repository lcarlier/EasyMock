#ifndef VOIDFUNSTRUCTWITHEMBEDDEDANONYMOUSSTRUCTFACTORY_H
#define VOIDFUNSTRUCTWITHEMBEDDEDANONYMOUSSTRUCTFACTORY_H

#include <FunctionFactory.h>
#include <voidFunStructWithEmbeddedAnonymousStruct.h>

class VoidFunStructWithEmbeddedAnonymousStructFactory : public FunctionFactory<int, std::tuple<struct topEmbeddedAnonymous>, std::tuple<EasyMock_Matcher>>
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

#endif /* VOIDFUNSTRUCTWITHEMBEDDEDANONYMOUSSTRUCTFACTORY_H */

