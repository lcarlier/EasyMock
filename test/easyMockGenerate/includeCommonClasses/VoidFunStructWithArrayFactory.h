#ifndef VOIDFUNSTRUCTWITHARRAYFACTORY_H
#define VOIDFUNSTRUCTWITHARRAYFACTORY_H

#include <FunctionFactory.h>
#include <easyMock.h>
#include <voidFunStructWithArray.h>

class VoidFunStructWithArrayFactory : public FunctionFactory<void, std::tuple<struct structWithArray>, std::tuple<EasyMock_Matcher>>
{
public:
  FunctionDeclaration functionFactory() override;
  FunctionDeclaration* newFunctionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;

};

#endif /* VOIDFUNSTRUCTWITHARRAYFACTORY_H */

