#ifndef UNSSHORTFUNUNSSHORTFACTORY_H
#define UNSSHORTFUNUNSSHORTFACTORY_H

#include <FunctionFactory.h>
#include <easyMock.h>

class UnsShortFunUnsShortFactory : public FunctionFactory<unsigned short, std::tuple<unsigned short>, std::tuple<EasyMock_Matcher>>
{
public:
  FunctionDeclaration functionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  void setupTestCase(EasyMockTestCase::TestCase tc) override;

};


#endif /* UNSSHORTFUNUNSSHORTFACTORY_H */
