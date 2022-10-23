#ifndef UNSINTFUNUNSINTINTFACTORY_H
#define UNSINTFUNUNSINTINTFACTORY_H

#include <FunctionFactory.h>
#include <easyMock.h>

class UnsIntFunUnsIntIntFactory : public FunctionFactory<unsigned int, std::tuple<unsigned int, int>, std::tuple<EasyMock_Matcher, EasyMock_Matcher>>
{
public:
  std::shared_ptr<FunctionDeclaration> functionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  void setupTestCase(EasyMockTestCase::TestCase tc) override;

};

#endif /* UNSINTFUNUNSINTINTFACTORY_H */
