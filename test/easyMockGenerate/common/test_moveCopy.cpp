#include <gtest/gtest.h>
#include <CType.h>
#include <Function.h>
#include <Parameter.h>
#include <StructField.h>
#include <StructType.h>
#include <AutoCleanVectorPtr.h>

TEST(moveCopy, CType)
{
  CType ctype1(CTYPE_CHAR);
  CType ctype2(ctype1);
  ASSERT_EQ(ctype1, ctype2);

  CType ctype3(CTYPE_DOUBLE);
  ASSERT_NE(ctype3,ctype1);
  ctype3 = ctype1;
  ASSERT_EQ(ctype3,ctype1);

  CType ctype4 = std::move(ctype3);
  ASSERT_EQ(ctype4, ctype1);

  CType ctype6(CTYPE_DOUBLE);
  ASSERT_NE(ctype6, ctype2);
  ctype6 = std::move(ctype2);
  ASSERT_EQ(ctype6, ctype1);
}

TEST(moveCopy, Function)
{
  Function f1("foo", VoidReturnValue(), {});
  Function f2(f1);
  ASSERT_EQ(f1, f2);

  Function f3("bar", TypedReturnValue(CTYPE_INT), {});
  ASSERT_NE(f3,f1);
  f3 = f1;
  ASSERT_EQ(f3,f1);

  Function f4 = std::move(f3);
  ASSERT_EQ(f4, f1);

  Function f6("bar", TypedReturnValue(CTYPE_INT), {});
  ASSERT_NE(f6, f2);
  f6 = std::move(f2);
  ASSERT_EQ(f6, f1);
}

TEST(moveCopy, Parameter)
{
  Parameter p1(new CType(CTYPE_VOID), "v");
  Parameter p2(p1);
  ASSERT_EQ(p1, p2);

  Parameter p3(new CType(CTYPE_CHAR), "c");
  ASSERT_NE(p3,p1);
  p3 = p1;
  ASSERT_EQ(p3,p1);

  Parameter p4 = std::move(p3);
  ASSERT_EQ(p4, p1);

  Parameter p6(new CType(CTYPE_CHAR), "c");
  ASSERT_NE(p6, p2);
  p6 = std::move(p2);
  ASSERT_EQ(p6, p1);
}

TEST(moveCopy, ReturnValue)
{
  ReturnValue rv1 = VoidReturnValue();
  ReturnValue rv2(rv1);
  ASSERT_EQ(rv1, rv2);

  ReturnValue rv3 = StructReturnValue(new StructType("s1", {new StructField(CTYPE_INT, "a")}));
  ASSERT_NE(rv3,rv1);
  rv3 = rv1;
  ASSERT_EQ(rv3,rv1);

  ReturnValue rv4 = std::move(rv3);
  ASSERT_EQ(rv4, rv1);

  ReturnValue rv6 = StructReturnValue(new StructType("s1", {new StructField(CTYPE_INT, "a")}));
  ASSERT_NE(rv6, rv2);
  rv6 = std::move(rv2);
  ASSERT_EQ(rv6, rv1);
}

TEST(moveCopy, StructField)
{
  StructField f1(CTYPE_INT, "a");
  StructField f2(f1);
  ASSERT_EQ(f1, f2);

  StructField f3(new StructType("s", {new StructField(CTYPE_INT, "c"), new StructField(CTYPE_INT, "d")}), "e");
  ASSERT_NE(f3,f1);
  f3 = f1;
  ASSERT_EQ(f3,f1);

  StructField f4 = std::move(f3);
  ASSERT_EQ(f4, f1);

  StructField f6(new StructType("s", {new StructField(CTYPE_INT, "c"), new StructField(CTYPE_INT, "d")}), "e");
  ASSERT_NE(f6, f2);
  f6 = std::move(f2);
  ASSERT_EQ(f6, f1);
}

TEST(moveCopy, StructType)
{
  StructType st1("s", {new StructField(CTYPE_CHAR, "f")});
  StructType st2(st1);
  ASSERT_EQ(st1, st2);

  StructType st3("s", {new StructField(CTYPE_INT, "i")});
  ASSERT_NE(st3,st1);
  st3 = st1;
  ASSERT_EQ(st3,st1);

  StructType st4 = std::move(st3);
  ASSERT_EQ(st4, st1);

  StructType st6("s", {new StructField(CTYPE_INT, "i")});
  ASSERT_NE(st6, st2);
  st6 = std::move(st2);
  ASSERT_EQ(st6, st1);
}

TEST(moveCopy, PointerStructType)
{
  StructType st1("s", {new StructField(CTYPE_CHAR, "f")}, true);
  StructType st2(st1);
  ASSERT_EQ(st1, st2);

  StructType st3("s", {new StructField(CTYPE_INT, "i")}, true);
  ASSERT_NE(st3,st1);
  st3 = st1;
  ASSERT_EQ(st3,st1);

  StructType st4 = std::move(st3);
  ASSERT_EQ(st4, st1);

  StructType st6("s", {new StructField(CTYPE_INT, "i")}, true);
  ASSERT_NE(st6, st2);
  st6 = std::move(st2);
  ASSERT_EQ(st6, st1);
}

TEST(moveCopy, AutoCleanVectorPtr)
{
  AutoCleanVectorPtr<StructField> v1({new StructField(CTYPE_INT, "i"), new StructField(CTYPE_DOUBLE, "d")});
  AutoCleanVectorPtr<StructField> v2(v1);
  ASSERT_EQ(v1, v2);

  AutoCleanVectorPtr<StructField> v3({new StructField(CTYPE_DOUBLE, "d"), new StructField(CTYPE_INT, "i")});
  ASSERT_NE(v3,v1);
  v3 = v1;
  ASSERT_EQ(v3,v1);

  AutoCleanVectorPtr<StructField> v4 = std::move(v3);
  ASSERT_EQ(v4, v1);

  AutoCleanVectorPtr<StructField> v6({new StructField(CTYPE_DOUBLE, "d"), new StructField(CTYPE_INT, "i")});
  ASSERT_NE(v6, v2);
  v6 = std::move(v2);
  ASSERT_EQ(v6, v1);
}
