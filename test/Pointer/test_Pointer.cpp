#include <gtest/gtest.h>

#include <EasyMock_CType.h>
#include <Pointer.h>
#include <ConstQualifiedType.h>
#include <TypedefType.h>

#include <string>

TEST(Pointer, getFullDeclarationName)
{
  auto cqt = std::make_shared<ConstQualifiedType>(std::make_shared<CType>(CTYPE_CHAR));
  Pointer p { std::move(cqt) };
  ASSERT_STREQ(p.getFullDeclarationName().c_str(), "char const*");
}

TEST(Pointer, constPtr_getFullDeclarationName)
{
  auto p = std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_CHAR));
  ConstQualifiedType pcqt { std::move(p) };
  ASSERT_STREQ(pcqt.getFullDeclarationName().c_str(), "char* const");
}

TEST(Pointer, constPtr_constPointed_getFullDeclarationName)
{
  auto cqt = std::make_shared<ConstQualifiedType>(std::make_shared<CType>(CTYPE_CHAR));
  auto p = std::make_shared<Pointer>(std::move(cqt));
  ConstQualifiedType pcqt { std::move(p) };
  ASSERT_STREQ(pcqt.getFullDeclarationName().c_str(), "char const* const");
}

TEST(Pointer, typedef_getFullDeclarationName)
{
  auto cqt = std::make_shared<ConstQualifiedType>(std::make_shared<TypedefType>("foo", std::make_shared<CType>(CTYPE_CHAR)));
  Pointer p { std::move(cqt) };
  ASSERT_STREQ(p.getFullDeclarationName().c_str(), "foo const*");
}

TEST(Pointer, typedef_constPtr_constPointed_getFullDeclarationName)
{
  auto cqt = std::make_shared<ConstQualifiedType>(std::make_shared<TypedefType>("foo", std::make_shared<CType>(CTYPE_CHAR)));
  auto p = std::make_shared<Pointer>(std::move(cqt));
  ConstQualifiedType pcqt(std::move(p));
  ASSERT_STREQ(pcqt.getFullDeclarationName().c_str(), "foo const* const");
}

TEST(Pointer, typedef_getFullDeclarationName_naked)
{
  auto cqt = std::make_shared<ConstQualifiedType>(std::make_shared<TypedefType>("foo", std::make_shared<CType>(CTYPE_CHAR)));
  Pointer p { std::move(cqt) };
  ASSERT_STREQ(p.getFullDeclarationName().c_str(), "foo const*");
}

TEST(Pointer, typedef_toPointer)
{
  TypedefType t { "foo", std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_UINT)) };
  ASSERT_STREQ(t.getFullDeclarationName().c_str(), "foo");
}

TEST(Pointer, constVoidPointer)
{
  Pointer pointer{std::make_shared<ConstQualifiedType>(std::make_shared<CType>(CTYPE_VOID)) };
  ASSERT_STREQ(pointer.getFullDeclarationName().c_str(), "void const*");
}

TEST(Pointer, constPtr_isPointer)
{
  ConstQualifiedType cqt{std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_VOID)) };
  ASSERT_FALSE(cqt.isPointer());
}

TEST(Pointer, constPtr_asPointer)
{
  ConstQualifiedType cqt{std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_VOID)) };
  ASSERT_FALSE(cqt.asPointer());
}
