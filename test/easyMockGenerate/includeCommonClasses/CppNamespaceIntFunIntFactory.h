#ifndef EASYMOCK_CPPNAMESPACEINTFUNINTFACTORY_H
#define EASYMOCK_CPPNAMESPACEINTFUNINTFACTORY_H

#include <CppFunctionFactory.h>
#include <cppNamespaceIntFunInt.h>

class CppNamespaceIntFunIntFactory : public CppFunctionFactory<int, std::tuple<int>, std::tuple<EasyMock::EasyMock_Matcher_Cpp<int>>>
{
public:
  FunctionDeclaration functionFactory() override;
  ElementToMockList functionFactoryArray() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  void setupTestCase(EasyMockTestCase::TestCase tc) override;

};

class CppNamespaceIntFunIntGenerateTypeFactory : public CppNamespaceIntFunIntFactory
{
public:
  CppNamespaceIntFunIntGenerateTypeFactory() { m_generate_types = true; }
};


#endif //EASYMOCK_CPPNAMESPACEINTFUNINTFACTORY_H
