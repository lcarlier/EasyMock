#ifndef VOIDSTRUCTTYPEDDEFFACTORY_H
#define VOIDSTRUCTTYPEDDEFFACTORY_H

#include <FunctionFactory.h>
#include <easyMock.h>
#include <voidStructTypedDef.h>

class VoidStructTypedDefFactory : public FunctionFactory<unsigned short, std::tuple<TypedDefAnonynousStruct, TypedDefStruct>, std::tuple<EasyMock_Matcher, EasyMock_Matcher>>
{
public:
  Function functionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  //No test en generates because struct parameter generation are already tested. We only test parsing the typed def structure
};

#endif /* VOIDSTRUCTTYPEDDEFFACTORY_H */

