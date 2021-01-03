#ifndef VOIDFUNSTRUCTPTRFACTORY_H
#define VOIDFUNSTRUCTPTRFACTORY_H

#include <FunctionFactory.h>
#include <voidFunStructPtr.h>

class VoidFunStructPtrFactory : public FunctionFactory<void, std::tuple<struct s2*>, std::tuple<EasyMock_Matcher>>
{
public:
  FunctionDeclaration functionFactory() override;
  FunctionDeclaration* newFunctionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;

};

#endif /* VOIDFUNSTRUCTPTRFACTORY_H */

