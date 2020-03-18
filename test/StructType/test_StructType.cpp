#include <gtest/gtest.h>

#include <StructType.h>

TEST(StructType, StructTypeConstructor)
{
  StructType st1("s", {new ComposableField(CTYPE_CHAR, "f")});
  ASSERT_FALSE(st1.isCType());
  ASSERT_TRUE(st1.isStruct());
  ASSERT_FALSE(st1.isUnion());
}

TEST(StructType, PointerStructTypeConstructor)
{
  StructType st1("s", {new ComposableField(CTYPE_CHAR, "f")});
  ASSERT_FALSE(st1.isCType());
  ASSERT_TRUE(st1.isStruct());
  ASSERT_FALSE(st1.isUnion());
}
