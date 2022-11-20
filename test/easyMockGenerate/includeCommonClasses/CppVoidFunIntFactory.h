#ifndef EASYMOCK_CPPVOIDFUNVOIDINT_H
#define EASYMOCK_CPPVOIDFUNVOIDINT_H

#include <CppFunctionFactory.h>
#include <cppVoidFunInt.h>

class CppVoidFunIntFactory : public CppFunctionFactory<void, std::tuple<int>, std::tuple<EasyMock::EasyMock_Matcher_Cpp<int>>>
{
public:
  std::shared_ptr<FunctionDeclaration> functionFactory() override;
  ElementToMockList functionFactoryArray() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  void setupTestCase(EasyMockTestCase::TestCase tc) override;

};

class CppVoidFunIntGenerateTypeFactory : public CppVoidFunIntFactory
{
public:
  CppVoidFunIntGenerateTypeFactory() { m_generate_types = true;}
};

#endif //EASYMOCK_CPPVOIDFUNVOIDINT_H
