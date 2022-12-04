#ifndef EASYMOCK_CPPFUNCTIONFACTORY_H
#define EASYMOCK_CPPFUNCTIONFACTORY_H

#include <functional>
#include "FunctionFactory.h"

template<typename T>
struct DefaultConstructibleReferenceWrapper: public std::reference_wrapper<T>
{
  DefaultConstructibleReferenceWrapper():std::reference_wrapper<T>(a){}
  DefaultConstructibleReferenceWrapper(T& v):std::reference_wrapper<T>(v){}
  static T a;
};

template<typename T>
T DefaultConstructibleReferenceWrapper<T>::a{};

template<typename RV, typename Params, typename Compare>
class CppFunctionFactory: public FunctionFactory<RV, Params, Compare>
{
  bool isCpp() override final { return true; }
};

#endif //EASYMOCK_CPPFUNCTIONFACTORY_H
