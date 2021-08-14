#include <gtest/gtest.h>

#include <TypedefType.h>
#include <StructType.h>
#include <Pointer.h>
#include <ConstQualifiedType.h>
#include <EasyMock_CType.h>

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

TEST(ContainsTypeDef, notContainsTypedef)
{
  CType c{CTYPE_INT};
  ASSERT_FALSE(c.containsTypeDef());
}

TEST(ContainsTypeDef, simple)
{
  TypedefType td{"int_t",new CType {CTYPE_INT}};
  ASSERT_TRUE(td.containsTypeDef());
}

TEST(ContainsTypeDef, pointerToTypedef)
{
  Pointer p{new TypedefType{"int_t", new CType{CTYPE_INT}}};
  ASSERT_TRUE(p.containsTypeDef());
}

TEST(ContainsTypeDef, pointerToPointerTypedef)
{
  Pointer p{new Pointer{new TypedefType{"int_t", new CType{CTYPE_INT}}}};
  ASSERT_TRUE(p.containsTypeDef());
}

TEST(ContainsTypeDef, constTypedef)
{
  ConstQualifiedType cq{new TypedefType{"int_t", new CType{CTYPE_INT}}};
  ASSERT_TRUE(cq.containsTypeDef());
}

TEST(ContainsTypeDef, constPointerTypedef)
{
  ConstQualifiedType cq{new Pointer{new TypedefType{"int_t", new CType{CTYPE_INT}}}};
  ASSERT_TRUE(cq.containsTypeDef());
}