#ifndef LONGLONGFUNLONGLONGFACTORY_H
#define LONGLONGFUNLONGLONGFACTORY_H

#include <FunctionFactory.h>
#include <easyMock.h>

class LongLongFunLongLongFactory : public FunctionFactory<long long, std::tuple<long long>, std::tuple<EasyMock_Matcher>>
{
public:
  FunctionDeclaration functionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  void setupTestCase(EasyMockTestCase::TestCase tc) override;

};

#endif /* LONGLONGFUNLONGLONGFACTORY_H */
