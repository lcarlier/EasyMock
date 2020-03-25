#ifndef VOIDFUNSTRUCTWITHANONYMOUSSTRUCTFIELDFACTORY_H
#define VOIDFUNSTRUCTWITHANONYMOUSSTRUCTFIELDFACTORY_H

#include <FunctionFactory.h>
#include <voidFunStructWithAnonymousStructField.h>

class VoidFunStructWithAnonymousStructFieldFactory : public FunctionFactory<int, std::tuple<struct topAnonymousStructField>, std::tuple<EasyMock_Matcher>>
{
public:
  Function functionFactory() override;
  Function* newFunctionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;

};

#endif /* VOIDFUNSTRUCTWITHANONYMOUSSTRUCTFIELDFACTORY_H */

