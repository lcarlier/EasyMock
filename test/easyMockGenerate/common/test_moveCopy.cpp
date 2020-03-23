#include <gtest/gtest.h>
#include <CType.h>
#include <Function.h>
#include <Parameter.h>
#include <ComposableField.h>
#include <StructType.h>
#include <UnionType.h>
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

static void testMoveCopyParameter(Parameter &p1)
{
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

TEST(moveCopy, Parameter)
{
  Parameter p1(new CType(CTYPE_VOID), "v");

  testMoveCopyParameter(p1);
}

TEST(moveCopy, ParameterPointer)
{
  bool isPointer = true;
  Parameter p1(new CType(CTYPE_VOID), "v", isPointer);

  testMoveCopyParameter(p1);
}

TEST(moveCopy, ParameterWithStructSubRecursive)
{
  bool isEmbeddedInOtherType = false;
  StructType *st1 = new StructType("st1", isEmbeddedInOtherType);
  StructType *st2 = new StructType("st2", isEmbeddedInOtherType);
  st1->addStructField(new ComposableField(st2, "st1SubSt2"));
  //st1 is recursive in st2 because it is access via the parameter "st1Val" which is type st2 and has a st1 as field member
  st2->addStructField(new ComposableField(st1, "st2SubSt1", {.isPointer = true, .isArray = false, .arraySize = 0, .isRecursiveTypeField = true}));
  st2->addStructField(new ComposableField(st2, "st2SubSt2", {.isPointer = true, .isArray = false, .arraySize = 0, .isRecursiveTypeField = true}));
  Parameter p1(st1, "st1Val");

  testMoveCopyParameter(p1);
}

TEST(moveCopy, ReturnValue)
{
  bool isEmbeddedInOtherType = false;
  ReturnValue rv1 = VoidReturnValue();
  ReturnValue rv2(rv1);
  ASSERT_EQ(rv1, rv2);

  ReturnValue rv3 = StructReturnValue(new StructType("s1", ComposableField::Vector({new ComposableField(CTYPE_INT, "a")}), isEmbeddedInOtherType));
  ASSERT_NE(rv3,rv1);
  rv3 = rv1;
  ASSERT_EQ(rv3,rv1);

  ReturnValue rv4 = std::move(rv3);
  ASSERT_EQ(rv4, rv1);

  ReturnValue rv6 = StructReturnValue(new StructType("s1", ComposableField::Vector({new ComposableField(CTYPE_INT, "a")}), isEmbeddedInOtherType));
  ASSERT_NE(rv6, rv2);
  rv6 = std::move(rv2);
  ASSERT_EQ(rv6, rv1);
}

TEST(moveCopy, ReturnValuePointer)
{
  bool isPointer = true;
  bool isEmbeddedInOtherType = false;
  ReturnValue rv1 = VoidReturnValue(isPointer);
  ReturnValue rv2(rv1);
  ASSERT_EQ(rv1, rv2);

  ReturnValue rv3 = StructReturnValue(new StructType("s1", ComposableField::Vector({new ComposableField(CTYPE_INT, "a")}), isEmbeddedInOtherType), isPointer);
  ASSERT_NE(rv3,rv1);
  rv3 = rv1;
  ASSERT_EQ(rv3,rv1);

  ReturnValue rv4 = std::move(rv3);
  ASSERT_EQ(rv4, rv1);

  ReturnValue rv6 = StructReturnValue(new StructType("s1", ComposableField::Vector({new ComposableField(CTYPE_INT, "a")}), isEmbeddedInOtherType), isPointer);
  ASSERT_NE(rv6, rv2);
  rv6 = std::move(rv2);
  ASSERT_EQ(rv6, rv1);
}

static void testMoveStructField(ComposableField &f1)
{
  bool isEmbeddedInOtherType = false;
  ComposableField f2(f1);
  ASSERT_EQ(f1, f2);

  ComposableField f3(new StructType("s", ComposableField::Vector({new ComposableField(CTYPE_INT, "c"), new ComposableField(CTYPE_INT, "d")}), isEmbeddedInOtherType), "e");
  ASSERT_NE(f3,f1);
  f3 = f1;
  ASSERT_EQ(f3,f1);

  ComposableField f4 = std::move(f3);
  ASSERT_EQ(f4, f1);

  ComposableField f6(new StructType("s", ComposableField::Vector({new ComposableField(CTYPE_INT, "c"), new ComposableField(CTYPE_INT, "d")}), isEmbeddedInOtherType), "e");
  ASSERT_NE(f6, f2);
  f6 = std::move(f2);
  ASSERT_EQ(f6, f1);
}

TEST(moveCopy, ComposableField)
{
  ComposableField f1(CTYPE_INT, "a");

  testMoveStructField(f1);
}

TEST(moveCopy, StructFieldPtr)
{
  ComposableField f1(CTYPE_INT, "a");
  f1.setPointer(true);

  testMoveStructField(f1);
}

TEST(moveCopy, StructFieldBoundedArray)
{
  ComposableField f1(new CType(CTYPE_INT), "boundedArray", {.isPointer = false, .isArray = true, .arraySize = 10, .isRecursiveTypeField = false});

  testMoveStructField(f1);
}

TEST(moveCopy, StructFieldUnBoundedArray)
{
  ComposableField f1(new CType(CTYPE_INT), "unBoundedArray", {.isPointer = false, .isArray = true, .arraySize = 0, .isRecursiveTypeField = false});

  testMoveStructField(f1);
}

template <class T>
static void testComposableType(T &st1)
{
  bool isEmbeddedInOtherType = false;
  T st2(st1);
  ASSERT_EQ(st1, st2);

  T st3("s", ComposableField::Vector({new ComposableField(CTYPE_INT, "i")}), isEmbeddedInOtherType);
  ASSERT_NE(st3,st1);
  st3 = st1;
  ASSERT_EQ(st3,st1);

  T st4 = std::move(st3);
  ASSERT_EQ(st4, st1);

  T st6("s", ComposableField::Vector({new ComposableField(CTYPE_INT, "i")}), isEmbeddedInOtherType);
  ASSERT_NE(st6, st2);
  st6 = std::move(st2);
  ASSERT_EQ(st6, st1);
}

TEST(moveCopy, StructType)
{
  bool isEmbeddedInOtherType = false;
  StructType st1("s", ComposableField::Vector({new ComposableField(CTYPE_CHAR, "f")}), isEmbeddedInOtherType);

  testComposableType(st1);
}

TEST(moveCopy, UnionType)
{
  bool isEmbeddedInOtherType = false;
  UnionType st1("s", ComposableField::Vector({new ComposableField(CTYPE_CHAR, "f")}), isEmbeddedInOtherType);

  testComposableType(st1);
}

TEST(moveCopy, StructTypeRecursive)
{
  bool isRecursiveType = true;
  bool isEmbeddedInOtherType = false;
  StructType st1("recurs1", isEmbeddedInOtherType);
  ComposableField::attributes attrib = {.isPointer = true, .isArray = false, .arraySize = 0, .isRecursiveTypeField = isRecursiveType};
  st1.addStructField(new ComposableField(&st1, "rfield", attrib));
  st1.addStructField(new ComposableField(new CType(CTYPE_INT), "intField"));
  StructType st2(st1);
  ASSERT_EQ(st1, st2);
  const ComposableField::Vector& st2ContaineField = *st2.getContainedFields();
  ASSERT_EQ(&st2, st2ContaineField[0].getType());

  StructType st3("s", ComposableField::Vector({new ComposableField(CTYPE_INT, "i")}), isEmbeddedInOtherType);
  ASSERT_NE(st3,st1);
  st3 = st1;
  ASSERT_EQ(st3,st1);
  const ComposableField::Vector& st3ContaineField = *st3.getContainedFields();
  ASSERT_EQ(&st3, st3ContaineField[0].getType());

  StructType st4 = std::move(st3);
  ASSERT_EQ(st4, st1);
  const ComposableField::Vector& st4ContaineField = *st4.getContainedFields();
  ASSERT_EQ(&st4, st4ContaineField[0].getType());

  StructType st6("s", ComposableField::Vector({new ComposableField(CTYPE_INT, "i")}), isEmbeddedInOtherType);
  ASSERT_NE(st6, st2);
  st6 = std::move(st2);
  ASSERT_EQ(st6, st1);
  const ComposableField::Vector& st6ContaineField = *st6.getContainedFields();
  ASSERT_EQ(&st6, st6ContaineField[0].getType());
}

TEST(moveCopy, StructTypeSubFieldRecursive)
{
  bool isRecursiveType = true;
  bool isEmbeddedInOtherType = true;
  StructType st1("recurs1", isEmbeddedInOtherType);
  StructType* subSt = new StructType("subSt", isEmbeddedInOtherType);
  subSt->addStructField(new ComposableField(&st1, "rfield", {.isPointer = true, .isArray = false, .arraySize = 0, .isRecursiveTypeField = isRecursiveType}));
  st1.addStructField(new ComposableField(subSt, "subField"));
  subSt = nullptr; //Dereference, pointer is not usable here anymore
  StructType st2(st1);
  ASSERT_EQ(st1, st2);
  const ComposableField::Vector& st2ContaineField = *st2.getContainedFields();
  const ComposableField::Vector& st2SubStContainerField = *st2ContaineField[0].getType()->getContainedFields();
  ASSERT_EQ(&st2, st2SubStContainerField[0].getType());

  StructType st3("s", ComposableField::Vector({new ComposableField(CTYPE_INT, "i")}), isEmbeddedInOtherType);
  ASSERT_NE(st3,st1);
  st3 = st1;
  ASSERT_EQ(st3,st1);
  const ComposableField::Vector& st3ContaineField = *st3.getContainedFields();
  const ComposableField::Vector& st3SubStContainerField = *st3ContaineField[0].getType()->getContainedFields();
  ASSERT_EQ(&st3, st3SubStContainerField[0].getType());

  StructType st4 = std::move(st3);
  ASSERT_EQ(st4, st1);
  const ComposableField::Vector& st4ContaineField = *st4.getContainedFields();
  const ComposableField::Vector& st4SubStContainerField = *st4ContaineField[0].getType()->getContainedFields();
  ASSERT_EQ(&st4, st4SubStContainerField[0].getType());

  StructType st6("s", ComposableField::Vector({new ComposableField(CTYPE_INT, "i")}), isEmbeddedInOtherType);
  ASSERT_NE(st6, st2);
  st6 = std::move(st2);
  ASSERT_EQ(st6, st1);
  const ComposableField::Vector& st6ContaineField = *st6.getContainedFields();
  const ComposableField::Vector& st6SubStContainerField = *st6ContaineField[0].getType()->getContainedFields();
  ASSERT_EQ(&st6, st6SubStContainerField[0].getType());
}

/*
 * struct s2; //Or union
 *
 * struct s1 { //Or union
 *    struct s1 *s1SubS1;
 *    struct s2 *s1SubS2;
 * }
 *
 * struct s2 { //Or union
 *    struct s1 s2SubS1;
 * }
 *
 * test moveCopy(s2);
 */

template <class T>
static void runTypeTwoRecursiveTypes(T &s2)
{
  bool isEmbeddedInOtherType = false;
  T *s1 = new T("s1", isEmbeddedInOtherType);
  s1->addStructField(new ComposableField(s1, "s1SubS1", {.isPointer = true, .isArray = false, .arraySize = 0, .isRecursiveTypeField = true}));
  s1->addStructField(new ComposableField(&s2, "s1SubS2", {.isPointer = true, .isArray = false, .arraySize = 0, .isRecursiveTypeField = true}));

  s2.addStructField(new ComposableField(s1, "s2SubS1"));

  testComposableType(s2);
}

TEST(moveCopy, StructTypeTwoRecursiveTypes)
{
  bool isEmbeddedInOtherType = false;
  StructType s2("s2", isEmbeddedInOtherType);
  runTypeTwoRecursiveTypes(s2);
}

TEST(moveCopy, UnionTypeTwoRecursiveTypes)
{
  bool isEmbeddedInOtherType = false;
  UnionType u2("u2", isEmbeddedInOtherType);
  runTypeTwoRecursiveTypes(u2);
}

TEST(moveCopy, StructTypedAnonymousTypedDef)
{
  bool isEmbeddedInOtherType = false;

  StructType s1("", "Anonymous", isEmbeddedInOtherType);

  testComposableType(s1);
}

TEST(moveCopy, UnionTypedAnonymousTypedDef)
{
  bool isEmbeddedInOtherType = false;

  UnionType u1("", "Anonymous", isEmbeddedInOtherType);

  testComposableType(u1);
}

TEST(moveCopy, StructTypedTypedDef)
{
  bool isEmbeddedInOtherType = false;

  StructType s1("foo", "NotAnonymous", isEmbeddedInOtherType);

  testComposableType(s1);
}

TEST(moveCopy, UnionTypedTypedDef)
{
  bool isEmbeddedInOtherType = false;

  UnionType u1("foo", "NotAnonymous", isEmbeddedInOtherType);

  testComposableType(u1);
}

TEST(moveCopy, StructEmbeddedInOtherType)
{
  bool isEmbeddedInOtherType = true;

  StructType s1("foo", "NotAnonymous", isEmbeddedInOtherType);

  testComposableType(s1);
}

TEST(moveCopy, UnionEmbeddedInOtherType)
{
  bool isEmbeddedInOtherType = true;

  UnionType u1("foo", "NotAnonymous", isEmbeddedInOtherType);

  testComposableType(u1);
}

TEST(moveCopy, AutoCleanVectorPtr)
{
  AutoCleanVectorPtr<ComposableField> v1({new ComposableField(CTYPE_INT, "i"), new ComposableField(CTYPE_DOUBLE, "d")});
  AutoCleanVectorPtr<ComposableField> v2(v1);
  ASSERT_EQ(v1, v2);

  AutoCleanVectorPtr<ComposableField> v3({new ComposableField(CTYPE_DOUBLE, "d"), new ComposableField(CTYPE_INT, "i")});
  ASSERT_NE(v3,v1);
  v3 = v1;
  ASSERT_EQ(v3,v1);

  AutoCleanVectorPtr<ComposableField> v4 = std::move(v3);
  ASSERT_EQ(v4, v1);

  AutoCleanVectorPtr<ComposableField> v6({new ComposableField(CTYPE_DOUBLE, "d"), new ComposableField(CTYPE_INT, "i")});
  ASSERT_NE(v6, v2);
  v6 = std::move(v2);
  ASSERT_EQ(v6, v1);
}
