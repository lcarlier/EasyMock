#ifndef VOIDSTRUCTANONYMOUSTYPEDEF_HPP
#define VOIDSTRUCTANONYMOUSTYPEDEF_HPP


#include <FunctionFactory.h>
#include <easyMock.h>
#include <structAnonymousTypedDefFunStructAnonymousTypedDef.h>

class StructAnonymousTypedDefFunStructAnonymousTypedDefFactory : public FunctionFactory<TypedDefAnonymousStruct, std::tuple<TypedDefAnonymousStruct>, std::tuple<EasyMock_Matcher>>
{
  public:
  FunctionDeclaration functionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  void setupTestCase(EasyMockTestCase::TestCase tc) override;
};

#endif /* VOIDSTRUCTANONYMOUSTYPEDEF_HPP */

