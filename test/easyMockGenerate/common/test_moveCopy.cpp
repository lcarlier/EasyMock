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

TEST(moveCopy, ParameterPointer)
{
  bool isPointer = true;
  Parameter p1(new CType(CTYPE_VOID), "v", isPointer);
  Parameter p2(p1);
  ASSERT_EQ(p1, p2);

  Parameter p3(new CType(CTYPE_CHAR), "c", isPointer);
  ASSERT_NE(p3,p1);
  p3 = p1;
  ASSERT_EQ(p3,p1);

  Parameter p4 = std::move(p3);
  ASSERT_EQ(p4, p1);

  Parameter p6(new CType(CTYPE_CHAR), "c", isPointer);
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

TEST(moveCopy, ReturnValuePointer)
{
  bool isPointer = true;
  ReturnValue rv1 = VoidReturnValue(isPointer);
  ReturnValue rv2(rv1);
  ASSERT_EQ(rv1, rv2);

  ReturnValue rv3 = StructReturnValue(new StructType("s1", {new StructField(CTYPE_INT, "a")}), isPointer);
  ASSERT_NE(rv3,rv1);
  rv3 = rv1;
  ASSERT_EQ(rv3,rv1);

  ReturnValue rv4 = std::move(rv3);
  ASSERT_EQ(rv4, rv1);

  ReturnValue rv6 = StructReturnValue(new StructType("s1", {new StructField(CTYPE_INT, "a")}), isPointer);
  ASSERT_NE(rv6, rv2);
  rv6 = std::move(rv2);
  ASSERT_EQ(rv6, rv1);
}

static void testMoveStructField(StructField &f1)
{
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

TEST(moveCopy, StructField)
{
  StructField f1(CTYPE_INT, "a");

  testMoveStructField(f1);
}

TEST(moveCopy, StructFieldPtr)
{
  StructField f1(CTYPE_INT, "a");
  f1.setPointer(true);

  testMoveStructField(f1);
}

TEST(moveCopy, StructFieldBoundedArray)
{
  StructField f1(new CType(CTYPE_INT), "boundedArray", {.isPointer = false, .isArray = true, .arraySize = 10, .isRecursiveTypeField = false});

  testMoveStructField(f1);
}

TEST(moveCopy, StructFieldUnBoundedArray)
{
  StructField f1(new CType(CTYPE_INT), "unBoundedArray", {.isPointer = false, .isArray = true, .arraySize = 0, .isRecursiveTypeField = false});

  testMoveStructField(f1);
}

static void testStructType(StructType &st1)
{
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

TEST(moveCopy, StructType)
{
  StructType st1("s", {new StructField(CTYPE_CHAR, "f")});

  testStructType(st1);
}

TEST(moveCopy, StructTypeRecursive)
{
  bool isRecursiveType = true;
  StructType st1("recurs1");
  StructField::attributes attrib = {.isPointer = false, .isArray = false, .arraySize = 0, .isRecursiveTypeField = isRecursiveType};
  st1.addStructField(new StructField(&st1, "rfield", attrib));
  StructType st2(st1);
  ASSERT_EQ(st1, st2);
  const StructField::Vector& st2ContaineField = *st2.getContainedFields();
  ASSERT_EQ(&st2, st2ContaineField[0].getType());

  StructType st3("s", {new StructField(CTYPE_INT, "i")});
  ASSERT_NE(st3,st1);
  st3 = st1;
  ASSERT_EQ(st3,st1);
  const StructField::Vector& st3ContaineField = *st3.getContainedFields();
  ASSERT_EQ(&st3, st3ContaineField[0].getType());

  StructType st4 = std::move(st3);
  ASSERT_EQ(st4, st1);
  const StructField::Vector& st4ContaineField = *st4.getContainedFields();
  ASSERT_EQ(&st4, st4ContaineField[0].getType());

  StructType st6("s", {new StructField(CTYPE_INT, "i")});
  ASSERT_NE(st6, st2);
  st6 = std::move(st2);
  ASSERT_EQ(st6, st1);
  const StructField::Vector& st6ContaineField = *st6.getContainedFields();
  ASSERT_EQ(&st6, st6ContaineField[0].getType());
}

TEST(moveCopy, StructTypeSubFieldRecursive)
{
  bool isRecursiveType = true;
  StructType st1("recurs1");
  StructType* subSt = new StructType("subSt");
  subSt->addStructField(new StructField(&st1, "rfield", {.isPointer = false, .isArray = false, .arraySize = 0, .isRecursiveTypeField = isRecursiveType}));
  st1.addStructField(new StructField(subSt, "subField"));
  subSt = nullptr; //Dereference, pointer is not usable here anymore
  StructType st2(st1);
  ASSERT_EQ(st1, st2);
  const StructField::Vector& st2ContaineField = *st2.getContainedFields();
  const StructField::Vector& st2SubStContainerField = *st2ContaineField[0].getType()->getContainedFields();
  ASSERT_EQ(&st2, st2SubStContainerField[0].getType());

  StructType st3("s", {new StructField(CTYPE_INT, "i")});
  ASSERT_NE(st3,st1);
  st3 = st1;
  ASSERT_EQ(st3,st1);
  const StructField::Vector& st3ContaineField = *st3.getContainedFields();
  const StructField::Vector& st3SubStContainerField = *st3ContaineField[0].getType()->getContainedFields();
  ASSERT_EQ(&st3, st3SubStContainerField[0].getType());

  StructType st4 = std::move(st3);
  ASSERT_EQ(st4, st1);
  const StructField::Vector& st4ContaineField = *st4.getContainedFields();
  const StructField::Vector& st4SubStContainerField = *st4ContaineField[0].getType()->getContainedFields();
  ASSERT_EQ(&st4, st4SubStContainerField[0].getType());

  StructType st6("s", {new StructField(CTYPE_INT, "i")});
  ASSERT_NE(st6, st2);
  st6 = std::move(st2);
  ASSERT_EQ(st6, st1);
  const StructField::Vector& st6ContaineField = *st6.getContainedFields();
  const StructField::Vector& st6SubStContainerField = *st6ContaineField[0].getType()->getContainedFields();
  ASSERT_EQ(&st6, st6SubStContainerField[0].getType());
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
