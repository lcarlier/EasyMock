#ifndef TEST_VOIDFUNVOID_H
#define TEST_VOIDFUNVOID_H

#include <FunctionFactory.h>

class VoidFunVoidFactory : public FunctionFactory<int, std::tuple<>, std::tuple<>> //return value is void but do not care since we do not use it
{
public:
  FunctionDeclaration functionFactory() override;
  FunctionDeclaration* newFunctionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  void setupTestCase(EasyMockTestCase::TestCase tc) override;

};

#endif /* TEST_VOIDFUNVOID_H */

