#ifndef UNSLONGLONGFUNUNSLONGLONGFACTORY_H
#define UNSLONGLONGFUNUNSLONGLONGFACTORY_H

#include <FunctionFactory.h>
#include <easyMock.h>

class UnsLongLongFunUnsLongLongFactory : public FunctionFactory<unsigned long long, std::tuple<unsigned long long>, std::tuple<EasyMock_Matcher>>
{
public:
  FunctionDeclaration functionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  void setupTestCase(EasyMockTestCase::TestCase tc) override;

};

#endif /* UNSLONGLONGFUNUNSLONGLONGFACTORY_H */
