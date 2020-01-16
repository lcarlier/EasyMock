#ifndef SHORTFUNSHORTFACTORY_H
#define SHORTFUNSHORTFACTORY_H

#include <FunctionFactory.h>
#include <easyMock.h>

class ShortFunShortFactory : public FunctionFactory<short, std::tuple<short>, std::tuple<EasyMock_Matcher>>
{
public:
  Function functionFactory() override;
  Function* newFunctionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  void setupTestCase(EasyMockTestCase::TestCase tc) override;

};

#endif /* SHORTFUNSHORTFACTORY_H */
