#ifndef VOIDFUNSTRUCTWITHTYPEDEFSTRUCTFACTORY_H
#define VOIDFUNSTRUCTWITHTYPEDEFSTRUCTFACTORY_H

#include <FunctionFactory.h>
#include <voidFunStructWithTypedefStruct.h>

class VoidFunStructWithTypedefStructFactory : public FunctionFactory<int, std::tuple<t_struct>, std::tuple<EasyMock_Matcher>>
{
public:
  Function functionFactory() override;
  Function* newFunctionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;

};

#endif /* VOIDFUNSTRUCTWITHTYPEDEFSTRUCT_H */

