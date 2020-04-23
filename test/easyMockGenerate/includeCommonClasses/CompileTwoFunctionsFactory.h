#ifndef COMPILETWOFUNCTIONSFACTORY_H
#define COMPILETWOFUNCTIONSFACTORY_H

#include <FunctionFactory.h>
#include <compileTwoFunctions.h>

class CompileTwoFunctionsFactory : public FunctionFactory<int, std::tuple<struct twoFunStruct>, std::tuple<EasyMock_Matcher>>
{
public:
  ElementToMockList functionFactoryArray() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;

};

#endif /* COMPILETWOFUNCTIONSFACTORY_H */

