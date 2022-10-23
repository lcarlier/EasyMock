#ifndef TEST_CHARFUNCHAR_H
#define TEST_CHARFUNCHAR_H

#include <FunctionFactory.h>
#include <easyMock.h>

class CharFunCharFactory : public FunctionFactory<char, std::tuple<char>, std::tuple<EasyMock_Matcher>>
{
public:
  std::shared_ptr<FunctionDeclaration> functionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  void setupTestCase(EasyMockTestCase::TestCase tc) override;

};

#endif /* TEST_CHARFUNVOID_H */
