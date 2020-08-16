#ifndef STRUCTWITHUNIONFUNSTRUCTWITHUNIONFACTORY_H
#define STRUCTWITHUNIONFUNSTRUCTWITHUNIONFACTORY_H

#include <FunctionFactory.h>
#include <easyMock.h>
#include <structWithUnionFunStructWithUnion.h>

class StructWithUnionFunStructWithUnionFactory : public FunctionFactory<sWithUnion, std::tuple<sWithUnion>, std::tuple<EasyMock_Matcher>>
{
public:
  FunctionDeclaration functionFactory() override;
  FunctionDeclaration* newFunctionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  void setupTestCase(EasyMockTestCase::TestCase tc) override;

};

#endif /* STRUCTWITHUNIONFUNSTRUCTWITHUNIONFACTORY_H */

