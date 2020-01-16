#include <gtest/gtest.h>
#include <CType.h>
#include <Function.h>
#include <Parameter.h>
#include <ReturnValue.h>
#include <StructType.h>
#include <AutoCleanVectorPtr.h>

TEST(equality, CType)
{
  CType c1(CTYPE_INT);
  CType c2(CTYPE_INT);
  CType c3(CTYPE_DOUBLE);

  ASSERT_EQ(c1,c2);
  ASSERT_NE(c1,c3);
  ASSERT_NE(c2,c3);
}

TEST(equality, FunctionWithDifferentParams)
{
  Function f1("foo", VoidReturnValue(), {NamedParameter(CTYPE_INT, "foo")});
  Function f2("foo", VoidReturnValue(), {NamedParameter(CTYPE_DOUBLE, "foo")});

  ASSERT_NE(f1, f2);
}

TEST(equality, FunctionWithSameParamsButWithDifferentName)
{
  Function f1("foo", VoidReturnValue(), {NamedParameter(CTYPE_INT, "foo")});
  Function f2("foo", VoidReturnValue(), {NamedParameter(CTYPE_INT, "bar")});

  ASSERT_EQ(f1, f2);
}

TEST(equality, FunctionWithSameParamsButReturnValueIsDifferent)
{
  Function f1("foo", TypedReturnValue(CTYPE_INT), {NamedParameter(CTYPE_INT, "foo")});
  Function f2("foo", TypedReturnValue(CTYPE_DOUBLE), {NamedParameter(CTYPE_INT, "bar")});

  ASSERT_NE(f1, f2);
}

TEST(equality, FunctionSameParamsSwaped)
{
  Function f1("foo", VoidReturnValue(), {NamedParameter(CTYPE_INT, "aInt"), NamedParameter(CTYPE_DOUBLE, "aDouble")});
  Function f2("foo", VoidReturnValue(), {NamedParameter(CTYPE_DOUBLE, "aDouble"), NamedParameter(CTYPE_INT, "aInt")});

  ASSERT_NE(f1, f2);
}

TEST(equality, ParameterSameParam)
{
  Parameter p1(new CType(CTYPE_VOID), "v1");
  Parameter p2(new CType(CTYPE_VOID), "v2");

  //Even though name is different parameters are the same
  ASSERT_EQ(p1, p2);
}

TEST(equality, ParameterDifferentParam)
{
  Parameter p1(new CType(CTYPE_INT), "p1");
  Parameter p2(new CType(CTYPE_VOID), "p1");

  ASSERT_NE(p1, p2);
}

TEST(equality, ReturnValueSame)
{
  ReturnValue rv1;
  ReturnValue rv2;

  ASSERT_EQ(rv1, rv2);
}

TEST(equality, ReturnValueDifferent)
{
  ReturnValue rv1 = VoidReturnValue();
  ReturnValue rv2 = TypedReturnValue(CTYPE_INT);

  ASSERT_NE(rv1, rv2);
}

TEST(equality, StructFieldSame)
{
  StructField f1(CTYPE_INT, "a");
  StructField f2(CTYPE_INT, "a");

  ASSERT_EQ(f1, f2);

  StructField f3(new StructType("s", {new StructField(CTYPE_INT, "c"), new StructField(CTYPE_INT, "d")}), "e");
  StructField f4(new StructType("s", {new StructField(CTYPE_INT, "c"), new StructField(CTYPE_INT, "d")}), "e");

  ASSERT_EQ(f3, f4);
}

TEST(equality, StructFieldDifferent)
{
  StructField f1(CTYPE_INT, "a");
  StructField f2(CTYPE_DOUBLE, "a");

  ASSERT_NE(f1, f2);

  StructField f3(new StructType("s", {new StructField(CTYPE_INT, "c"), new StructField(CTYPE_INT, "d")}), "e");
  StructField f4(new CType(CTYPE_INT), "f");

  ASSERT_NE(f3, f4);
}

TEST(equality, StructTypeSame)
{
  StructType s1("s", {});
  StructType s2("s", {});

  ASSERT_EQ(s1, s2);

  StructType s3("s", {new StructField(CTYPE_CHAR, "f")});
  StructType s4("s", {new StructField(CTYPE_CHAR, "f")});

  ASSERT_EQ(s3, s4);
}

TEST(equality, PointerStructTypeSame)
{
  StructType s1("s", {}, true);
  StructType s2("s", {}, true);

  ASSERT_EQ(s1, s2);

  StructType s3("s", {new StructField(CTYPE_CHAR, "f")}, true);
  StructType s4("s", {new StructField(CTYPE_CHAR, "f")}, true);

  ASSERT_EQ(s3, s4);
}

TEST(equality, StructTypeDifferent)
{
  StructType s1("s", {});
  StructType s2("s", {new StructField(CTYPE_CHAR, "f")});

  ASSERT_NE(s1,s2);
}

TEST(equality, PointerStructTypeDifferent)
{
  StructType s1("s", {}, true);
  StructType s2("s", {new StructField(CTYPE_CHAR, "f")}, true);

  ASSERT_NE(s1,s2);
}

TEST(equality, AutoCleanVectorSame)
{
  AutoCleanVectorPtr<int> v1({new int(1), new int(2)});
  AutoCleanVectorPtr<int> v2({new int(1), new int(2)});

  ASSERT_EQ(v1, v2);
}

TEST(equality, AutoCleanVectorDifferent)
{
  AutoCleanVectorPtr<int> v1({new int(1), new int(2)});
  AutoCleanVectorPtr<int> v2({new int(2), new int(1)});

  ASSERT_NE(v1, v2);
}
