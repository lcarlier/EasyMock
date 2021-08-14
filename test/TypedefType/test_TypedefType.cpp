#include <gtest/gtest.h>

#include <TypedefType.h>
#include <StructType.h>
#include <Pointer.h>
#include <ConstQualifiedType.h>

#include <string>

TEST(TypedefType, isAnonymous)
{
  StructType *s = new StructType("", false);
  TypedefType td {"t_def", s};
  ASSERT_FALSE(td.isAnonymous());
  ASSERT_TRUE(s->getRawType()->isAnonymous());
}

TEST(TypedefType, constIsAnonymous)
{
  StructType *s = new StructType("", false);
  TypedefType td {"t_def", new ConstQualifiedType{ s }};
  ASSERT_FALSE(td.isAnonymous());
  ASSERT_TRUE(td.getTypee()->isAnonymous());
  ASSERT_TRUE(s->getRawType()->isAnonymous());
}
