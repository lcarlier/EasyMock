#ifndef VOIDSTRUCTTYPEDDEFFACTORY_H
#define VOIDSTRUCTTYPEDDEFFACTORY_H

#include <FunctionFactory.h>
#include <easyMock.h>
#include <structTypedDefFunStructTypedDef.h>

class StructTypedDefFunStructTypedDefFactory : public FunctionFactory<TypedDefStruct, std::tuple<TypedDefStruct>, std::tuple<EasyMock_Matcher>>
{
public:
  std::shared_ptr<FunctionDeclaration> functionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  void setupTestCase(EasyMockTestCase::TestCase tc) override;
};

class StructTypedDefFunStructTypedDefGenerateTypeFactory : public StructTypedDefFunStructTypedDefFactory
{
public:
  StructTypedDefFunStructTypedDefGenerateTypeFactory() { m_generate_types = true; }
};

#endif /* VOIDSTRUCTTYPEDDEFFACTORY_H */

