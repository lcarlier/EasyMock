#ifndef VOIDFUNSTRUCTWITHSECONDLEVELANONYMOUSFACTORY_H
#define VOIDFUNSTRUCTWITHSECONDLEVELANONYMOUSFACTORY_H

#include <FunctionFactory.h>
#include <easyMock.h>
#include <voidFunStructWithSecondLevelAnonymous.h>

class VoidFunStructWithSecondLevelAnonymousFactory : public FunctionFactory<void, std::tuple<top_t>, std::tuple<EasyMock_Matcher>>
{
public:
  std::shared_ptr<FunctionDeclaration> functionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  std::string getMatcherFunctionName() override;
  std::string getFieldWrongName() override;
  std::string getSubFieldWrongName() override;
  std::string getSubFieldWrongTypeName() override;
  std::string getSubComposableTypeType() override;

  void setupTestCase(EasyMockTestCase::TestCase tc) override;
};

class VoidFunStructWithSecondLevelAnonymousGenerateTypeFactory : public VoidFunStructWithSecondLevelAnonymousFactory
{
public:
  VoidFunStructWithSecondLevelAnonymousGenerateTypeFactory() { m_generate_types = true; }
};

#endif /* VOIDFUNSTRUCTWITHSECONDLEVELANONYMOUSFACTORY_H */

