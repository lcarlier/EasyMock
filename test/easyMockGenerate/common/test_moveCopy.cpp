#include <gtest/gtest.h>
#include <EasyMock_CType.h>
#include <Function.h>
#include <Parameter.h>
#include <ComposableField.h>
#include <StructType.h>
#include <UnionType.h>
#include <AutoCleanVectorPtr.h>
#include <Pointer.h>
#include <FunctionDeclaration.h>
#include <FunctionType.h>
#include <Enum.h>
#include <IncompleteType.h>
#include <ComposableBitfield.h>
#include <ConstQualifiedType.h>
#include <TypedefType.h>

#include "common.h"

#include <PrintObjects.h>

namespace
{
template<typename ...>
struct TestFunctionWrapper;


template<typename T, typename ... Param>
struct TestFunctionWrapper<T, std::tuple<Param ...>>
{
  void test(Param &&... p1, Param &&... p2)
  {
    T f1(std::forward<Param>(p1)...);
    T f2(f1);
    ASSERT_EQ(f1, f2);

    T f3(std::forward<Param>(p2)...);
    ASSERT_NE(f3,f1);
    f3 = f1;
    ASSERT_EQ(f3,f1);

    T f4 = std::move(f3);
    ASSERT_EQ(f4, f1);

    T f6(std::forward<Param>(p2)...);
    ASSERT_NE(f6, f2);
    f6 = std::move(f2);
    ASSERT_EQ(f6, f1);
  }
};

#define DECLARE_FUNCTION_TEST_FUNCTION(funName) \
template<typename T, typename ... Param> \
void funName() \
{ \
  TestFunctionWrapper<T, Param...> testStruct{}; \
  if constexpr(std::is_base_of<FunctionType, T>::value) \
  { \
    testStruct.test(f1Param, \
                    f2Param); \
  } \
  else \
  { \
    testStruct.test("foo", f1Param, \
                    "foo", f2Param); \
  } \
}
}

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

static void testMovePointer(Pointer &p1)
{
  Pointer p2(p1);
  ASSERT_EQ(p1, p2);

  Pointer p3(new CType(CTYPE_DOUBLE));
  ASSERT_NE(p3, p1);
  p3 = p1;
  ASSERT_EQ(p3, p1);

  Pointer p4 = std::move(p3);
  ASSERT_EQ(p4, p1);

  Pointer p6(new CType(CTYPE_DOUBLE));
  ASSERT_NE(p6, p2);
  p6 = std::move(p2);
  ASSERT_EQ(p6, p1);
}

TEST(moveCopy, Pointer)
{
  Pointer p1(new CType(CTYPE_INT));

  testMovePointer(p1);
}

TEST(moveCopy, PointerToConst)
{
  Pointer p1 { new ConstQualifiedType(new CType(CTYPE_INT)) };

  testMovePointer(p1);
}

static void testMoveConstPointer(ConstQualifiedType &p1)
{
  ConstQualifiedType p2 { p1 };
  ASSERT_EQ(p1, p2);

  ConstQualifiedType p3 { new Pointer(new CType(CTYPE_DOUBLE)) };
  ASSERT_NE(p3, p1);
  p3 = p1;
  ASSERT_EQ(p3, p1);

  ConstQualifiedType p4 = std::move(p3);
  ASSERT_EQ(p4, p1);

  ConstQualifiedType p6 { new Pointer(new CType(CTYPE_DOUBLE)) };
  ASSERT_NE(p6, p2);
  p6 = std::move(p2);
  ASSERT_EQ(p6, p1);
}

TEST(moveCopy, ConstPointer)
{
  ConstQualifiedType ctp { new Pointer(new CType(CTYPE_INT)) };

  testMoveConstPointer(ctp);
}

TEST(moveCopy, PointerWithRecursField)
{
  StructType *t_struct = new StructType("s_s1", false);
  t_struct->addField(new ComposableField(new Pointer(new IncompleteType(*t_struct, IncompleteType::Type::STRUCT)), "recur"));

  Pointer p1(t_struct);

  testMovePointer(p1);

  ASSERT_TRUE(p1.getPointedType()->isComposableType());

  Pointer p2 = std::move(p1);

  ASSERT_TRUE(p2.getPointedType()->isComposableType());
}

static void testMoveComposableField(ComposableField &f1)
{
  bool isEmbeddedInOtherType = false;
  ComposableField f2(f1);
  ASSERT_EQ(f1, f2);

  ComposableField f3(new StructType("s", ComposableFieldItf::Vector({new ComposableField(CTYPE_INT, "c"), new ComposableField(CTYPE_INT, "d")}), isEmbeddedInOtherType), "e");
  ASSERT_NE(f3,f1);
  f3 = f1;
  ASSERT_EQ(f3,f1);

  ComposableField f4 = std::move(f3);
  ASSERT_EQ(f4, f1);

  ComposableField f6(new StructType("s", ComposableFieldItf::Vector({new ComposableField(CTYPE_INT, "c"), new ComposableField(CTYPE_INT, "d")}), isEmbeddedInOtherType), "e");
  ASSERT_NE(f6, f2);
  f6 = std::move(f2);
  ASSERT_EQ(f6, f1);
}

TEST(moveCopy, ComposableField)
{
  ComposableField f1(CTYPE_INT, "a");

  testMoveComposableField(f1);
}

TEST(moveCopy, StructFieldPtr)
{
  ComposableField f1(new Pointer(new CType(CTYPE_INT)), "a");

  testMoveComposableField(f1);
}

TEST(moveCopy, StructFieldBoundedArray)
{
  ComposableField::attributes composableFieldParam(
  {
    .arraySize = 10
  }
  );
  ComposableField f1(new CType(CTYPE_INT), "boundedArray", composableFieldParam);

  testMoveComposableField(f1);
}

TEST(moveCopy, StructFieldUnBoundedArray)
{
  ComposableField::attributes composableFieldParam(
  {
    .arraySize = 0
  }
  );
  ComposableField f1(new CType(CTYPE_INT), "unBoundedArray", composableFieldParam);

  testMoveComposableField(f1);
}

TEST(moveCopy, ComposableFieldConst)
{
  ComposableField f1 { new ConstQualifiedType(new CType(CTYPE_INT)), "a" };

  testMoveComposableField(f1);
}

TEST(moveCopy, ComposableFieldDeclString)
{
  ComposableField f1(new CType(CTYPE_INT), "a");
  f1.setDeclareString("fromDefine");

  testMoveComposableField(f1);
}

template <class T>
static void testComposableType(T &st1)
{
  bool isEmbeddedInOtherType = false;
  T st2(st1);
  ASSERT_EQ(st1, st2);

  T st3("s", ComposableFieldItf::Vector({new ComposableField(CTYPE_INT, "i")}), isEmbeddedInOtherType);
  ASSERT_NE(st3,st1);
  st3 = st1;
  ASSERT_EQ(st3,st1);

  T st4 = std::move(st3);
  ASSERT_EQ(st4, st1);

  T st6("s", ComposableFieldItf::Vector({new ComposableField(CTYPE_INT, "i")}), isEmbeddedInOtherType);
  ASSERT_NE(st6, st2);
  st6 = std::move(st2);
  ASSERT_EQ(st6, st1);
}

TEST(moveCopy, StructType)
{
  bool isEmbeddedInOtherType = false;
  StructType st1("s", ComposableFieldItf::Vector({new ComposableField(CTYPE_CHAR, "f")}), isEmbeddedInOtherType);

  testComposableType(st1);
}

TEST(moveCopy, UnionType)
{
  bool isEmbeddedInOtherType = false;
  UnionType st1("s", ComposableFieldItf::Vector({new ComposableField(CTYPE_CHAR, "f")}), isEmbeddedInOtherType);

  testComposableType(st1);
}

TEST(moveCopy, StructTypeRecursive)
{
  const TypeItf *pointedType = nullptr;
  bool isEmbeddedInOtherType = false;
  StructType st1("recurs1", isEmbeddedInOtherType);
  st1.addField(new ComposableField(new Pointer(new IncompleteType(st1, IncompleteType::Type::STRUCT)), "rfield"));
  st1.addField(new ComposableField(new CType(CTYPE_INT), "intField"));
  StructType st2(st1);
  ASSERT_EQ(st1, st2);
  const ComposableFieldItf::Vector& st1ContaineField = st1.getContainedFields();
  const ComposableFieldItf::Vector& st2ContaineField = st2.getContainedFields();
  ASSERT_EQ(st1.getFullDeclarationName(), dynamic_cast<const Pointer *>(st1ContaineField[0].getType())->getPointedType()->getFullDeclarationName());
  ASSERT_EQ(st2.getFullDeclarationName(), dynamic_cast<const Pointer *>(st2ContaineField[0].getType())->getPointedType()->getFullDeclarationName());

  StructType st3("s", ComposableFieldItf::Vector({new ComposableField(CTYPE_INT, "i")}), isEmbeddedInOtherType);
  ASSERT_NE(st3,st1);
  st3 = st1;
  ASSERT_EQ(st3,st1);
  const ComposableFieldItf::Vector& st3ContaineField = st3.getContainedFields();
  pointedType = dynamic_cast<const Pointer *>(st3ContaineField[0].getType())->getPointedType();
  ASSERT_EQ(st3.getFullDeclarationName(), pointedType->getFullDeclarationName());
  ASSERT_TRUE(pointedType->isIncompleteType());

  StructType st4 = std::move(st3);
  ASSERT_EQ(st4, st1);
  const ComposableFieldItf::Vector& st4ContaineField = st4.getContainedFields();
  pointedType = dynamic_cast<const Pointer *>(st4ContaineField[0].getType())->getPointedType();
  ASSERT_EQ(st4.getFullDeclarationName(), pointedType->getFullDeclarationName());
  ASSERT_TRUE(pointedType->isIncompleteType());

  StructType st6("s", ComposableFieldItf::Vector({new ComposableField(CTYPE_INT, "i")}), isEmbeddedInOtherType);
  ASSERT_NE(st6, st2);
  st6 = std::move(st2);
  ASSERT_EQ(st6, st1);
  const ComposableFieldItf::Vector& st6ContaineField = st6.getContainedFields();
  pointedType = dynamic_cast<const Pointer *>(st6ContaineField[0].getType())->getPointedType();
  ASSERT_EQ(st6.getFullDeclarationName(), pointedType->getFullDeclarationName());
  ASSERT_TRUE(pointedType->isIncompleteType());
}

TEST(moveCopy, StructTypeSubFieldRecursive)
{
  const TypeItf *pointedType = nullptr;
  bool isEmbeddedInOtherType = true;
  StructType st1("recurs1", isEmbeddedInOtherType);
  StructType* subSt = new StructType("subSt", isEmbeddedInOtherType);
  subSt->addField(new ComposableField(new Pointer(new IncompleteType(st1, IncompleteType::Type::STRUCT)), "rfield"));
  st1.addField(new ComposableField(subSt, "subField"));
  subSt = nullptr; //Dereference, pointer is not usable here anymore
  StructType st2(st1);
  ASSERT_EQ(st1, st2);
  const ComposableFieldItf::Vector& st1ContaineField = st1.getContainedFields();
  const ComposableFieldItf::Vector& st1SubStContainerField = st1ContaineField[0].getType()->getContainedFields();
  pointedType = dynamic_cast<const Pointer *>(st1SubStContainerField[0].getType())->getPointedType();
  ASSERT_EQ(st1.getFullDeclarationName(), pointedType->getFullDeclarationName());
  ASSERT_TRUE(pointedType->isIncompleteType());
  const ComposableFieldItf::Vector& st2ContaineField = st2.getContainedFields();
  const ComposableFieldItf::Vector& st2SubStContainerField = st2ContaineField[0].getType()->getContainedFields();
  pointedType = dynamic_cast<const Pointer *>(st2SubStContainerField[0].getType())->getPointedType();
  ASSERT_EQ(st2.getFullDeclarationName(), pointedType->getFullDeclarationName());
  ASSERT_TRUE(pointedType->isIncompleteType());

  StructType st3("s", ComposableFieldItf::Vector({new ComposableField(CTYPE_INT, "i")}), isEmbeddedInOtherType);
  ASSERT_NE(st3,st1);
  st3 = st1;
  ASSERT_EQ(st3,st1);
  const ComposableFieldItf::Vector& st3ContaineField = st3.getContainedFields();
  const ComposableFieldItf::Vector& st3SubStContainerField = st3ContaineField[0].getType()->getContainedFields();
  pointedType = dynamic_cast<const Pointer *>(st3SubStContainerField[0].getType())->getPointedType();
  ASSERT_EQ(st3.getFullDeclarationName(), pointedType->getFullDeclarationName());
  ASSERT_TRUE(pointedType->isIncompleteType());

  StructType st4 = std::move(st3);
  ASSERT_EQ(st4, st1);
  const ComposableFieldItf::Vector& st4ContaineField = st4.getContainedFields();
  const ComposableFieldItf::Vector& st4SubStContainerField = st4ContaineField[0].getType()->getContainedFields();
  pointedType = dynamic_cast<const Pointer *>(st4SubStContainerField[0].getType())->getPointedType();
  ASSERT_EQ(st4.getFullDeclarationName(), pointedType->getFullDeclarationName());
  ASSERT_TRUE(pointedType);

  StructType st6("s", ComposableFieldItf::Vector({new ComposableField(CTYPE_INT, "i")}), isEmbeddedInOtherType);
  ASSERT_NE(st6, st2);
  st6 = std::move(st2);
  ASSERT_EQ(st6, st1);
  const ComposableFieldItf::Vector& st6ContaineField = st6.getContainedFields();
  const ComposableFieldItf::Vector& st6SubStContainerField = st6ContaineField[0].getType()->getContainedFields();
  pointedType = dynamic_cast<const Pointer *>(st6SubStContainerField[0].getType())->getPointedType();
  ASSERT_EQ(st6.getFullDeclarationName(), pointedType->getFullDeclarationName());
  ASSERT_TRUE(pointedType);
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
  s1->addField(new ComposableField(new Pointer(new IncompleteType(*s1, IncompleteType::Type::STRUCT)), "s1SubS1"));
  s1->addField(new ComposableField(new Pointer(new IncompleteType(s2, IncompleteType::Type::STRUCT)), "s1SubS2"));

  s2.addField(new ComposableField(s1, "s2SubS1"));

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

static void testTypedefType(TypedefType& p1)
{
  TypedefType p2(p1);
  ASSERT_EQ(p1, p2);

  TypedefType p3( "char_t", new CType(CTYPE_DOUBLE));
  ASSERT_NE(p3, p1);
  p3 = p1;
  ASSERT_EQ(p3, p1);

  TypedefType p4 = std::move(p3);
  ASSERT_EQ(p4, p1);

  TypedefType p6("char_t", new CType(CTYPE_DOUBLE));
  ASSERT_NE(p6, p2);
  p6 = std::move(p2);
  ASSERT_EQ(p6, p1);
}

TEST(moveCopy, StructTypedAnonymousTypedDef)
{
  bool isEmbeddedInOtherType = false;

  TypedefType s1 { "Anonymous", new StructType("", isEmbeddedInOtherType) };

  testTypedefType(s1);
}

TEST(moveCopy, UnionTypedAnonymousTypedDef)
{
  bool isEmbeddedInOtherType = false;

  TypedefType u1 { "Anonymous", new UnionType("", isEmbeddedInOtherType) };

  testTypedefType(u1);
}


TEST(moveCopy, StructTypedTypedDef)
{
  bool isEmbeddedInOtherType = false;

  TypedefType s1 { "NotAnonymous", new StructType("foo", isEmbeddedInOtherType) };

  testTypedefType(s1);
}

TEST(moveCopy, UnionTypedTypedDef)
{
  bool isEmbeddedInOtherType = false;

  TypedefType u1 { "NotAnonymous", new UnionType("foo", isEmbeddedInOtherType) };

  testTypedefType(u1);
}

TEST(moveCopy, StructEmbeddedInOtherType)
{
  bool isEmbeddedInOtherType = true;

  TypedefType s1 { "NotAnonymous", new StructType("foo", isEmbeddedInOtherType) };

  testTypedefType(s1);
}

TEST(moveCopy, UnionEmbeddedInOtherType)
{
  bool isEmbeddedInOtherType = true;

  TypedefType u1 { "NotAnonymous", new UnionType("foo", isEmbeddedInOtherType) };

  testTypedefType(u1);
}

TEST(moveCopy, fromSTDIO)
{
  bool isEmbeddedInOtherType = false;
  TypedefType *tFILE_T = new TypedefType("T_MY_IO_FILE" ,new StructType("MY_IO_FILE", isEmbeddedInOtherType));
  StructType *FILE_T = dynamic_cast<StructType*>(tFILE_T->getTypee());
  StructType *IO_MARK = new StructType("MY_IO_MARK", isEmbeddedInOtherType);

  IO_MARK->addField(new ComposableField(new Pointer(new IncompleteType(*IO_MARK, IncompleteType::Type::STRUCT)), "_next"));
  IO_MARK->addField(new ComposableField(new Pointer(new IncompleteType(*tFILE_T, IncompleteType::Type::STRUCT)), "_sbuf"));

  FILE_T->addField(new ComposableField(new Pointer(IO_MARK), "_markers"));
  FILE_T->addField(new ComposableField(new Pointer(new IncompleteType(*tFILE_T, IncompleteType::Type::STRUCT)), "_chain"));

  Parameter *p = new Parameter(new Pointer(tFILE_T), "file");
  FILE_T = nullptr; //We lost the ownership
  Function f1("structFileFromStdio", TypedReturnValue(CTYPE_VOID), Parameter::Vector({p}));
  p = nullptr; //We lost the ownership

  Function f2(f1);

  ASSERT_EQ(f1, f2);
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
  Parameter p1(new Pointer(new CType(CTYPE_VOID)), "v");

  testMoveCopyParameter(p1);
}

TEST(moveCopy, ParameterPointerConst)
{
  Parameter p1 { new Pointer(new ConstQualifiedType(new CType(CTYPE_INT))), "v" };

  testMoveCopyParameter(p1);
}

TEST(moveCopy, ParameterPointerDeclareString)
{
  Parameter p1(new Pointer(new CType(CTYPE_INT)), "v");
  p1.setDeclareString("fromDefine");

  testMoveCopyParameter(p1);
}

TEST(moveCopy, ParameterWithStructSubRecursive)
{
  bool isEmbeddedInOtherType = false;
  StructType *st1 = new StructType("st1", isEmbeddedInOtherType);
  StructType *st2 = new StructType("st2", isEmbeddedInOtherType);
  st1->addField(new ComposableField(st2, "st1SubSt2"));
  //st1 is recursive in st2 because it is access via the parameter "st1Val" which is type st2 and has a st1 as field member
  st2->addField(new ComposableField(new Pointer(new IncompleteType(*st1, IncompleteType::Type::STRUCT)), "st2SubSt1"));
  st2->addField(new ComposableField(new Pointer(new IncompleteType(*st2, IncompleteType::Type::STRUCT)), "st2SubSt2"));
  Parameter p1(st1, "st1Val");

  testMoveCopyParameter(p1);
}

TEST(moveCopy, ParameterWithPointerToStructSubRecursive)
{
  bool isEmbeddedInOtherType = false;
  StructType *st1 = new StructType("st1", isEmbeddedInOtherType);
  StructType *st2 = new StructType("st2", isEmbeddedInOtherType);
  st1->addField(new ComposableField(st2, "st1SubSt2"));
  //st1 is recursive in st2 because it is access via the parameter "st1Val" which is type st2 and has a st1 as field member
  st2->addField(new ComposableField(new Pointer(new IncompleteType(*st1, IncompleteType::Type::STRUCT)), "st2SubSt1"));
  st2->addField(new ComposableField(new Pointer(new IncompleteType(*st2, IncompleteType::Type::STRUCT)), "st2SubSt2"));
  Parameter p1(new Pointer(st1), "st1Val");

  testMoveCopyParameter(p1);
}

static void testMoveCopyReturnValue(ReturnValue& rv1)
{
  bool isEmbeddedInOtherType = false;
  ReturnValue rv2(rv1);
  ASSERT_EQ(rv1, rv2);

  ReturnValue rv3 = StructReturnValue(new StructType("s1", ComposableFieldItf::Vector({new ComposableField(CTYPE_INT, "a")}), isEmbeddedInOtherType));
  ASSERT_NE(rv3,rv1);
  rv3 = rv1;
  ASSERT_EQ(rv3,rv1);

  ReturnValue rv4 = std::move(rv3);
  ASSERT_EQ(rv4, rv1);

  ReturnValue rv6 = StructReturnValue(new StructType("s1", ComposableFieldItf::Vector({new ComposableField(CTYPE_INT, "a")}), isEmbeddedInOtherType));
  ASSERT_NE(rv6, rv2);
  rv6 = std::move(rv2);
  ASSERT_EQ(rv6, rv1);
}

TEST(moveCopy, ReturnValue)
{
  ReturnValue rv1 = VoidReturnValue();

  testMoveCopyReturnValue(rv1);
}

TEST(moveCopy, ReturnValuePointer)
{
  bool isPointer = true;
  ReturnValue rv1 = VoidReturnValue(isPointer);

  testMoveCopyReturnValue(rv1);
}

TEST(moveCopy, ReturnValueConst)
{
  ReturnValue rv1 { new ConstQualifiedType(new CType(CTYPE_INT)) };

  testMoveCopyReturnValue(rv1);
}

TEST(moveCopy, ReturnValueDeclareString)
{
  ReturnValue rv1(new CType(CTYPE_INT));
  rv1.setDeclareString("fromDefine");

  testMoveCopyReturnValue(rv1);
}

#define f1Param VoidReturnValue(), {}
#define f2Param TypedReturnValue(CTYPE_INT), {}

  DECLARE_FUNCTION_TEST_FUNCTION(testFunction)

#undef f1Param
#undef f2Param

TEST(moveCopy, Function)
{
    testFunction<Function, functionTuple>();
}

TEST(moveCopy, FunctionDeclaration)
{
    testFunction<FunctionDeclaration, functionTuple>();
}

TEST(moveCopy, FunctionType)
{
    testFunction<FunctionType, functionTypeTuple>();
}

TEST(moveCopy, Enum)
{
  Enum etype1("e1");
  etype1.addEnumValue(0, "ZERO");
  etype1.addEnumValue(1, "ONE");
  Enum etype2(etype1);
  ASSERT_EQ(etype1, etype2);

  Enum etype3("e2");
  ASSERT_NE(etype3,etype1);
  etype3 = etype1;
  ASSERT_EQ(etype3,etype1);

  Enum etype4 = std::move(etype3);
  ASSERT_EQ(etype4, etype1);

  Enum etype6("e3");
  ASSERT_NE(etype6, etype2);
  etype6 = std::move(etype2);
  ASSERT_EQ(etype6, etype1);
}

void testComposableField(ComposableBitfield& bf1)
{
  ComposableBitfield bf2 { bf1 };
  ASSERT_EQ(bf1, bf2);

  ComposableBitfield bf3(CTYPE_CHAR, "foo", 3);
  ASSERT_NE(bf3,bf1);
  bf3 = bf1;
  ASSERT_EQ(bf3,bf1);

  ComposableBitfield bf4 = std::move(bf3);
  ASSERT_EQ(bf4, bf1);

  ComposableBitfield bf5(CTYPE_CHAR, "bar", 3);
  ASSERT_NE(bf5, bf2);
  bf5 = std::move(bf2);
  ASSERT_EQ(bf5, bf1);

}

TEST(moveCopy, ComposableBitfield)
{
  ComposableBitfield bf1(CTYPE_UCHAR, "foo", 3);
  testComposableField(bf1);
}

TEST(moveCopy, ComposableBitfieldTypedef)
{
  TypedefType typedefType { "t_uint", new CType(CTYPE_UINT) };
  ComposableBitfield bf1{ static_cast<TypedefType*>(typedefType.clone()), "foo", 3 };
  testComposableField(bf1);
}

TEST(moveCopy, ConstQualifiedType)
{
  TypedefType *uChar = new TypedefType("foo", new CType(CTYPE_UCHAR));
  ConstQualifiedType bf1 { uChar };
  ConstQualifiedType bf2 { bf1 };
  ASSERT_EQ(bf1, bf2);

  TypedefType cChar { "foo", new CType(CTYPE_CHAR) };
  ConstQualifiedType bf3{ cChar.clone() };
  ASSERT_NE(bf3,bf1);
  bf3 = bf1;
  ASSERT_EQ(bf3,bf1);

  ConstQualifiedType bf4 = std::move(bf3);
  ASSERT_EQ(bf4, bf1);

  TypedefType* cChar2 = new TypedefType("bar", new CType(CTYPE_CHAR));
  ConstQualifiedType bf5 { cChar2 };
  ASSERT_NE(bf5, bf2);
  bf5 = std::move(bf2);
  ASSERT_EQ(bf5, bf1);
}
