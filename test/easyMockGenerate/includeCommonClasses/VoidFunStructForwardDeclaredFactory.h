#ifndef VOIDFUNSTRUCTFORWARDDECLAREDFACTORY_H
#define VOIDFUNSTRUCTFORWARDDECLAREDFACTORY_H

#include <FunctionFactory.h>
#include <easyMock.h>

#include <voidFunStructForwardDeclared.h>

class VoidFunStructForwardDeclaredFactory : public FunctionFactory<int, std::tuple<struct forwardDeclaredChild>, std::tuple<EasyMock_Matcher>>
{
public:
  ElementToMockList functionFactoryArray() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;

};

#endif /* VOIDFUNSTRUCTFORWARDDECLAREDFACTORY_H */

