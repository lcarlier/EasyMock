#ifndef VOIDFUNPARAMNONAMEFACTORY_H
#define VOIDFUNPARAMNONAMEFACTORY_H

#include <FunctionFactory.h>
#include <voidFunParamNoName.h>

class VoidFunParamNoNameFactory : public FunctionFactory<void, std::tuple<int, float>, std::tuple<EasyMock_Matcher, EasyMock_Matcher>>
{
public:
  FunctionDeclaration functionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;

};

#endif /* VOIDFUNPARAMNONAME_H */
