#ifndef UNIONANONYMOUSTYPEDDEFFUNUNIONANONYMOUSTYPEDDEFFACTORY_H
#define UNIONANONYMOUSTYPEDDEFFUNUNIONANONYMOUSTYPEDDEFFACTORY_H

#include <FunctionFactory.h>
#include <easyMock.h>
#include <unionAnonymousTypedDefFunUnionAnonymousTypedDef.h>

class UnionAnonymousTypedDefFunUnionAnonymousTypedDefFactory : public FunctionFactory<TypedDefAnonymousUnion, std::tuple<TypedDefAnonymousUnion>, std::tuple<EasyMock_Matcher>>
{
public:
  Function functionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  void setupTestCase(EasyMockTestCase::TestCase tc) override;
private:

};

#endif /* UNIONANONYMOUSTYPEDDEFFUNUNIONANONYMOUSTYPEDDEFFACTORY_H */

