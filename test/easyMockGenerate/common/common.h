#ifndef COMMON_H
#define COMMON_H

#include <ReturnValue.h>
#include <Parameter.h>
#include <StructType.h>

#include <tuple>

using functionTuple = std::tuple<const char*, ReturnValue, Parameter::Vector>;
using functionTypeTuple = std::tuple<ReturnValue, Parameter::Vector>;

#endif /* COMMON_H */
