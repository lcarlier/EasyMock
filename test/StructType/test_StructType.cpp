#include <gtest/gtest.h>

#include <StructType.h>

TEST(StructType, StructTypeConstructor)
{
  StructType st1("s", {new StructField(CTYPE_CHAR, "f")});
  ASSERT_FALSE(st1.isCType());
  ASSERT_TRUE(st1.isStruct());
}

TEST(StructType, PointerStructTypeConstructor)
{
  StructType st1("s", {new StructField(CTYPE_CHAR, "f")});
  ASSERT_FALSE(st1.isCType());
  ASSERT_TRUE(st1.isStruct());
}
