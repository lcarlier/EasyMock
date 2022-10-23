#ifndef EASYMOCK_CPPFUNCTIONCLASSFACTORY_H
#define EASYMOCK_CPPFUNCTIONCLASSFACTORY_H

#include "CppFunctionFactory.h"

template<typename ClassType, typename RV, typename Params, typename Compare>
class CppFunctionClassFactory: public CppFunctionFactory<RV, Params, Compare>
{
  using CppFunctionFactory<RV, Params, Compare>::setupTestCase;
  virtual void setupTestCase(EasyMockTestCase::TestCaseClass tc) {fprintf(stderr, "Function %s must be overriden\n\r", __FUNCTION__); assert(false);};
  virtual ClassType& getInstance() = 0;
  // This constexpr function "overrides" the function in FunctionFactory
  constexpr bool isClassMember() { return true; }
};

#endif //EASYMOCK_CPPFUNCTIONCLASSFACTORY_H
