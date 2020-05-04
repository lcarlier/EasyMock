#ifndef VOIDFUNPARAMNONAMEFACTORY_H
#define VOIDFUNPARAMNONAMEFACTORY_H

#include <FunctionFactory.h>
#include <voidFunParamNoName.h>

class VoidFunParamNoNameFactory : public FunctionFactory<int, std::tuple<int, float>, std::tuple<EasyMock_Matcher, EasyMock_Matcher>>
{
public:
  Function functionFactory() override;
  Function* newFunctionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;

};

#endif /* VOIDFUNPARAMNONAME_H */

