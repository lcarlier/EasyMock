#include <gtest/gtest.h>

#include <StructType.h>
#include <FunctionType.h>
#include <Pointer.h>
#include <ConstQualifiedType.h>

#include <string>

/*
 * cdecl> declare foo as function(int) returning pointer to function(float) returning int
 * int (*foo(int ))(float )
 */
TEST(ReturnValue, CheckPointerToFunction)
{
  Parameter::Vector pv{};
  pv.emplace_back(NamedParameter(CTYPE_FLOAT, ""));
  auto ft = std::make_shared<FunctionType>(TypedReturnValue(CTYPE_INT), std::move(pv));
  auto ptf = std::make_shared<Pointer>(std::move(ft));
  ReturnValue rv(std::move(ptf));
  EXPECT_STRCASEEQ(rv.getDeclareString().c_str(), "int(*");
}

/*
 * cdecl> declare foo as function(int) returning const pointer to function(float) returning int
 * int (* const foo(int ))(float )
 */
TEST(ReturnValue, CheckConstPointerToFunction)
{
  Parameter::Vector pvft{};
  pvft.emplace_back(NamedParameter(CTYPE_FLOAT, ""));
  auto ft = std::make_shared<FunctionType>(TypedReturnValue(CTYPE_INT), std::move(pvft));
  auto cptf = std::make_shared<ConstQualifiedType>(std::make_shared<Pointer>(std::move(ft)));
  ReturnValue rv(std::move(cptf));
  cptf = nullptr;
  EXPECT_STRCASEEQ(rv.getDeclareString().c_str(), "int(* const");
}

/*
 * cdecl> declare foo as function(int) returning pointer to function(float) returning pointer to function(char) returning double
 * double (*(*foo(int ))(float ))(char )
 */
TEST(ReturnValue, CheckPointerToPointerToFunction)
{
  Parameter::Vector pvft1{};
  pvft1.emplace_back(NamedParameter(CTYPE_CHAR, ""));
  auto ft1 = std::make_shared<FunctionType>(TypedReturnValue(CTYPE_DOUBLE), std::move(pvft1));
  auto ptf1 = std::make_shared<Pointer>(std::move(ft1));
  Parameter::Vector pvft2{};
  pvft2.emplace_back(NamedParameter(CTYPE_FLOAT, ""));
  auto ft2 = std::make_shared<FunctionType>(ReturnValue(ptf1), std::move(pvft2));
  auto ptf2 = std::make_shared<Pointer>(std::move(ft2));
  ReturnValue rv(std::move(ptf2));
  EXPECT_STRCASEEQ(rv.getDeclareString().c_str(), "double(*(*");
}

/*
 * cdecl> declare foo as function(int) returning const pointer to function(float) returning const pointer to function(char) returning double
 * double (*(*foo(int ))(float ))(char )
 */
TEST(ReturnValue, CheckConstPointerToConstPointerToFunction)
{
  Parameter::Vector pvft1{};
  pvft1.emplace_back(NamedParameter(CTYPE_CHAR, ""));
  auto ft1 = std::make_shared<FunctionType>(TypedReturnValue(CTYPE_DOUBLE), std::move(pvft1));
  auto cptf1 = std::make_shared<ConstQualifiedType>(std::make_shared<Pointer>(std::move(ft1)));
  Parameter::Vector pvft2{};
  pvft2.emplace_back(NamedParameter(CTYPE_FLOAT, ""));
  auto ft2 = std::make_shared<FunctionType>(ReturnValue(cptf1), std::move(pvft2));
  auto cptf2 = std::make_shared<ConstQualifiedType>(std::make_shared<Pointer>(std::move(ft2)));
  ReturnValue rv(std::move(cptf2));
  EXPECT_STRCASEEQ(rv.getDeclareString().c_str(), "double(* const(* const");
}
