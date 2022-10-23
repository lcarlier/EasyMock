#ifndef COMMON_H
#define COMMON_H

#include <FunctionDeclaration.h>
#include <ReturnValue.h>
#include <Parameter.h>
#include <StructType.h>

#include <tuple>

using functionTuple = std::tuple<const char*, ReturnValue, Parameter::Vector>;
using functionTypeTuple = std::tuple<ReturnValue, Parameter::Vector>;


namespace
{
  std::shared_ptr<const FunctionDeclaration> getF1()
  {
    return std::make_shared<const FunctionDeclaration>("f1", VoidReturnValue(), Parameter::Vector{});
  }
  std::shared_ptr<const FunctionDeclaration> getF2()
  {
    Parameter::Vector params;
    params.emplace_back(NamedParameter(CTYPE_INT, "i"));
    return std::make_shared<const FunctionDeclaration>("f2", TypedReturnValue(CTYPE_INT), std::move(params));
  }
}

#endif /* COMMON_H */
