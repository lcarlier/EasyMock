#ifndef LONGDOUBLEFUNLONGDOUBLEFACTORY_H
#define LONGDOUBLEFUNLONGDOUBLEFACTORY_H

#include <FunctionFactory.h>

class LongDoubleFunLongDoubleFactory : public FunctionFactory<long double, std::tuple<long double>, std::tuple<EasyMock_Matcher>>
{
public:
  FunctionDeclaration functionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  void setupTestCase(EasyMockTestCase::TestCase tc) override;

};

#endif /* LONGDOUBLEFUNLONGDOUBLEFACTORY_H */
