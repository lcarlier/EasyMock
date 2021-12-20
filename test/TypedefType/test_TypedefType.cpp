#include <gtest/gtest.h>

#include <TypedefType.h>
#include <StructType.h>
#include <Pointer.h>
#include <ConstQualifiedType.h>
#include <EasyMock_CType.h>

#include <string>

TEST(TypedefType, isAnonymous)
{
  auto s = std::make_shared<StructType>("", false);
  TypedefType td {"t_def", s};
  ASSERT_FALSE(td.isAnonymous());
  ASSERT_TRUE(s->getRawType()->isAnonymous());
}

TEST(TypedefType, constIsAnonymous)
{
  auto s = std::make_shared<StructType>("", false);
  TypedefType td {"t_def", s};
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
  TypedefType td{"int_t",std::make_shared<CType>(CTYPE_INT)};
  ASSERT_TRUE(td.containsTypeDef());
}

TEST(ContainsTypeDef, pointerToTypedef)
{
  Pointer p{std::make_shared<TypedefType>("int_t", std::make_shared<CType>(CTYPE_INT))};
  ASSERT_TRUE(p.containsTypeDef());
}

TEST(ContainsTypeDef, pointerToPointerTypedef)
{
  Pointer p{std::make_shared<Pointer>(std::make_shared<TypedefType>("int_t", std::make_shared<CType>(CTYPE_INT)))};
  ASSERT_TRUE(p.containsTypeDef());
}

TEST(ContainsTypeDef, constTypedef)
{
  ConstQualifiedType cq{std::make_shared<TypedefType>("int_t", std::make_shared<CType>(CTYPE_INT))};
  ASSERT_TRUE(cq.containsTypeDef());
}

TEST(ContainsTypeDef, constPointerTypedef)
{
  ConstQualifiedType cq{std::make_shared<Pointer>(std::make_shared<TypedefType>("int_t", std::make_shared<CType>(CTYPE_INT)))};
  ASSERT_TRUE(cq.containsTypeDef());
}
