#ifndef STRUCTSUBSTRUCTRECURSIVETYPEFACTORY_H
#define STRUCTSUBSTRUCTRECURSIVETYPEFACTORY_H

#include <FunctionFactory.h>
#include <easyMock.h>
#include <structSubStructRecursiveType.h>

class StructSubStructRecursiveTypeFactory : public FunctionFactory<void, std::tuple<struct st1>, std::tuple<EasyMock_Matcher>>
{
public:
  FunctionDeclaration functionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  std::string getMatcherFunctionName() override;
  std::string getFieldWrongName() override;
  std::string getSubFieldWrongName() override;
  std::string getSubFieldWrongTypeName() override;
  std::string getSubComposableTypeType() override;

  void setupTestCase(EasyMockTestCase::TestCase tc) override;
};

class StructSubStructRecursiveTypeGenerateTypeFactory : public StructSubStructRecursiveTypeFactory
{
public:
  StructSubStructRecursiveTypeGenerateTypeFactory() { m_generate_types = true; }
};

#endif /* STRUCTSUBSTRUCTRECURSIVETYPEFACTORY_H */

