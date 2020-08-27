#include <gtest/gtest.h>
#include <CType.h>
#include <Function.h>
#include <Parameter.h>
#include <ReturnValue.h>
#include <StructType.h>
#include <UnionType.h>
#include <ComposableField.h>
#include <AutoCleanVectorPtr.h>
#include <Pointer.h>
#include <FunctionType.h>
#include <FunctionDeclaration.h>
#include <Enum.h>

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

TEST(equality, PointerToConstSame)
{
  bool isConst = true;
  Pointer p1(new CType(CTYPE_INT, isConst));
  Pointer p2(new CType(CTYPE_INT, !isConst));

  ASSERT_NE(p1, p2);
  p2.getPointedType()->setConst(isConst);
  ASSERT_EQ(p1, p2);
}

TEST(equality, ConstPointerSame)
{
  bool isConst = true;
  Pointer p1(new CType(CTYPE_INT), isConst);
  Pointer p2(new CType(CTYPE_INT), !isConst);

  ASSERT_NE(p1, p2);
  p2.setConst(isConst);
  ASSERT_EQ(p1, p2);
}

template<typename T>
void functionWithDifferentParams()
{
  T f1("foo", VoidReturnValue(), Parameter::Vector({NamedParameter(CTYPE_INT, "foo")}));
  T f2("foo", VoidReturnValue(), Parameter::Vector({NamedParameter(CTYPE_DOUBLE, "foo")}));

  ASSERT_NE(f1, f2);
}

TEST(equality, FunctionWithDifferentParams)
{
  functionWithDifferentParams<Function>();
}

TEST(equality, FunctionTypeWithDifferentParams)
{
  functionWithDifferentParams<FunctionType>();
}

TEST(equality, FunctionDeclarationWithDifferentParams)
{
  functionWithDifferentParams<FunctionDeclaration>();
}

template<typename T>
void functionWithSameParamsButWithDifferentName()
{
  T f1("foo", VoidReturnValue(), Parameter::Vector({NamedParameter(CTYPE_INT, "foo")}));
  T f2("foo", VoidReturnValue(), Parameter::Vector({NamedParameter(CTYPE_INT, "bar")}));

  ASSERT_EQ(f1, f2);
}

TEST(equality, FunctionWithSameParamsButWithDifferentName)
{
  functionWithSameParamsButWithDifferentName<Function>();
}

TEST(equality, FunctionTypeWithSameParamsButWithDifferentName)
{
  functionWithSameParamsButWithDifferentName<FunctionType>();
}

TEST(equality, FunctionDeclarationWithSameParamsButWithDifferentName)
{
  functionWithSameParamsButWithDifferentName<FunctionDeclaration>();
}

template<typename T>
void functionWithSameParamsButReturnValueIsDifferent()
{
  T f1("foo", TypedReturnValue(CTYPE_INT), Parameter::Vector({NamedParameter(CTYPE_INT, "foo")}));
  T f2("foo", TypedReturnValue(CTYPE_DOUBLE), Parameter::Vector({NamedParameter(CTYPE_INT, "bar")}));

  ASSERT_NE(f1, f2);
}

TEST(equality, FunctionWithSameParamsButReturnValueIsDifferent)
{
  functionWithSameParamsButReturnValueIsDifferent<Function>();
}

TEST(equality, FunctionTypeWithSameParamsButReturnValueIsDifferent)
{
  functionWithSameParamsButReturnValueIsDifferent<FunctionType>();
}

TEST(equality, FunctionDeclarationWithSameParamsButReturnValueIsDifferent)
{
  functionWithSameParamsButReturnValueIsDifferent<FunctionDeclaration>();
}

template<typename T>
void functionSameParamsSwaped()
{
  T f1("foo", VoidReturnValue(), Parameter::Vector({NamedParameter(CTYPE_INT, "aInt"), NamedParameter(CTYPE_DOUBLE, "aDouble")}));
  T f2("foo", VoidReturnValue(), Parameter::Vector({NamedParameter(CTYPE_DOUBLE, "aDouble"), NamedParameter(CTYPE_INT, "aInt")}));

  ASSERT_NE(f1, f2);
}

TEST(equality, FunctionSameParamsSwaped)
{
  functionSameParamsSwaped<Function>();
}

TEST(equality, FunctionTypeSameParamsSwaped)
{
  functionSameParamsSwaped<FunctionType>();
}

TEST(equality, FunctionDeclarationSameParamsSwaped)
{
  functionSameParamsSwaped<FunctionDeclaration>();
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
  Parameter p1(new Pointer(new CType(CTYPE_VOID)), "v1");
  Parameter p2(new Pointer(new CType(CTYPE_VOID)), "v2");

  //Even though name is different parameters are the same
  ASSERT_EQ(p1, p2);
}

TEST(equality, ParameterConstSameParam)
{
  bool isConst = true;
  Parameter p1(new CType(CTYPE_VOID, isConst), "v1");
  Parameter p2(new CType(CTYPE_VOID, isConst), "v2");

  //Even though name is different parameters are the same
  ASSERT_EQ(p1, p2);
}

TEST(equality, ParameterDeclareStringSameParam)
{
  Parameter p1(new CType(CTYPE_VOID), "v1");
  Parameter p2(new CType(CTYPE_VOID), "v2");
  p1.setDeclareString(p1.getType()->getFullDeclarationName());
  p2.setDeclareString(p2.getType()->getFullDeclarationName());

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
  Parameter p1(new Pointer(new CType(CTYPE_INT)), "p1");
  Parameter p2(new Pointer(new CType(CTYPE_VOID)), "p1");

  ASSERT_NE(p1, p2);

  Parameter p3(new Pointer(new CType(CTYPE_INT)), "p1");
  Parameter p4(new CType(CTYPE_INT), "p1");

  ASSERT_NE(p3, p4);
}

TEST(equality, ParameterConstDifferentParam)
{
  bool isConst = true;
  Parameter p1(new CType(CTYPE_INT, isConst), "p1");
  Parameter p2(new CType(CTYPE_VOID, isConst), "p1");

  ASSERT_NE(p1, p2);

  Parameter p3(new CType(CTYPE_INT, isConst), "p1");
  Parameter p4(new CType(CTYPE_INT, !isConst), "p1");

  ASSERT_NE(p3, p4);
}

TEST(equality, ParameterDeclareStringDifferentParam)
{
  Parameter p1(new CType(CTYPE_INT), "p1");
  Parameter p2(new CType(CTYPE_INT), "p1");
  p1.setDeclareString("fromDefine");

  ASSERT_NE(p1, p2);

  Parameter p3(new CType(CTYPE_INT), "p1");
  Parameter p4(new CType(CTYPE_INT), "p1");
  p3.setDeclareString(p3.getType()->getFullDeclarationName());
  p4.setDeclareString("FromDefine");

  ASSERT_NE(p3, p4);
}

TEST(equality, ReturnValueSame)
{
  ReturnValue rv1(new CType(CTYPE_INT));
  ReturnValue rv2(new CType(CTYPE_INT));

  ASSERT_EQ(rv1, rv2);
}

TEST(equality, ReturnValuePointerSame)
{
  ReturnValue rv1(new Pointer(new CType(CTYPE_INT)));
  ReturnValue rv2(new Pointer(new CType(CTYPE_INT)));

  ASSERT_EQ(rv1, rv2);
}

TEST(equality, ReturnValueConstSame)
{
  bool isConst = true;
  ReturnValue rv1(new CType(CTYPE_INT, isConst));
  ReturnValue rv2(new CType(CTYPE_INT, isConst));

  ASSERT_EQ(rv1, rv2);
}

TEST(equality, ReturnValueDeclareStringSame)
{
  ReturnValue rv1(new CType(CTYPE_INT));
  ReturnValue rv2(new CType(CTYPE_INT));
  rv1.setDeclareString(rv1.getType()->getFullDeclarationName());
  rv2.setDeclareString(rv2.getType()->getFullDeclarationName());

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
  ReturnValue rv1 = VoidReturnValue(isPointer);
  ReturnValue rv2 = TypedReturnValue(CTYPE_INT, isPointer);

  ASSERT_NE(rv1, rv2);

  isPointer = true;
  ReturnValue rv3 = TypedReturnValue(CTYPE_INT, isPointer);
  isPointer = false;
  ReturnValue rv4 = TypedReturnValue(CTYPE_INT, isPointer);

  ASSERT_NE(rv3, rv4);
}

TEST(equality, ReturnValueConstDifferent)
{
  bool isConst = true;

  ReturnValue rv1 = VoidReturnValue();
  ReturnValue rv2 = ReturnValue(new CType(CTYPE_INT, isConst));

  ASSERT_NE(rv1, rv2);

  ReturnValue rv3 = ReturnValue(new CType(CTYPE_INT, isConst));
  ReturnValue rv4 = ReturnValue(new CType(CTYPE_INT, !isConst));

  ASSERT_NE(rv3, rv4);
}

TEST(equality, ReturnValueDeclareStringDifferent)
{
  ReturnValue rv1(new CType(CTYPE_INT));
  ReturnValue rv2(new CType(CTYPE_INT));
  rv1.setDeclareString("FromDefine");

  ASSERT_NE(rv1, rv2);

  ReturnValue rv3(new CType(CTYPE_INT));
  ReturnValue rv4(new CType(CTYPE_INT));
  rv3.setDeclareString(rv3.getType()->getFullDeclarationName());
  rv4.setDeclareString("FromDefine");

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

  f1.getType()->setPointer(true);
  ASSERT_NE(f1, f2);
  f2.getType()->setPointer(true);
  ASSERT_EQ(f1, f2);

  bool isEmbeddedInOtherType = false;
  ComposableField f3(new StructType("s", ComposableField::Vector({new ComposableField(CTYPE_INT, "c"), new ComposableField(CTYPE_INT, "d")}), isEmbeddedInOtherType), "e");
  ComposableField f4(new StructType("s", ComposableField::Vector({new ComposableField(CTYPE_INT, "c"), new ComposableField(CTYPE_INT, "d")}), isEmbeddedInOtherType), "e");

  ASSERT_EQ(f3, f4);
  f3.getType()->getContainedFields()[1].getType()->setPointer(true);
  ASSERT_NE(f3, f4);
  f4.getType()->getContainedFields()[1].getType()->setPointer(true);
  ASSERT_EQ(f3, f4);

  f3.getType()->getContainedFields()[1].setArraySize(10);
  ASSERT_NE(f3, f4);
  f4.getType()->getContainedFields()[1].setArraySize(10);
  ASSERT_EQ(f3, f4);
}

TEST(equality, StructFieldConstSame)
{
  bool isConst = true;
  ComposableField f1(new CType(CTYPE_INT, isConst), "a");
  ComposableField f2(new CType(CTYPE_INT, isConst), "a");

  ASSERT_EQ(f1, f2);
}

TEST(equality, StructFieldDeclStringSame)
{
  ComposableField f1(new CType(CTYPE_INT), "a");
  ComposableField f2(new CType(CTYPE_INT), "a");
  f1.setDeclareString(f1.getType()->getFullDeclarationName());
  f2.setDeclareString(f2.getType()->getFullDeclarationName());

  ASSERT_EQ(f1, f2);
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

TEST(equality, StructFieldConstDifferent)
{
  bool isConst = true;
  ComposableField f1(new CType(CTYPE_INT, !isConst), "a");
  ComposableField f2(new CType(CTYPE_INT, isConst), "a");

  ASSERT_NE(f1, f2);
}

TEST(equality, StructFieldDeclStringDifferent)
{
  ComposableField f1(new CType(CTYPE_INT), "a");
  ComposableField f2(new CType(CTYPE_INT), "a");
  f1.setDeclareString(f1.getType()->getFullDeclarationName());
  f2.setDeclareString("FromMacro");

  ASSERT_NE(f1, f2);
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

TEST(equality, Enum)
{
  Enum e1("e1", "");
  Enum e2("e1", "");
  Enum e3("e2", "");

  ASSERT_EQ(e1,e2);
  ASSERT_NE(e1,e3);
  ASSERT_NE(e2,e3);

  TypeItf &tiC1 = e1;
  TypeItf &tiC2 = e2;
  TypeItf &tiC3 = e3;
  ASSERT_EQ(tiC1,tiC2);
  ASSERT_NE(tiC1,tiC3);
  ASSERT_NE(tiC2,tiC3);
}
