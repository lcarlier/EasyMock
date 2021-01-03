#include <gtest/gtest.h>

#include <EasyMock_CType.h>
#include <gtestPrintClasses.h>

typedef struct
{
  easyMock_cTypes_t signedType;
  easyMock_cTypes_t unsignedType;
} ctype_params;

class ctype_unsigned_testcase : public ::testing::TestWithParam<ctype_params>
{
};

TEST_P(ctype_unsigned_testcase, ctypeConstructor)
{
  const ParamType &params = GetParam();

  CType signedT = CType(params.signedType);
  ASSERT_EQ(signedT.getName(), easyMock_arrayCTypeStr[params.signedType]);

  CType unsignedT = CType(params.unsignedType);
  ASSERT_EQ(unsignedT.getName(), easyMock_arrayCTypeStr[params.unsignedType]);
}

TEST_P(ctype_unsigned_testcase, ctypeSetUnsigned)
{
  const ParamType &params = GetParam();

  CType t = CType(params.signedType);

  ASSERT_TRUE(t.setUnsigned(true));

  ASSERT_EQ(t.getCType(), params.unsignedType);
  ASSERT_EQ(t.getName(), easyMock_arrayCTypeStr[params.unsignedType]);

  ASSERT_TRUE(t.setUnsigned(false));

  ASSERT_EQ(t.getCType(), params.signedType);
  ASSERT_EQ(t.getName(), easyMock_arrayCTypeStr[params.signedType]);
}

static ctype_params test_unsigned_params[]
{
#if IS_CHAR_DEFAULT_SIGNED
  {CTYPE_CHAR, CTYPE_UCHAR},
#endif
  {CTYPE_SCHAR, CTYPE_UCHAR},
  {CTYPE_SHORT, CTYPE_USHORT},
  {CTYPE_INT, CTYPE_UINT},
  {CTYPE_LONG, CTYPE_ULONG},
  {CTYPE_LONG_LONG, CTYPE_ULONG_LONG}
};

INSTANTIATE_TEST_CASE_P(CtypeUnsignedTypes, ctype_unsigned_testcase, ::testing::ValuesIn(test_unsigned_params));

class ctype_signed_only_testcase : public ::testing::TestWithParam<easyMock_cTypes_t>
{
};

TEST_P(ctype_signed_only_testcase, ctypeSetUnsigned)
{
  const ParamType &param = GetParam();

  const easyMock_cTypes_t &e_ctype = param;

  CType t = CType(e_ctype);

  ASSERT_FALSE(t.setUnsigned(true));
  ASSERT_FALSE(t.setUnsigned(false));

  ASSERT_EQ(t.getCType(), e_ctype);
  ASSERT_EQ(t.getName(), easyMock_arrayCTypeStr[e_ctype]);
}

static easyMock_cTypes_t test_signed_only_params[]
{
  CTYPE_DOUBLE,
  CTYPE_FLOAT,
  CTYPE_LONG_DOUBLE,
  CTYPE_VOID
};

INSTANTIATE_TEST_CASE_P(CtypeSignedType, ctype_signed_only_testcase, ::testing::ValuesIn(test_signed_only_params));

TEST(ctype_char_signed_unsigned, naked_char_default)
{
  CType c(CTYPE_CHAR);
  CType nc(CTYPE_CHAR);
  CType sc(CTYPE_SCHAR);
  CType uc(CTYPE_UCHAR);

  ASSERT_EQ(c, nc);
  ASSERT_NE(c, sc);
  ASSERT_NE(c, uc);
#if IS_CHAR_DEFAULT_SIGNED
  ASSERT_TRUE(c.setUnsigned(true));
  ASSERT_NE(c, nc);
  ASSERT_NE(c, sc);
  ASSERT_EQ(c, uc);

  ASSERT_TRUE(c.setUnsigned(false));
#else
  ASSERT_TRUE(c.setUnsigned(false));
  ASSERT_NE(c, nc);
  ASSERT_EQ(c, sc);
  ASSERT_NE(c, uc);

  ASSERT_TRUE(c.setUnsigned(true));
#endif
  ASSERT_EQ(c, nc);
  ASSERT_NE(c, sc);
  ASSERT_NE(c, uc);
}

TEST(ctype_char_signed_unsigned, signed_char)
{
  CType sc(CTYPE_SCHAR);
  CType ref_sc(CTYPE_SCHAR);
  CType c(CTYPE_CHAR);
  CType uc(CTYPE_UCHAR);

  ASSERT_EQ(sc, ref_sc);
  ASSERT_NE(sc, c);
  ASSERT_NE(sc, uc);

  ASSERT_TRUE(sc.setUnsigned(true));
  ASSERT_NE(sc, ref_sc);
  ASSERT_NE(sc, c);
  ASSERT_EQ(sc, uc);

  ASSERT_TRUE(sc.setUnsigned(false));
  ASSERT_EQ(sc, ref_sc);
  ASSERT_NE(sc, c);
  ASSERT_NE(sc, uc);
}

TEST(ctype_char_signed_unsigned, unsigned_signed_char)
{
  CType uc(CTYPE_UCHAR);
  CType ref_uc(CTYPE_UCHAR);
  CType c(CTYPE_CHAR);
  CType sc(CTYPE_SCHAR);

  ASSERT_EQ(uc, ref_uc);
  ASSERT_NE(uc, c);
  ASSERT_NE(uc, sc);

  ASSERT_TRUE(uc.setUnsigned(false));
  ASSERT_NE(uc, ref_uc);
  ASSERT_NE(uc, c);
  ASSERT_EQ(uc, sc);

  ASSERT_TRUE(uc.setUnsigned(true));
  ASSERT_EQ(uc, ref_uc);
  ASSERT_NE(uc, c);
  ASSERT_NE(uc, sc);
}

