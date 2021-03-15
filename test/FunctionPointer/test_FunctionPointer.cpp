#include <gtest/gtest.h>

#include <FunctionDeclaration.h>
#include <FunctionType.h>
#include <Pointer.h>
#include <TypedefType.h>

#include <string>

TEST(FunctionPointer, CheckTypeDefPointerToFunction)
{
  FunctionType *ft = new FunctionType(TypedReturnValue(CTYPE_INT), Parameter::Vector({NamedParameter(CTYPE_FLOAT, "f")}));
  TypedefType ptf("foo", new Pointer(ft));
  ft = nullptr;
  EXPECT_STRCASEEQ(ptf.getFullDeclarationName().c_str(), "foo");
}

TEST(FunctionType, checkPrefix)
{
  FunctionType ft(TypedReturnValue(CTYPE_INT), Parameter::Vector({NamedParameter(CTYPE_FLOAT, "f")}));
  ASSERT_STREQ(ft.getDeclarationPrefix().c_str(), "int(");
}

TEST(FunctionType, checkPostfix)
{
  FunctionType ft(TypedReturnValue(CTYPE_INT), Parameter::Vector({NamedParameter(CTYPE_FLOAT, "f")}));
  // This will need to be modified once the bug to also print the parameter name is fix.
  ASSERT_STREQ(ft.getDeclarationPostfix().c_str(), ")(float)");
}
