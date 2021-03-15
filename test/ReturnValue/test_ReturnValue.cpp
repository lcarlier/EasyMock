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
  FunctionType *ft = new FunctionType(TypedReturnValue(CTYPE_INT), Parameter::Vector({NamedParameter(CTYPE_FLOAT, "")}));
  Pointer *ptf = new Pointer(ft);
  ft = nullptr;
  ReturnValue rv(ptf);
  ptf = nullptr;
  EXPECT_STRCASEEQ(rv.getDeclareString().c_str(), "int(*");
}

/*
 * cdecl> declare foo as function(int) returning const pointer to function(float) returning int
 * int (* const foo(int ))(float )
 */
TEST(ReturnValue, CheckConstPointerToFunction)
{
  FunctionType *ft = new FunctionType(TypedReturnValue(CTYPE_INT), Parameter::Vector({NamedParameter(CTYPE_FLOAT, "")}));
  ConstQualifiedType *cptf = new ConstQualifiedType(new Pointer(ft));
  ft = nullptr;
  ReturnValue rv(cptf);
  cptf = nullptr;
  EXPECT_STRCASEEQ(rv.getDeclareString().c_str(), "int(* const");
}

/*
 * cdecl> declare foo as function(int) returning pointer to function(float) returning pointer to function(char) returning double
 * double (*(*foo(int ))(float ))(char )
 */
TEST(ReturnValue, CheckPointerToPointerToFunction)
{
  FunctionType *ft1 = new FunctionType(TypedReturnValue(CTYPE_DOUBLE), Parameter::Vector({NamedParameter(CTYPE_CHAR, "")}));
  Pointer *ptf1 = new Pointer(ft1);
  ft1 = nullptr;
  FunctionType *ft2 = new FunctionType(ReturnValue(ptf1), Parameter::Vector({NamedParameter(CTYPE_FLOAT, "")}));
  ptf1 = nullptr;
  Pointer *ptf2 = new Pointer(ft2);
  ft2 = nullptr;
  ReturnValue rv(ptf2);
  EXPECT_STRCASEEQ(rv.getDeclareString().c_str(), "double(*(*");
}

/*
 * cdecl> declare foo as function(int) returning const pointer to function(float) returning const pointer to function(char) returning double
 * double (*(*foo(int ))(float ))(char )
 */
TEST(ReturnValue, CheckConstPointerToConstPointerToFunction)
{
  FunctionType *ft1 = new FunctionType(TypedReturnValue(CTYPE_DOUBLE), Parameter::Vector({NamedParameter(CTYPE_CHAR, "")}));
  ConstQualifiedType *cptf1 = new ConstQualifiedType(new Pointer(ft1));
  ft1 = nullptr;
  FunctionType *ft2 = new FunctionType(ReturnValue(cptf1), Parameter::Vector({NamedParameter(CTYPE_FLOAT, "")}));
  cptf1 = nullptr;
  ConstQualifiedType *cptf2 = new ConstQualifiedType(new Pointer(ft2));
  ft2 = nullptr;
  ReturnValue rv(cptf2);
  EXPECT_STRCASEEQ(rv.getDeclareString().c_str(), "double(* const(* const");
}
