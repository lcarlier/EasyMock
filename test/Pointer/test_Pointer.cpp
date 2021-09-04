#include <gtest/gtest.h>

#include <EasyMock_CType.h>
#include <Pointer.h>
#include <ConstQualifiedType.h>
#include <TypedefType.h>

#include <string>

TEST(Pointer, getFullDeclarationName)
{
  ConstQualifiedType* cqt = new ConstQualifiedType(new CType(CTYPE_CHAR));
  Pointer p { cqt };
  ASSERT_STREQ(p.getFullDeclarationName().c_str(), "char const*");
}

TEST(Pointer, constPtr_getFullDeclarationName)
{
  Pointer* p = new Pointer(new CType(CTYPE_CHAR));
  ConstQualifiedType pcqt { p };
  ASSERT_STREQ(pcqt.getFullDeclarationName().c_str(), "char* const");
}

TEST(Pointer, constPtr_constPointed_getFullDeclarationName)
{
  ConstQualifiedType* cqt = new ConstQualifiedType(new CType(CTYPE_CHAR));
  Pointer* p = new Pointer(cqt);
  ConstQualifiedType pcqt { p };
  ASSERT_STREQ(pcqt.getFullDeclarationName().c_str(), "char const* const");
}

TEST(Pointer, typedef_getFullDeclarationName)
{
  ConstQualifiedType* cqt = new ConstQualifiedType(new TypedefType("foo", new CType(CTYPE_CHAR)));
  Pointer p { cqt };
  ASSERT_STREQ(p.getFullDeclarationName().c_str(), "foo const*");
}

TEST(Pointer, typedef_constPtr_constPointed_getFullDeclarationName)
{
  ConstQualifiedType* cqt = new ConstQualifiedType(new TypedefType("foo", new CType(CTYPE_CHAR)));
  Pointer* p = new Pointer { cqt };
  ConstQualifiedType pcqt(p);
  ASSERT_STREQ(pcqt.getFullDeclarationName().c_str(), "foo const* const");
}

TEST(Pointer, typedef_getFullDeclarationName_naked)
{
  ConstQualifiedType* cqt = new ConstQualifiedType(new TypedefType("foo", new CType(CTYPE_CHAR)));
  Pointer p { cqt };
  ASSERT_STREQ(p.getFullDeclarationName().c_str(), "foo const*");
}

TEST(Pointer, typedef_toPointer)
{
  TypedefType t { "foo", new Pointer(new CType(CTYPE_UINT)) };
  ASSERT_STREQ(t.getFullDeclarationName().c_str(), "foo");
}

TEST(Pointer, constVoidPointer)
{
  Pointer pointer{new ConstQualifiedType(new CType(CTYPE_VOID)) };
  ASSERT_STREQ(pointer.getFullDeclarationName().c_str(), "void const*");
}

TEST(Pointer, constPtr_isPointer)
{
  ConstQualifiedType cqt{new Pointer(new CType(CTYPE_VOID)) };
  ASSERT_FALSE(cqt.isPointer());
}

TEST(Pointer, constPtr_asPointer)
{
  ConstQualifiedType cqt{new Pointer(new CType(CTYPE_VOID)) };
  ASSERT_FALSE(cqt.asPointer());
}
