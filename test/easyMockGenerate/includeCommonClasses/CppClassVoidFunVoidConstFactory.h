#ifndef EASYMOCK_CPPCLASSVOIDFUNVOIDCONSTFACTORY_H
#define EASYMOCK_CPPCLASSVOIDFUNVOIDCONSTFACTORY_H

#include <CppFunctionClassFactory.h>
#include <cppClassVoidFunVoidConst.h>

class CppClassVoidFunVoidConstFactory : public CppFunctionClassFactory<ClassVoidFunVoidConst, void, std::tuple<ClassVoidFunVoidConst*>, std::tuple<>>
{
public:
  std::shared_ptr<FunctionDeclaration> functionFactory() override;
  ElementToMockList functionFactoryArray() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  void setupTestCase(EasyMockTestCase::TestCase tc) override;
  void setupTestCase(EasyMockTestCase::TestCaseClass tc) override;
  ClassVoidFunVoidConst& getInstance() override;
private:
  void setupOneExpect(ClassVoidFunVoidConst* expectInstance, ClassVoidFunVoidConst* paramInstance);
};

class CppClassVoidFunVoidConstGenerateTypeFactory : public CppClassVoidFunVoidConstFactory
{
public:
  CppClassVoidFunVoidConstGenerateTypeFactory() { m_generate_types = true; }
};

#endif //EASYMOCK_CPPCLASSVOIDFUNVOIDCONSTFACTORY_H
