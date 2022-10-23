#ifndef VOIDSTRUCTANONYMOUSTYPEDEF_HPP
#define VOIDSTRUCTANONYMOUSTYPEDEF_HPP


#include <FunctionFactory.h>
#include <easyMock.h>
#include <structAnonymousTypedDefFunStructAnonymousTypedDef.h>

class StructAnonymousTypedDefFunStructAnonymousTypedDefFactory : public FunctionFactory<TypedDefAnonymousStruct, std::tuple<TypedDefAnonymousStruct, TypedDefAnonymousStruct2>, std::tuple<EasyMock_Matcher, EasyMock_Matcher>>
{
  public:
  std::shared_ptr<FunctionDeclaration> functionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  void setupTestCase(EasyMockTestCase::TestCase tc) override;
};

class StructAnonymousTypedDefFunStructAnonymousTypedDefGenerateTypeFactory : public StructAnonymousTypedDefFunStructAnonymousTypedDefFactory
{
public:
  StructAnonymousTypedDefFunStructAnonymousTypedDefGenerateTypeFactory() { m_generate_types = true; }
};

#endif /* VOIDSTRUCTANONYMOUSTYPEDEF_HPP */

