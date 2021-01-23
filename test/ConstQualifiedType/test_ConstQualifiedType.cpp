#include <gtest/gtest.h>

#include <ConstQualifiedType.h>
#include <EasyMock_CType.h>
#include <Pointer.h>

#include <string>

TEST(ConstQualifiedType, isConst)
{
  ConstQualifiedType cqt(new CType(CTYPE_CHAR));
  ASSERT_TRUE(cqt.isConst());
}

TEST(ConstQualifiedType, isAnonymous)
{
  ConstQualifiedType cqt(new CType(CTYPE_CHAR));
  ASSERT_FALSE(cqt.isAnonymous());
}

TEST(ConstQualifiedType, getFullDeclarationName)
{
  ConstQualifiedType cqt(new CType(CTYPE_CHAR));
  ASSERT_STREQ(cqt.getFullDeclarationName().c_str(), "char const");
}

TEST(ConstQualifiedType, getFullNonQualifiedDeclarationName)
{
  ConstQualifiedType cqt(new CType(CTYPE_CHAR));
  ASSERT_STREQ(cqt.getFullNonQualifiedDeclarationName().c_str(), "char");
}

TEST(ConstQualifiedType, typedef_getFullDeclarationName)
{
  ConstQualifiedType cqt { new CType(CTYPE_CHAR, "foo") };
  ASSERT_STREQ(cqt.getFullDeclarationName().c_str(), "foo const");
}

TEST(ConstQualifiedType, typedef_getFullNonQualifiedDeclarationName)
{
  ConstQualifiedType cqt { new CType(CTYPE_CHAR, "foo") };
  ASSERT_STREQ(cqt.getFullNonQualifiedDeclarationName().c_str(), "foo");
}
