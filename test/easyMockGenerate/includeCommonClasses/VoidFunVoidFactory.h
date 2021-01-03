#ifndef TEST_VOIDFUNVOID_H
#define TEST_VOIDFUNVOID_H

#include <FunctionFactory.h>

class VoidFunVoidFactory : public FunctionFactory<void, std::tuple<>, std::tuple<>>
{
public:
  FunctionDeclaration functionFactory() override;
  FunctionDeclaration* newFunctionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  void setupTestCase(EasyMockTestCase::TestCase tc) override;

};

#endif /* TEST_VOIDFUNVOID_H */

