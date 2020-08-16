#ifndef STRUCTFUNSTRUCTFACTORY_H
#define STRUCTFUNSTRUCTFACTORY_H

#include <FunctionFactory.h>
#include <easyMock.h>
#include <structFunStruct.h>
#include <iostream>

class StructFunStructFactory : public FunctionFactory<s1, std::tuple<s2>, std::tuple<EasyMock_Matcher>>
{
public:
  FunctionDeclaration functionFactory() override;
  FunctionDeclaration* newFunctionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  void setupTestCase(EasyMockTestCase::TestCase tc) override;

};

#endif /* STRUCTFUNSTRUCTFACTORY_H */

