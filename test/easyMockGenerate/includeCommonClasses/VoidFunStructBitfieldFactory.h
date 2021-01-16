#ifndef STRUCTBITFIELDFUNSTRUCTBITFIELDFACTORY_H
#define STRUCTBITFIELDFUNSTRUCTBITFIELDFACTORY_H

#include <FunctionFactory.h>
#include <easyMock.h>
#include <voidFunStructBitfield.h>

class VoidFunStructBitfieldFactory : public FunctionFactory<void, std::tuple<struct BoxPropsContainer>, std::tuple<EasyMock_Matcher>>
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

class VoidFunStructBitfieldGenerateTypeFactory : public VoidFunStructBitfieldFactory
{
public:
  VoidFunStructBitfieldGenerateTypeFactory() { m_generate_types = true; }
};

#endif /* STRUCTBITFIELDFUNSTRUCTBITFIELDFACTORY_H */

