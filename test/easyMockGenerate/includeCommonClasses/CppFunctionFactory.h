#ifndef EASYMOCK_CPPFUNCTIONFACTORY_H
#define EASYMOCK_CPPFUNCTIONFACTORY_H

#include "FunctionFactory.h"

template<typename RV, typename Params, typename Compare>
class CppFunctionFactory: public FunctionFactory<RV, Params, Compare>
{
  bool isCpp() override final { return true; }
};

#endif //EASYMOCK_CPPFUNCTIONFACTORY_H
