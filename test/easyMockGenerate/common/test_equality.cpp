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

  TypeItf &tiC1 = c1;
  TypeItf &tiC2 = c2;
  TypeItf &tiC3 = c3;
  ASSERT_EQ(tiC1,tiC2);
  ASSERT_NE(tiC1,tiC3);
  ASSERT_NE(tiC2,tiC3);
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

TEST(equality, ParameterPointerSameParam)
{
  bool isPointer = true;
  Parameter p1(new CType(CTYPE_VOID), "v1", isPointer);
  Parameter p2(new CType(CTYPE_VOID), "v2", isPointer);

  //Even though name is different parameters are the same
  ASSERT_EQ(p1, p2);
}

TEST(equality, ParameterDifferentParam)
{
  Parameter p1(new CType(CTYPE_INT), "p1");
  Parameter p2(new CType(CTYPE_VOID), "p1");

  ASSERT_NE(p1, p2);
}

TEST(equality, ParameterPointerDifferentParam)
{
  bool isPointer = true;
  Parameter p1(new CType(CTYPE_INT), "p1", isPointer);
  Parameter p2(new CType(CTYPE_VOID), "p1", isPointer);

  ASSERT_NE(p1, p2);

  isPointer = true;
  Parameter p3(new CType(CTYPE_INT), "p1", isPointer);
  isPointer = false;
  Parameter p4(new CType(CTYPE_INT), "p1", isPointer);

  ASSERT_NE(p3, p4);
}

TEST(equality, ReturnValueSame)
{
  ReturnValue rv1;
  ReturnValue rv2;

  ASSERT_EQ(rv1, rv2);
}

TEST(equality, ReturnValuePointerSame)
{
  bool isPointer = true;
  ReturnValue rv1(new CType(CTYPE_INT), isPointer);
  ReturnValue rv2(new CType(CTYPE_INT), isPointer);

  ASSERT_EQ(rv1, rv2);
}

TEST(equality, ReturnValueDifferent)
{
  ReturnValue rv1 = VoidReturnValue();
  ReturnValue rv2 = TypedReturnValue(CTYPE_INT);

  ASSERT_NE(rv1, rv2);
}

TEST(equality, ReturnValuePointerDifferent)
{
  bool isPointer = true;
  ReturnValue rv1 = VoidReturnValue();
  rv1.setPointer(isPointer);
  ReturnValue rv2 = TypedReturnValue(CTYPE_INT, isPointer);

  ASSERT_NE(rv1, rv2);

  isPointer = true;
  ReturnValue rv3 = TypedReturnValue(CTYPE_INT, isPointer);
  isPointer = false;
  ReturnValue rv4 = TypedReturnValue(CTYPE_INT, isPointer);

  ASSERT_NE(rv3, rv4);
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

TEST(equality, StructFieldPointerSame)
{
  StructField f1(CTYPE_INT, "a");
  StructField f2(CTYPE_INT, "a");

  f1.setPointer(true);
  ASSERT_NE(f1, f2);
  f2.setPointer(true);
  ASSERT_EQ(f1, f2);

  StructField f3(new StructType("s", {new StructField(CTYPE_INT, "c"), new StructField(CTYPE_INT, "d")}), "e");
  StructField f4(new StructType("s", {new StructField(CTYPE_INT, "c"), new StructField(CTYPE_INT, "d")}), "e");

  ASSERT_EQ(f3, f4);
  (*f3.getType()->getContainedFields())[1].setPointer(true);
  ASSERT_NE(f3, f4);
  (*f4.getType()->getContainedFields())[1].setPointer(true);
  ASSERT_EQ(f3, f4);

  (*f3.getType()->getContainedFields())[1].setArray(true);
  ASSERT_NE(f3, f4);
  (*f4.getType()->getContainedFields())[1].setArray(true);
  ASSERT_EQ(f3, f4);

  (*f3.getType()->getContainedFields())[1].setArraySize(10);
  ASSERT_NE(f3, f4);
  (*f4.getType()->getContainedFields())[1].setArraySize(10);
  ASSERT_EQ(f3, f4);
}

TEST(equality, StructFieldDifferent)
{
  StructField f1(CTYPE_INT, "a");
  StructField f2(CTYPE_DOUBLE, "a");

  ASSERT_NE(f1, f2);

  StructField f3(new StructType("s", {new StructField(CTYPE_INT, "c"), new StructField(CTYPE_INT, "d")}), "e");
  StructField f4(new StructType("s", {new StructField(CTYPE_INT, "c"), new StructField(CTYPE_DOUBLE, "d")}), "e");

  ASSERT_NE(f3, f4);
}

TEST(equality, StructTypeSame)
{
  StructType s1("s", {});
  StructType s2("s", {});

  ASSERT_EQ(s1, s2);
  //Test from base class to make sure that the comparison overload is working
  TypeItf &sTitfS1 = s1;
  TypeItf &sTitfS2 = s2;
  ASSERT_EQ(sTitfS1, sTitfS2);

  StructType s3("s", {new StructField(CTYPE_CHAR, "f")});
  StructType s4("s", {new StructField(CTYPE_CHAR, "f")});

  ASSERT_EQ(s3, s4);
  //Test from base class to make sure that the comparison overload is working
  TypeItf &sTitfS3 = s3;
  TypeItf &sTitfS4 = s4;
  ASSERT_EQ(sTitfS3, sTitfS4);
}

TEST(equality, StructTypeDifferent)
{
  StructType s1("s", {});
  StructType s2("s", {new StructField(CTYPE_CHAR, "f")});

  ASSERT_NE(s1,s2);
  //Test from base class to make sure that the comparison overload is working
  TypeItf &sTitfS1 = s1;
  TypeItf &sTitfS2 = s2;
  ASSERT_NE(sTitfS1, sTitfS2);
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
