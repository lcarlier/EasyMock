#ifndef VARIADICFUNCTIONSFACTORY_H
#define VARIADICFUNCTIONSFACTORY_H

#include <FunctionFactory.h>
#include <variadicFunctions.h>

class VariadicFunctionsFactory : public FunctionFactory<int, std::tuple<int>, std::tuple<EasyMock_Matcher>>
{
public:
  ElementToMockList functionFactoryArray() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;

};

#endif /* VARIADICFUNCTIONSFACTORY_H */

