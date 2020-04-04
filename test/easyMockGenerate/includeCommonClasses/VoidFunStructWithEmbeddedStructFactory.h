#ifndef VOIDFUNSTRUCTWITHEMBEDDEDSTRUCTFACTORY_H
#define VOIDFUNSTRUCTWITHEMBEDDEDSTRUCTFACTORY_H

#include <FunctionFactory.h>
#include <voidFunStructWithEmbeddedStruct.h>

class VoidFunStructWithEmbeddedStructFactory : public FunctionFactory<int, std::tuple<struct topEmbedded>, std::tuple<EasyMock_Matcher>>
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

#endif /* VOIDFUNSTRUCTWITHEMBEDDEDSTRUCTFACTORY_H */

