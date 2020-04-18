#ifndef VOIDFUNSTRUCTRECUSNONTYPEDEFFACTORY_H
#define VOIDFUNSTRUCTRECUSNONTYPEDEFFACTORY_H

#include <FunctionFactory.h>
#include <voidFunStructRecursNonTypedef.h>

class VoidFunStructRecusNonTypedefFactory : public FunctionFactory<int, std::tuple<t_s1>, std::tuple<EasyMock_Matcher>>
{
public:
  Function functionFactory() override;
  Function* newFunctionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;

};

#endif /* VOIDFUNSTRUCTRECUSNONTYPEDEFFACTORY_H */
