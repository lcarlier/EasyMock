#ifndef INTFUNSTRUCTPTRINTCHARPTRFACTORY_H
#define INTFUNSTRUCTPTRINTCHARPTRFACTORY_H

#include <FunctionFactory.h>
#include <voidFunStructPtr.h>

class IntFunStructPtrIntCharPtrFactory : public FunctionFactory<int, std::tuple<struct s2*, int, char*>, std::tuple<EasyMock_Matcher, EasyMock_Matcher, EasyMock_Matcher>>
{
public:
  Function functionFactory() override;
  Function* newFunctionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
};

#endif /* INTFUNSTRUCTPTRINTCHARPTRFACTORY_H */

