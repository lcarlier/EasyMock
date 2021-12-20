#include <gtest/gtest.h>

#include <StructType.h>
#include <Pointer.h>
#include <IncompleteType.h>
#include <ComposableField.h>

#include <string>

TEST(StructType, StructTypeConstructor)
{
  bool isEmbeddedInOtherType = false;
  ComposableType::ComposableFieldTypeVector fieldVector{};
  fieldVector.emplace_back(ComposableField(CTYPE_CHAR, "f"));
  StructType st1("s", std::move(fieldVector), isEmbeddedInOtherType);
  ASSERT_FALSE(st1.isCType());
  ASSERT_TRUE(st1.isStruct());
  ASSERT_FALSE(st1.isUnion());
  ASSERT_FALSE(st1.isDeclarationEmbeddedInOtherType());
  ASSERT_FALSE(st1.isAnonymous());
}

TEST(StructType, EmbeddedInOtherType)
{
  bool isEmbeddedInOtherType = true;

  ComposableType::ComposableFieldTypeVector fieldVector;
  fieldVector.emplace_back(ComposableField(CTYPE_CHAR, "f"));
  StructType st1("s", std::move(fieldVector), isEmbeddedInOtherType);
  ASSERT_FALSE(st1.isCType());
  ASSERT_TRUE(st1.isStruct());
  ASSERT_FALSE(st1.isUnion());
  ASSERT_TRUE(st1.isDeclarationEmbeddedInOtherType());
}

TEST(StructType, AnonymousStructGetFullDeclarationName)
{
  bool isEmbeddedInOtherType = false;

  ComposableType::ComposableFieldTypeVector vectorField{};
  vectorField.emplace_back(ComposableField(CTYPE_CHAR, "f"));
  StructType st1("", std::move(vectorField), isEmbeddedInOtherType);
  ASSERT_FALSE(st1.isCType());
  ASSERT_TRUE(st1.isStruct());
  ASSERT_FALSE(st1.isUnion());

  std::string uniqueName("struct");

  ASSERT_STREQ(uniqueName.c_str(), st1.getFullDeclarationName().c_str());
}

TEST(StructType, PtrToPtrRecur)
{
  StructType t("ptrToPtrStructRecur", false);
  auto p = std::make_shared<Pointer>(std::make_shared<IncompleteType>(t, IncompleteType::Type::STRUCT));
  auto p2p = std::make_shared<Pointer>(std::move(p));
  t.addField(ComposableField(std::move(p2p), "r"));
  //Nothing to check in particular. The address sanitiser shouldn't return any error
}
