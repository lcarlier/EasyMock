
#ifndef FLOATFUNFLOATFACTORY_H
#define FLOATFUNFLOATFACTORY_H

#include <FunctionFactory.h>

class FloatFunFloatFactory : public FunctionFactory<float, std::tuple<float>, std::tuple<EasyMock_Matcher>>
{
public:
  FunctionDeclaration functionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  void setupTestCase(EasyMockTestCase::TestCase tc) override;

};

#endif /* FLOATFUNFLOATFACTORY_H */
