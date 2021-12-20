#ifndef STRUCTWITHUNIONFUNSTRUCTWITHUNIONFACTORY_H
#define STRUCTWITHUNIONFUNSTRUCTWITHUNIONFACTORY_H

#include <FunctionFactory.h>
#include <easyMock.h>
#include <structWithUnionFunStructWithUnion.h>

class StructWithUnionFunStructWithUnionFactory : public FunctionFactory<sWithUnion, std::tuple<sWithUnion>, std::tuple<EasyMock_Matcher>>
{
public:
  FunctionDeclaration functionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  void setupTestCase(EasyMockTestCase::TestCase tc) override;

};

class StructWithUnionFunStructWithUnionGenerateTypeFactory : public StructWithUnionFunStructWithUnionFactory
{
public:
  StructWithUnionFunStructWithUnionGenerateTypeFactory() { m_generate_types = true; }
};

#endif /* STRUCTWITHUNIONFUNSTRUCTWITHUNIONFACTORY_H */
