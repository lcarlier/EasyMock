#include <gtest/gtest.h>

#include <FunctionDeclaration.h>
#include <FunctionType.h>
#include <Pointer.h>

#include <string>

/*
 * cdecl> declare foo as pointer to function(float) returning int
 * int (*foo)(float )
 */
TEST(ReturnValue, CheckNakedPointerToFunction)
{
  FunctionType *ft = new FunctionType("", TypedReturnValue(CTYPE_INT), Parameter::Vector({NamedParameter(CTYPE_FLOAT, "f")}));
  Pointer ptf(ft, "foo", false);
  ft = nullptr;
  EXPECT_STRCASEEQ(ptf.getFullDeclarationName().c_str(), "int(*foo)(float)");
}
