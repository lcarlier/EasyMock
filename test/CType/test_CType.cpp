#include <gtest/gtest.h>

#include <CType.h>

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

TEST_P(ctype_unsigned_testcase, ctypeConstructorPointer)
{
  const ParamType &params = GetParam();

  std::string signedPointerName(easyMock_arrayCTypeStr[params.signedType]);
  signedPointerName.push_back('*');
  CType signedPtrT = CType(params.signedType, true);
  ASSERT_TRUE(signedPtrT.isPointer());
  ASSERT_EQ(signedPtrT.getName(), signedPointerName.c_str());

  std::string unsignedPointerName(easyMock_arrayCTypeStr[params.unsignedType]);
  unsignedPointerName.push_back('*');
  CType unsignedPtrT = CType(params.unsignedType, true);
  ASSERT_TRUE(unsignedPtrT.isPointer());
  ASSERT_EQ(unsignedPtrT.getName(), unsignedPointerName.c_str());
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

#if 0
TEST_P(ctype_unsigned_testcase, ctypeSetPointers)
{
  const ParamType &params = GetParam();

  CType t = CType(params.signedType);

  ASSERT_FALSE(t.isPointer());

  ASSERT_EQ(t.getCType(), params.unsignedType);
  ASSERT_EQ(t.getName(), easyMock_arrayCTypeStr[params.unsignedType]);

  ASSERT_TRUE(t.set(false));

  ASSERT_EQ(t.getCType(), params.signedType);
  ASSERT_EQ(t.getName(), easyMock_arrayCTypeStr[params.signedType]);
}
#endif

static ctype_params test_unsigned_params[]
{
  {CTYPE_CHAR, CTYPE_UCHAR},
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
