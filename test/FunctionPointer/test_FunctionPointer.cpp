#include <gtest/gtest.h>

#include <FunctionDeclaration.h>
#include <FunctionType.h>
#include <Pointer.h>
#include <TypedefType.h>

#include <string>

TEST(FunctionPointer, CheckTypeDefPointerToFunction)
{
  Parameter::Vector pv{};
  pv.emplace_back(NamedParameter(CTYPE_FLOAT, "f"));
  auto ft = std::make_shared<FunctionType>(TypedReturnValue(CTYPE_INT), std::move(pv));
  TypedefType ptf("foo", std::make_shared<Pointer>(std::move(ft)));
  ft = nullptr;
  EXPECT_STRCASEEQ(ptf.getFullDeclarationName().c_str(), "foo");
}

TEST(FunctionType, checkPrefix)
{
  Parameter::Vector pv{};
  pv.emplace_back(NamedParameter(CTYPE_FLOAT, "f"));
  FunctionType ft(TypedReturnValue(CTYPE_INT), std::move(pv));
  ASSERT_STREQ(ft.getDeclarationPrefix().c_str(), "int(");
}

TEST(FunctionType, checkPostfix)
{
  Parameter::Vector pv{};
  pv.emplace_back(NamedParameter(CTYPE_FLOAT, "f"));
  FunctionType ft(TypedReturnValue(CTYPE_INT), std::move(pv));
  // This will need to be modified once the bug to also print the parameter name is fix.
  ASSERT_STREQ(ft.getDeclarationPostfix().c_str(), ")(float)");
}
