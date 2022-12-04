#ifndef EASYMOCK_CPPREFINTFUNREFINTFACTORY_H
#define EASYMOCK_CPPREFINTFUNREFINTFACTORY_H

#include <CppFunctionFactory.h>
#include <cppRefIntFunRefInt.h>

class CppRefIntFunRefIntFactory : public CppFunctionFactory<DefaultConstructibleReferenceWrapper<int>, std::tuple<DefaultConstructibleReferenceWrapper<int>>, std::tuple<EasyMock::EasyMock_Matcher_Cpp<int&>>>
{
public:
  std::shared_ptr<FunctionDeclaration> functionFactory() override;
  ElementToMockList functionFactoryArray() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  void setupTestCase(EasyMockTestCase::TestCase tc) override;
};

class CppRefIntFunRefIntGenerateTypeFactory : public CppRefIntFunRefIntFactory
{
public:
  CppRefIntFunRefIntGenerateTypeFactory() { m_generate_types = true;}
};

#endif //EASYMOCK_CPPREFINTFUNREFINTFACTORY_H
