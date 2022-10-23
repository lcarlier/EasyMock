#ifndef EASYMOCK_CPPCLASSINTFUNINTFACTORY_H
#define EASYMOCK_CPPCLASSINTFUNINTFACTORY_H

#include <CppFunctionClassFactory.h>
#include <cppClassIntFunInt.h>

class CppClassIntFunIntFactory : public CppFunctionClassFactory<ClassIntFunInt, int, std::tuple<ClassIntFunInt*, int>, std::tuple<EasyMock::EasyMock_Matcher_Cpp<int>>>
{
public:
  std::shared_ptr<FunctionDeclaration> functionFactory() override;
  ElementToMockList functionFactoryArray() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  void setupTestCase(EasyMockTestCase::TestCase tc) override;
  void setupTestCase(EasyMockTestCase::TestCaseClass tc) override;
  ClassIntFunInt& getInstance() override;
private:
  void setupOneExpect(ClassIntFunInt* expectInstance, ClassIntFunInt* paramInstance);
};

class CppClassIntFunIntGenerateTypeFactory : public CppClassIntFunIntFactory
{
public:
  CppClassIntFunIntGenerateTypeFactory() { m_generate_types = true; }
};

#endif //EASYMOCK_CPPCLASSINTFUNINTFACTORY_H
