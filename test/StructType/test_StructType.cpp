#include <gtest/gtest.h>

#include <StructType.h>

#include <string>

TEST(StructType, StructTypeConstructor)
{
  bool isEmbeddedInOtherType = false;
  StructType st1("s", ComposableField::Vector({new ComposableField(CTYPE_CHAR, "f")}), isEmbeddedInOtherType);
  ASSERT_FALSE(st1.isCType());
  ASSERT_TRUE(st1.isStruct());
  ASSERT_FALSE(st1.isUnion());
  ASSERT_FALSE(st1.isEmbeddedInOtherType());
}

TEST(StructType, EmbeddedInOtherType)
{
  bool isEmbeddedInOtherType = true;

  StructType st1("s", ComposableField::Vector({new ComposableField(CTYPE_CHAR, "f")}), isEmbeddedInOtherType);
  ASSERT_FALSE(st1.isCType());
  ASSERT_TRUE(st1.isStruct());
  ASSERT_FALSE(st1.isUnion());
  ASSERT_TRUE(st1.isEmbeddedInOtherType());
}

TEST(StructType, UniqueName)
{
  bool isEmbeddedInOtherType = true;

  for(int i = 0; i < 3; i++)
  {
    StructType st1("", ComposableField::Vector({new ComposableField(CTYPE_CHAR, "f")}), isEmbeddedInOtherType);
    ASSERT_FALSE(st1.isCType());
    ASSERT_TRUE(st1.isStruct());
    ASSERT_FALSE(st1.isUnion());
    ASSERT_TRUE(st1.isEmbeddedInOtherType());
    std::string uniqueName("struct_anonymous_type_in_file_0_number_");
    uniqueName.append(std::to_string(i+1));
    ASSERT_STREQ(uniqueName.c_str(), st1.getUniqueName().c_str());
  }
}
