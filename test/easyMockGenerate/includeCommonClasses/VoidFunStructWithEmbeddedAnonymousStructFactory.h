#ifndef VOIDFUNSTRUCTWITHEMBEDDEDANONYMOUSSTRUCTFACTORY_H
#define VOIDFUNSTRUCTWITHEMBEDDEDANONYMOUSSTRUCTFACTORY_H

#include <FunctionFactory.h>
#include <voidFunStructWithEmbeddedAnonymousStruct.h>

class VoidFunStructWithEmbeddedAnonymousStructFactory : public FunctionFactory<int, std::tuple<struct topEmbeddedAnonymous>, std::tuple<EasyMock_Matcher>>
{
public:
  Function functionFactory() override;
  Function* newFunctionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;

};

#endif /* VOIDFUNSTRUCTWITHEMBEDDEDANONYMOUSSTRUCTFACTORY_H */

