#ifndef DOUBLEFUNDOUBLEFACTORY_H
#define DOUBLEFUNDOUBLEFACTORY_H

#include <FunctionFactory.h>

class DoubleFunDoubleFactory : public FunctionFactory<double, std::tuple<double>, std::tuple<EasyMock_Matcher>>
{
public:
  std::shared_ptr<FunctionDeclaration> functionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  void setupTestCase(EasyMockTestCase::TestCase tc) override;

};

#endif /* DOUBLEFUNDOUBLEFACTORY_H */
