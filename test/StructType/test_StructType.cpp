#include <gtest/gtest.h>

#include <StructType.h>
#include <Pointer.h>
#include <IncompleteType.h>
#include <ComposableField.h>

#include <string>

TEST(StructType, StructTypeConstructor)
{
  bool isEmbeddedInOtherType = false;
  StructType st1("s", ComposableFieldItf::Vector({new ComposableField(CTYPE_CHAR, "f")}), isEmbeddedInOtherType);
  ASSERT_FALSE(st1.isCType());
  ASSERT_TRUE(st1.isStruct());
  ASSERT_FALSE(st1.isUnion());
  ASSERT_FALSE(st1.isDeclarationEmbeddedInOtherType());
  ASSERT_FALSE(st1.isAnonymous());
}

TEST(StructType, EmbeddedInOtherType)
{
  bool isEmbeddedInOtherType = true;

  StructType st1("s", ComposableFieldItf::Vector({new ComposableField(CTYPE_CHAR, "f")}), isEmbeddedInOtherType);
  ASSERT_FALSE(st1.isCType());
  ASSERT_TRUE(st1.isStruct());
  ASSERT_FALSE(st1.isUnion());
  ASSERT_TRUE(st1.isDeclarationEmbeddedInOtherType());
}

TEST(StructType, AnonymousStructGetFullDeclarationName)
{
  bool isEmbeddedInOtherType = false;

  StructType st1("", ComposableFieldItf::Vector({new ComposableField(CTYPE_CHAR, "f")}), isEmbeddedInOtherType);
  ASSERT_FALSE(st1.isCType());
  ASSERT_TRUE(st1.isStruct());
  ASSERT_FALSE(st1.isUnion());

  std::string uniqueName("struct");

  ASSERT_STREQ(uniqueName.c_str(), st1.getFullDeclarationName().c_str());
}

TEST(StructType, PtrToPtrRecur)
{
  StructType t("ptrToPtrStructRecur", false);
  Pointer *p = new Pointer(new IncompleteType(t, IncompleteType::Type::STRUCT));
  Pointer *p2p = new Pointer(p);
  t.addField(new ComposableField(p2p, "r"));
  //Nothing to check in particular. The address sanitiser shouldn't return any error
}
