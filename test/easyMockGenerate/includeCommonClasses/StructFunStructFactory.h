#ifndef STRUCTFUNSTRUCTFACTORY_H
#define STRUCTFUNSTRUCTFACTORY_H

#include <FunctionFactory.h>
#include <easyMock.h>
#include <structFunStruct.h>
#include <iostream>

class StructFunStructFactory : public FunctionFactory<s1, std::tuple<struct s2, struct onelineStruct>, std::tuple<EasyMock_Matcher, EasyMock_Matcher>>
{
public:
  std::shared_ptr<FunctionDeclaration> functionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  void setupTestCase(EasyMockTestCase::TestCase tc) override;

};

class StructFunStructGenerateTypeFactory : public StructFunStructFactory
{
public:
  StructFunStructGenerateTypeFactory() { m_generate_types = true; }
};

#endif /* STRUCTFUNSTRUCTFACTORY_H */
