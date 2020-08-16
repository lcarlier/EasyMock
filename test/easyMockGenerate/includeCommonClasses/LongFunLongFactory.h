#ifndef LONGFUNLONGFACTORY_H
#define LONGFUNLONGFACTORY_H

#include <FunctionFactory.h>

class LongFunLongFactory : public FunctionFactory<long, std::tuple<long>, std::tuple<EasyMock_Matcher>>
{
public:
  FunctionDeclaration functionFactory() override;
  FunctionDeclaration* newFunctionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  void setupTestCase(EasyMockTestCase::TestCase tc) override;

};

#endif /* LONGFUNLONGFACTORY_H */

