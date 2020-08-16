#ifndef UNIONTYPEDDEFFUNUNIONTYPEDDEFFACTORY_HPP
#define UNIONTYPEDDEFFUNUNIONTYPEDDEFFACTORY_HPP

#include <FunctionFactory.h>
#include <easyMock.h>
#include <unionTypedDefFunUnionTypedDef.h>

class UnionTypedDefFunUnionTypedDefFactory : public FunctionFactory<union u, std::tuple<t_u>, std::tuple<EasyMock_Matcher>>
{
public:
  FunctionDeclaration functionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  void setupTestCase(EasyMockTestCase::TestCase tc) override;
private:

};

#endif /* UNIONTYPEDDEFFUNUNIONTYPEDDEFFACTORY_HPP */

