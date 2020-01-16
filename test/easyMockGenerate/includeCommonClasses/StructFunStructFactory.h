#ifndef STRUCTFUNSTRUCTFACTORY_H
#define STRUCTFUNSTRUCTFACTORY_H

#include <FunctionFactory.h>
#include <easyMock.h>
#include <structFunStruct.h>
#include <iostream>

typedef struct s1 (*structFunStruct_funPtr)(struct s2);
typedef void (*structFunStruct_funExpectPtr)(struct s2 a, struct s1 rv, EasyMock_Matcher match_a);
typedef int (*structFunStruct_funMatcherPtr)(EASYMOCK_MATCHER_PARAM);

bool operator==(const struct s1 &lhs, const struct s1 &rhs);
std::ostream& operator<<(std::ostream& os, const struct s1& c);
std::ostream& operator<<(std::ostream& os, const struct s2& c);

class StructFunStructFactory : public FunctionFactory<s1, std::tuple<s2>, std::tuple<EasyMock_Matcher>>
//class StructFunStructFactory : public FunctionFactory<s1, s2>
//class StructFunStructFactory : public FunctionFactory<s1, std::tuple<s2>, EasyMock_Matcher>
{
public:
  Function functionFactory() override;
  Function* newFunctionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  void setupTestCase(EasyMockTestCase::TestCase tc) override;

};

#endif /* STRUCTFUNSTRUCTFACTORY_H */
