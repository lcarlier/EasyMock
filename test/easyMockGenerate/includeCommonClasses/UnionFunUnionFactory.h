#ifndef UNIONFUNUNIONFACTORY_H
#define UNIONFUNUNIONFACTORY_H

#include <FunctionFactory.h>
#include <easyMock.h>
#include <unionFunUnion.h>

class UnionFunUnionFactory : public FunctionFactory<union u1, std::tuple<union u2>, std::tuple<EasyMock_Matcher>>
{
public:
  Function functionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  void setupTestCase(EasyMockTestCase::TestCase tc) override;
private:

};

#endif /* UNIONFUNUNIONFACTORY_H */

