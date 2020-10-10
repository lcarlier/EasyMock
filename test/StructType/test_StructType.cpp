#include <gtest/gtest.h>

#include <StructType.h>
#include <Pointer.h>

#include <string>

TEST(StructType, StructTypeConstructor)
{
  bool isEmbeddedInOtherType = false;
  StructType st1("s", ComposableField::Vector({new ComposableField(CTYPE_CHAR, "f")}), isEmbeddedInOtherType);
  ASSERT_FALSE(st1.isCType());
  ASSERT_TRUE(st1.isStruct());
  ASSERT_FALSE(st1.isUnion());
  ASSERT_FALSE(st1.isDeclarationEmbeddedInOtherType());
  ASSERT_FALSE(st1.isAnonymous());
}

TEST(StructType, EmbeddedInOtherType)
{
  bool isEmbeddedInOtherType = true;

  StructType st1("s", ComposableField::Vector({new ComposableField(CTYPE_CHAR, "f")}), isEmbeddedInOtherType);
  ASSERT_FALSE(st1.isCType());
  ASSERT_TRUE(st1.isStruct());
  ASSERT_FALSE(st1.isUnion());
  ASSERT_TRUE(st1.isDeclarationEmbeddedInOtherType());
}

TEST(StructType, TestAnonymous)
{
  for(unsigned int i = 0; i < 3; i++)
  {
    StructType st("", ComposableField::Vector({new ComposableField(CTYPE_CHAR, "f")}), false);
    ASSERT_TRUE(st.isAnonymous());
    ASSERT_EQ(st.m_anonymous_number, i) << "i: " << i;

    StructType copySt(st);
    ASSERT_TRUE(copySt.isAnonymous());
    ASSERT_EQ(copySt.m_anonymous_number, i) << "i: " << i;
  }
}

TEST(StructType, UniqueNameAnonymous)
{
  bool isEmbeddedInOtherType = true;

  ComposableType::m_number_of_anonymous_composable_type = 0;
  for(int i = 0; i < 3; i++)
  {
    StructType st1("", ComposableField::Vector({new ComposableField(CTYPE_CHAR, "f")}), isEmbeddedInOtherType);
    ASSERT_FALSE(st1.isCType());
    ASSERT_TRUE(st1.isStruct());
    ASSERT_FALSE(st1.isUnion());
    ASSERT_TRUE(st1.isDeclarationEmbeddedInOtherType());
    std::string uniqueName("struct_anonymous_type_in_file_0_number_");
    uniqueName.append(std::to_string(i+1));
    ASSERT_STREQ(uniqueName.c_str(), st1.getUniqueName().c_str());
  }
}

TEST(StructType, UniqueNameStruct)
{
  bool isEmbeddedInOtherType = true;

  StructType st1("inOther", ComposableField::Vector({new ComposableField(CTYPE_CHAR, "f")}), isEmbeddedInOtherType);
  ASSERT_FALSE(st1.isCType());
  ASSERT_TRUE(st1.isStruct());
  ASSERT_FALSE(st1.isUnion());
  ASSERT_TRUE(st1.isDeclarationEmbeddedInOtherType());
  std::string uniqueName("struct_inOther");

  ASSERT_STREQ(uniqueName.c_str(), st1.getUniqueName().c_str());
}

TEST(StructType, UniqueNamTypeDefStruct)
{
  bool isEmbeddedInOtherType = true;

  StructType st1("", "typeDefInOther", ComposableField::Vector({new ComposableField(CTYPE_CHAR, "f")}), isEmbeddedInOtherType);
  ASSERT_FALSE(st1.isCType());
  ASSERT_TRUE(st1.isStruct());
  ASSERT_FALSE(st1.isUnion());
  ASSERT_TRUE(st1.isDeclarationEmbeddedInOtherType());
  std::string uniqueName("typeDefInOther");

  ASSERT_STREQ(uniqueName.c_str(), st1.getUniqueName().c_str());
}

TEST(StructType, PtrToPtrRecur)
{
  StructType t("ptrToPtrStructRecur", false);
  Pointer *p = new Pointer(&t);
  Pointer *p2p = new Pointer(p);
  ComposableField::attributes fieldAttr =
  {
    .arraySize = -1,
    .isIncompleteTypeField = true
  };
  t.addField(new ComposableField(p2p, "r", fieldAttr));
  //Nothing to check in particular. The address sanitiser shouldn't return any error
}
