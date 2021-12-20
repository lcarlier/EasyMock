#include <gtest/gtest.h>

#include <ConstQualifiedType.h>
#include <EasyMock_CType.h>
#include <Pointer.h>
#include <TypedefType.h>

#include <string>

TEST(ConstQualifiedType, isConst)
{
  ConstQualifiedType cqt(std::make_shared<CType>(CTYPE_CHAR));
  ASSERT_TRUE(cqt.isQualified());
  ASSERT_TRUE(cqt.isConst());
}

TEST(ConstQualifiedType, isAnonymous)
{
  ConstQualifiedType cqt(std::make_shared<CType>(CTYPE_CHAR));
  ASSERT_FALSE(cqt.isAnonymous());
}

TEST(ConstQualifiedType, getFullDeclarationName)
{
  ConstQualifiedType cqt(std::make_shared<CType>(CTYPE_CHAR));
  ASSERT_STREQ(cqt.getFullDeclarationName().c_str(), "char const");
}

TEST(ConstQualifiedType, getFullNonQualifiedDeclarationName)
{
  ConstQualifiedType cqt(std::make_shared<CType>(CTYPE_CHAR));
  TypeItf* unqualified = cqt.unqualify();
  ASSERT_STREQ(unqualified->getFullDeclarationName().c_str(), "char");
}

TEST(ConstQualifiedType, typedef_getFullDeclarationName)
{
  ConstQualifiedType cqt { std::make_shared<TypedefType>("foo", std::make_shared<CType>(CTYPE_CHAR)) };
  ASSERT_STREQ(cqt.getFullDeclarationName().c_str(), "foo const");
}

TEST(ConstQualifiedType, typedef_getFullNonQualifiedDeclarationName)
{
  TypedefType cqt { "foo" , std::make_shared<ConstQualifiedType>(std::make_shared<CType>(CTYPE_CHAR)) };
  TypeItf* unqualified = cqt.unqualify();
  ASSERT_STREQ(unqualified->getFullDeclarationName().c_str(), "foo");
}
