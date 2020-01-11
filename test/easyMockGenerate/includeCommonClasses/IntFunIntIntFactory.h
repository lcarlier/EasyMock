#ifndef INTFUNINTINTFACTORY_H
#define INTFUNINTINTFACTORY_H

#include <FunctionFactory.h>
#include <easyMock.h>

class IntFunIntIntFactory : public FunctionFactory<int, std::tuple<int, int>, std::tuple<EasyMock_Matcher, EasyMock_Matcher>>
{
public:
  Function functionFactory() override;
  Function* newFunctionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  void setupTestCase(EasyMockTestCase::TestCase tc) override;

};

#endif /* INTFUNINTINTFACTORY_H */

