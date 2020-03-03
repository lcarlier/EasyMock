#ifndef VOIDSTRUCTTYPEDDEFFACTORY_H
#define VOIDSTRUCTTYPEDDEFFACTORY_H

#include <FunctionFactory.h>
#include <easyMock.h>
#include <structTypedDefFunStructTypedDef.h>

class StructTypedDefFunStructTypedDefFactory : public FunctionFactory<TypedDefStruct, std::tuple<TypedDefStruct>, std::tuple<EasyMock_Matcher>>
{
public:
  Function functionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  void setupTestCase(EasyMockTestCase::TestCase tc) override;
};

#endif /* VOIDSTRUCTTYPEDDEFFACTORY_H */

