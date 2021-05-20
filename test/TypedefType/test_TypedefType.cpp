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
  ASSERT_FALSE(s->getRawType()->isAnonymous());
}

TEST(TypedefType, constIsAnonymous)
{
  StructType *s = new StructType("", false);
  TypedefType td {"t_def", new ConstQualifiedType{ s }};
  ASSERT_FALSE(s->getRawType()->isAnonymous());
}
