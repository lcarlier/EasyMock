#ifndef VOIDFUNSTRUCTWITHEMBEDDEDSTRUCTFACTORY_H
#define VOIDFUNSTRUCTWITHEMBEDDEDSTRUCTFACTORY_H

#include <FunctionFactory.h>
#include <voidFunStructWithEmbeddedStruct.h>

class VoidFunStructWithEmbeddedStructFactory : public FunctionFactory<int, std::tuple<struct topEmbedded>, std::tuple<EasyMock_Matcher>>
{
public:
  Function functionFactory() override;
  Function* newFunctionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;

};

#endif /* VOIDFUNSTRUCTWITHEMBEDDEDSTRUCTFACTORY_H */

