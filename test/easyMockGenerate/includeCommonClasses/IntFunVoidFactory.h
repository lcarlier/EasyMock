#ifndef INTFUNVOIDFACTORY_H
#define INTFUNVOIDFACTORY_H

#include <FunctionFactory.h>

class IntFunVoidFactory : public FunctionFactory<int, std::tuple<>, std::tuple<>>
{
public:
  FunctionDeclaration functionFactory() override;
  FunctionDeclaration* newFunctionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  void setupTestCase(EasyMockTestCase::TestCase tc) override;
};

#endif /* INTFUNVOIDFACTORY_H */

