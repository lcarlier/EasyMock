#ifndef UNSLONGFUNUNSLONGFACTORY_H
#define UNSLONGFUNUNSLONGFACTORY_H

#include <FunctionFactory.h>
#include <easyMock.h>

class UnsLongFunUnsLongFactory : public FunctionFactory<unsigned long, std::tuple<unsigned long>, std::tuple<EasyMock_Matcher>>
{
public:
  std::shared_ptr<FunctionDeclaration> functionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  void setupTestCase(EasyMockTestCase::TestCase tc) override;

};

#endif /* UNSLONGFUNUNSLONGFACTORY_H */
