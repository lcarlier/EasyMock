#ifndef CONSTINTFUNCONSTINTFACTORY_H
#define CONSTINTFUNCONSTINTFACTORY_H

#include <FunctionFactory.h>
#include <easyMock.h>

//The factory doesn't accept const but it doesn't change anything
class ConstIntFunConstIntFactory : public FunctionFactory<int, std::tuple<int>, std::tuple<EasyMock_Matcher>>
{
public:
  std::shared_ptr<FunctionDeclaration> functionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  void setupTestCase(EasyMockTestCase::TestCase tc) override;

};

#endif /* CONSTINTFUNCONSTINTFACTORY_H */
