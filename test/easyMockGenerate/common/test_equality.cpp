#include <gtest/gtest.h>
#include <CType.h>
#include <Function.h>
#include <Parameter.h>
#include <ReturnValue.h>
#include <StructType.h>
#include <UnionType.h>
#include <ComposableField.h>
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
  Function f1("foo", VoidReturnValue(), Parameter::Vector({NamedParameter(CTYPE_INT, "foo")}));
  Function f2("foo", VoidReturnValue(), Parameter::Vector({NamedParameter(CTYPE_DOUBLE, "foo")}));

  ASSERT_NE(f1, f2);
}

TEST(equality, FunctionWithSameParamsButWithDifferentName)
{
  Function f1("foo", VoidReturnValue(), Parameter::Vector({NamedParameter(CTYPE_INT, "foo")}));
  Function f2("foo", VoidReturnValue(), Parameter::Vector({NamedParameter(CTYPE_INT, "bar")}));

  ASSERT_EQ(f1, f2);
}

TEST(equality, FunctionWithSameParamsButReturnValueIsDifferent)
{
  Function f1("foo", TypedReturnValue(CTYPE_INT), Parameter::Vector({NamedParameter(CTYPE_INT, "foo")}));
  Function f2("foo", TypedReturnValue(CTYPE_DOUBLE), Parameter::Vector({NamedParameter(CTYPE_INT, "bar")}));

  ASSERT_NE(f1, f2);
}

TEST(equality, FunctionSameParamsSwaped)
{
  Function f1("foo", VoidReturnValue(), Parameter::Vector({NamedParameter(CTYPE_INT, "aInt"), NamedParameter(CTYPE_DOUBLE, "aDouble")}));
  Function f2("foo", VoidReturnValue(), Parameter::Vector({NamedParameter(CTYPE_DOUBLE, "aDouble"), NamedParameter(CTYPE_INT, "aInt")}));

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
  ComposableField f1(CTYPE_INT, "a");
  ComposableField f2(CTYPE_INT, "a");

  ASSERT_EQ(f1, f2);

  bool isEmbeddedInOtherType = false;
  ComposableField f3(new StructType("s", ComposableField::Vector({new ComposableField(CTYPE_INT, "c"), new ComposableField(CTYPE_INT, "d")}), isEmbeddedInOtherType), "e");
  ComposableField f4(new StructType("s", ComposableField::Vector({new ComposableField(CTYPE_INT, "c"), new ComposableField(CTYPE_INT, "d")}), isEmbeddedInOtherType), "e");

  ASSERT_EQ(f3, f4);
}

TEST(equality, StructFieldPointerSame)
{
  ComposableField f1(CTYPE_INT, "a");
  ComposableField f2(CTYPE_INT, "a");

  f1.setPointer(true);
  ASSERT_NE(f1, f2);
  f2.setPointer(true);
  ASSERT_EQ(f1, f2);

  bool isEmbeddedInOtherType = false;
  ComposableField f3(new StructType("s", ComposableField::Vector({new ComposableField(CTYPE_INT, "c"), new ComposableField(CTYPE_INT, "d")}), isEmbeddedInOtherType), "e");
  ComposableField f4(new StructType("s", ComposableField::Vector({new ComposableField(CTYPE_INT, "c"), new ComposableField(CTYPE_INT, "d")}), isEmbeddedInOtherType), "e");

  ASSERT_EQ(f3, f4);
  f3.getType()->getContainedFields()[1].setPointer(true);
  ASSERT_NE(f3, f4);
  f4.getType()->getContainedFields()[1].setPointer(true);
  ASSERT_EQ(f3, f4);

  f3.getType()->getContainedFields()[1].setArray(true);
  ASSERT_NE(f3, f4);
  f4.getType()->getContainedFields()[1].setArray(true);
  ASSERT_EQ(f3, f4);

  f3.getType()->getContainedFields()[1].setArraySize(10);
  ASSERT_NE(f3, f4);
  f4.getType()->getContainedFields()[1].setArraySize(10);
  ASSERT_EQ(f3, f4);
}

TEST(equality, StructFieldDifferent)
{
  ComposableField f1(CTYPE_INT, "a");
  ComposableField f2(CTYPE_DOUBLE, "a");

  ASSERT_NE(f1, f2);

  bool isEmbeddedInOtherType = false;
  ComposableField f3(new StructType("s", ComposableField::Vector({new ComposableField(CTYPE_INT, "c"), new ComposableField(CTYPE_INT, "d")}), isEmbeddedInOtherType), "e");
  ComposableField f4(new StructType("s", ComposableField::Vector({new ComposableField(CTYPE_INT, "c"), new ComposableField(CTYPE_DOUBLE, "d")}), isEmbeddedInOtherType), "e");

  ASSERT_NE(f3, f4);
}

template <class T>
static void runComposableTypeSame(T &s1, T &s2)
{
  ASSERT_EQ(s1, s2);
  //Test from base class to make sure that the comparison overload is working
  TypeItf &sTitfS1 = s1;
  TypeItf &sTitfS2 = s2;
  ASSERT_EQ(sTitfS1, sTitfS2);

  bool isEmbeddedInOtherType = false;
  T s3("s", ComposableField::Vector({new ComposableField(CTYPE_CHAR, "f")}), isEmbeddedInOtherType);
  T s4("s", ComposableField::Vector({new ComposableField(CTYPE_CHAR, "f")}), isEmbeddedInOtherType);

  ASSERT_EQ(s3, s4);
  //Test from base class to make sure that the comparison overload is working
  TypeItf &sTitfS3 = s3;
  TypeItf &sTitfS4 = s4;
  ASSERT_EQ(sTitfS3, sTitfS4);
}

TEST(equality, StructTypeSame)
{
  bool isEmbeddedInOtherType = false;
  StructType s1("s", ComposableField::Vector({}), isEmbeddedInOtherType);
  StructType s2("s", ComposableField::Vector({}), isEmbeddedInOtherType);

  runComposableTypeSame(s1, s2);
}

TEST(equality, UnionTypeSame)
{
  bool isEmbeddedInOtherType = true;
  UnionType u1("s", ComposableField::Vector({}), isEmbeddedInOtherType);
  UnionType u2("s", ComposableField::Vector({}), isEmbeddedInOtherType);

  runComposableTypeSame(u1, u2);
}

template <class T>
static void runComposableTypeDifferent(T &s1, T &s2)
{
  ASSERT_NE(s1,s2);
  //Test from base class to make sure that the comparison overload is working
  TypeItf &sTitfS1 = s1;
  TypeItf &sTitfS2 = s2;
  ASSERT_NE(sTitfS1, sTitfS2);
}

TEST(equality, StructTypeDifferent)
{
  bool isEmbeddedInOtherType = false;
  StructType s1("s", ComposableField::Vector({}), isEmbeddedInOtherType);
  StructType s2("s", ComposableField::Vector({new ComposableField(CTYPE_CHAR, "f")}), isEmbeddedInOtherType);

  runComposableTypeDifferent(s1, s2);
}

TEST(equality, UnionTypeDifferent)
{
  bool isEmbeddedInOtherType = false;
  UnionType u1("s", ComposableField::Vector({}), isEmbeddedInOtherType);
  UnionType u2("s", ComposableField::Vector({new ComposableField(CTYPE_CHAR, "f")}), isEmbeddedInOtherType);

  runComposableTypeDifferent(u1, u2);
}

TEST(equality, StructTypedDefEqual)
{
  bool isEmbeddedInOtherType = false;

  StructType s1("s1", "typeS1", isEmbeddedInOtherType);
  StructType s2("s1", "typeS1", isEmbeddedInOtherType);

  runComposableTypeSame(s1, s2);
}

TEST(equality, UnionTypedDefEqual)
{
  bool isEmbeddedInOtherType = false;

  UnionType u1("s1", "typeS1", isEmbeddedInOtherType);
  UnionType u2("s1", "typeS1", isEmbeddedInOtherType);

  runComposableTypeSame(u1, u2);
}

TEST(equality, StructTypedDefDifferent)
{
  bool isEmbeddedInOtherType = false;

  StructType s1("s1", "", isEmbeddedInOtherType);
  StructType s2("", "s1", isEmbeddedInOtherType);

  runComposableTypeDifferent(s1, s2);
}

TEST(equality, UnionTypedDefDifferent)
{
  bool isEmbeddedInOtherType = false;

  UnionType u1("s1", "", isEmbeddedInOtherType);
  UnionType u2("", "s1", isEmbeddedInOtherType);

  runComposableTypeDifferent(u1, u2);
}

TEST(equality, StructEmbeddedInOtherTypeDifferent)
{
  bool isEmbeddedInOtherType = false;

  StructType s1("s1", "typeS1", isEmbeddedInOtherType);
  StructType s2("s1", "typeS1", !isEmbeddedInOtherType);

  runComposableTypeDifferent(s1, s2);
}

TEST(equality, UnionEmbeddedInOtherTypeDifferent)
{
  bool isEmbeddedInOtherType = false;

  UnionType u1("s1", "typeS1", isEmbeddedInOtherType);
  UnionType u2("s1", "typeS1", !isEmbeddedInOtherType);

  runComposableTypeDifferent(u1, u2);
}

/*
 * Even though struct and union cannot have the same name (or tag).
 * We want to make sure that if the parser would return the wrong
 * object type but with the correct name that would trigger issue in other UTs.
 */
TEST(equality, StructVSUnion)
{
  bool isEmbeddedInOtherType = false;
  //Struct and union cannot have the same name (tag) but do it anyway.
  StructType s1("sameName", isEmbeddedInOtherType);
  UnionType u1("sameName", isEmbeddedInOtherType);

  ASSERT_NE(s1, u1);

  TypeItf &tS1 = s1;
  TypeItf &tU1 = u1;

  ASSERT_NE(tS1, tU1);
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
