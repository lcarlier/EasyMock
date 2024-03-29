#ifndef UNSCHARFUNUNSCHARFACTORY_H
#define UNSCHARFUNUNSCHARFACTORY_H

#include <FunctionFactory.h>
#include <easyMock.h>

class UnsCharFunUnsCharFactory : public FunctionFactory<unsigned char, std::tuple<unsigned char>, std::tuple<EasyMock_Matcher>>
{
public:
  std::shared_ptr<FunctionDeclaration> functionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  void setupTestCase(EasyMockTestCase::TestCase tc) override;

};

#endif /* UNSCHARFUNUNSCHARFACTORY_H */
