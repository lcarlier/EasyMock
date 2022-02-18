#ifndef EASYMOCK_CPPVOIDFUNVOIDFACTORY_H
#define EASYMOCK_CPPVOIDFUNVOIDFACTORY_H

#include <CppFunctionFactory.h>
#include <cppVoidFunVoid.h>

class CppVoidFunVoidFactory : public CppFunctionFactory<void, std::tuple<>, std::tuple<>>
{
public:
  FunctionDeclaration functionFactory() override;
  ElementToMockList functionFactoryArray() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  void setupTestCase(EasyMockTestCase::TestCase tc) override;

};

class CppVoidFunVoidGenerateTypeFactory : public CppVoidFunVoidFactory
{
public:
  CppVoidFunVoidGenerateTypeFactory() { m_generate_types = true; }
};

#endif //EASYMOCK_CPPVOIDFUNVOIDFACTORY_H
