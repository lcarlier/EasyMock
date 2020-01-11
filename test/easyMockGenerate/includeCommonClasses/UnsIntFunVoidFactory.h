#ifndef UNSINTFUNVOIDFACTORY_H
#define UNSINTFUNVOIDFACTORY_H

#include <FunctionFactory.h>

class UnsIntFunVoidFactory : public FunctionFactory<unsigned int, std::tuple<>, std::tuple<>>
{
public:
  Function functionFactory() override;
  Function* newFunctionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  void setupTestCase(EasyMockTestCase::TestCase tc) override;

};

#endif /* UNSINTFUNVOIDFACTORY_H */

