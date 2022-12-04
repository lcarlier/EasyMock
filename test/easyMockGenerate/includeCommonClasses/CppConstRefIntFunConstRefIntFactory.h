#ifndef EASYMOCK_CPPCONSTREFINTFUNCONSTREFINTFACTORY_H
#define EASYMOCK_CPPCONSTREFINTFUNCONSTREFINTFACTORY_H

#include <CppFunctionFactory.h>
#include <cppConstRefIntFunConstRefInt.h>

class CppConstRefIntFunConstRefIntFactory : public CppFunctionFactory<DefaultConstructibleReferenceWrapper<const int>, std::tuple<DefaultConstructibleReferenceWrapper<const int>>, std::tuple<EasyMock::EasyMock_Matcher_Cpp<const int&>>>
{
public:
  CppConstRefIntFunConstRefIntFactory(){m_rm_dir = false;}
  std::shared_ptr<FunctionDeclaration> functionFactory() override;
  ElementToMockList functionFactoryArray() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  void setupTestCase(EasyMockTestCase::TestCase tc) override;
};

class CppConstRefIntFunConstRefIntGenerateTypeFactory : public CppConstRefIntFunConstRefIntFactory
{
public:
  CppConstRefIntFunConstRefIntGenerateTypeFactory() { m_generate_types = true;}
};

#endif //EASYMOCK_CPPCONSTREFINTFUNCONSTREFINTFACTORY_H
