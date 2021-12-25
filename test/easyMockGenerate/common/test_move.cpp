#include <gtest/gtest.h>
#include <EasyMock_CType.h>
#include <Function.h>
#include <Parameter.h>
#include <ComposableField.h>
#include <StructType.h>
#include <UnionType.h>
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
  void test(Param &&... p1, Param &&... p2, Param &&... p3)
  {
    T f1(std::forward<Param>(p1)...);
    T f2(std::forward<Param>(p2)...);
    ASSERT_EQ(f1, f2);

    T f3(std::forward<Param>(p3)...);
    ASSERT_NE(f3,f2);
    f3 = std::move(f1);
    ASSERT_EQ(f3,f2);

    T f4 = std::move(f2);
    ASSERT_EQ(f4, f3);
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
                    f1Param, \
                    f2Param); \
  } \
  else \
  { \
    testStruct.test("foo", f1Param, \
                    "foo", f1Param, \
                    "foo", f2Param); \
  } \
}
}

TEST(moveCopy, CType)
{
  CType ctype1(CTYPE_CHAR);
  CType ctype2(CTYPE_CHAR);
  ASSERT_EQ(ctype1, ctype2);

  CType ctype3 = std::move(ctype2);
  ASSERT_EQ(ctype3, ctype1);

  CType ctype4(CTYPE_DOUBLE);
  ASSERT_NE(ctype4, ctype1);
  ctype4 = std::move(ctype3);
  ASSERT_EQ(ctype4, ctype1);
}

static void testMovePointer(Pointer &p1, Pointer &p2)
{
  ASSERT_EQ(p1, p2);
  Pointer p3 = std::move(p2);
  ASSERT_EQ(p3, p1);

  Pointer p4(std::make_shared<CType>(CTYPE_DOUBLE));
  ASSERT_NE(p4, p1);
  p4 = std::move(p3);
  ASSERT_EQ(p4, p1);
}

TEST(moveCopy, Pointer)
{
  Pointer p1(std::make_shared<CType>(CTYPE_INT));
  Pointer p2(std::make_shared<CType>(CTYPE_INT));

  testMovePointer(p1, p2);
}

TEST(moveCopy, PointerToConst)
{
  Pointer p1 { std::make_shared<ConstQualifiedType>(std::make_shared<CType>(CTYPE_INT)) };
  Pointer p2 { std::make_shared<ConstQualifiedType>(std::make_shared<CType>(CTYPE_INT)) };

  testMovePointer(p1, p2);
}

static void testMoveConstPointer(ConstQualifiedType &p1, ConstQualifiedType &p2)
{
  ASSERT_EQ(p1, p2);
  ConstQualifiedType p3 = std::move(p2);
  ASSERT_EQ(p3, p1);

  ConstQualifiedType p4 {std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_DOUBLE)) };
  ASSERT_NE(p4, p1);
  p4 = std::move(p3);
  ASSERT_EQ(p4, p1);
}

TEST(moveCopy, ConstPointer)
{
  ConstQualifiedType ctp1 { std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_INT)) };
  ConstQualifiedType ctp2 { std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_INT)) };

  testMoveConstPointer(ctp1, ctp2);
}

TEST(moveCopy, PointerWithRecursField)
{
  auto getStructToTest = []()
  {
    auto t_struct = std::make_shared<StructType>("s_s1", false);
    t_struct->addField(ComposableField(std::make_shared<Pointer>(std::make_shared<IncompleteType>(*t_struct, IncompleteType::Type::STRUCT)), "recur"));
    return t_struct;
  };

  Pointer p1(getStructToTest());
  Pointer p2(getStructToTest());


  testMovePointer(p1, p2);

  ASSERT_TRUE(p1.getPointedType()->isComposableType());

  Pointer p3 = std::move(p1);

  ASSERT_TRUE(p3.getPointedType()->isComposableType());
}

static void testMoveComposableField(ComposableField &f1, ComposableField &f2)
{
  bool isEmbeddedInOtherType = false;

  ComposableField f3 = std::move(f2);
  ASSERT_EQ(f3, f1);

  ComposableType::ComposableFieldTypeVector fieldTypeVector;
  fieldTypeVector.emplace_back(ComposableField(CTYPE_INT, "c"));
  fieldTypeVector.emplace_back(ComposableField(CTYPE_INT, "d"));
  ComposableField f4(std::make_shared<StructType>("s", std::move(fieldTypeVector), isEmbeddedInOtherType), "e");
  ASSERT_NE(f4, f1);
  f4 = std::move(f3);
  ASSERT_EQ(f4, f1);
}

TEST(moveCopy, ComposableField)
{
  ComposableField f1(CTYPE_INT, "a");
  ComposableField f2(CTYPE_INT, "a");

  testMoveComposableField(f1, f2);
}

TEST(moveCopy, StructFieldPtr)
{
  ComposableField f1(std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_INT)), "a");
  ComposableField f2(std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_INT)), "a");

  testMoveComposableField(f1, f2);
}

TEST(moveCopy, StructFieldBoundedArray)
{
  ComposableField::attributes composableFieldParam(
  {
    .arraySize = 10
  }
  );
  ComposableField f1(std::make_shared<CType>(CTYPE_INT), "boundedArray", composableFieldParam);
  ComposableField f2(std::make_shared<CType>(CTYPE_INT), "boundedArray", composableFieldParam);

  testMoveComposableField(f1, f2);
}

TEST(moveCopy, StructFieldUnBoundedArray)
{
  ComposableField::attributes composableFieldParam(
  {
    .arraySize = 0
  }
  );
  ComposableField f1(std::make_shared<CType>(CTYPE_INT), "unBoundedArray", composableFieldParam);
  ComposableField f2(std::make_shared<CType>(CTYPE_INT), "unBoundedArray", composableFieldParam);

  testMoveComposableField(f1, f2);
}

TEST(moveCopy, ComposableFieldConst)
{
  ComposableField f1 { std::make_shared<ConstQualifiedType>(std::make_shared<CType>(CTYPE_INT)), "a" };
  ComposableField f2 { std::make_shared<ConstQualifiedType>(std::make_shared<CType>(CTYPE_INT)), "a" };

  testMoveComposableField(f1, f2);
}

TEST(moveCopy, ComposableFieldDeclString)
{
  ComposableField f1(std::make_shared<CType>(CTYPE_INT), "a");
  f1.setDeclareString("fromDefine");

  ComposableField f2(std::make_shared<CType>(CTYPE_INT), "a");
  f2.setDeclareString("fromDefine");

  testMoveComposableField(f1, f2);
}

template <class T>
static void testComposableType(T &st1, T &st2)
{
  bool isEmbeddedInOtherType = false;

  ASSERT_EQ(st1, st2);
  T st3 = std::move(st2);
  ASSERT_EQ(st3, st1);

  ComposableType::ComposableFieldTypeVector fieldTypeVector;
  fieldTypeVector.emplace_back(ComposableField(CTYPE_INT, "i"));
  T st4("s", std::move(fieldTypeVector), isEmbeddedInOtherType);
  ASSERT_NE(st4, st1);
  st4 = std::move(st3);
  ASSERT_EQ(st4, st1);
}

namespace
{
  ComposableType::ComposableFieldTypeVector getVectorFieldTestType()
  {
    ComposableType::ComposableFieldTypeVector fieldTypeVector;
    fieldTypeVector.emplace_back(ComposableField(CTYPE_CHAR, "f"));
    
    return fieldTypeVector;
  }
}
TEST(moveCopy, StructType)
{
  bool isEmbeddedInOtherType = false;
  
  StructType st1("s", getVectorFieldTestType(), isEmbeddedInOtherType);
  StructType st2("s", getVectorFieldTestType(), isEmbeddedInOtherType);

  testComposableType(st1, st2);
}

TEST(moveCopy, UnionType)
{
  bool isEmbeddedInOtherType = false;
  UnionType st1("s", getVectorFieldTestType(), isEmbeddedInOtherType);
  UnionType st2("s", getVectorFieldTestType(), isEmbeddedInOtherType);

  testComposableType(st1, st2);
}

TEST(moveCopy, StructTypeRecursive)
{
  bool isEmbeddedInOtherType = false;
  auto getStructToTest = [&isEmbeddedInOtherType]()
  {
    StructType st1("recurs1", isEmbeddedInOtherType);
    st1.addField(ComposableField(std::make_shared<Pointer>(std::make_shared<IncompleteType>(st1, IncompleteType::Type::STRUCT)), "rfield"));
    st1.addField(ComposableField(std::make_shared<CType>(CTYPE_INT), "intField"));

    return st1;
  };

  StructType st1 = getStructToTest();
  StructType st2 = getStructToTest();
  ASSERT_EQ(st1, st2);

  const TypeItf *pointedType = nullptr;

  const ComposableType::ComposableFieldTypeVector& st1ContaineField = st1.getContainedFields();
  const ComposableType::ComposableFieldTypeVector& st2ContaineField = st2.getContainedFields();
  ASSERT_EQ(st1.getFullDeclarationName(), std::get<ComposableField>(st1ContaineField[0]).getType()->asPointer()->getPointedType()->getFullDeclarationName());
  ASSERT_EQ(st2.getFullDeclarationName(), std::get<ComposableField>(st2ContaineField[0]).getType()->asPointer()->getPointedType()->getFullDeclarationName());

  StructType st3 = std::move(st2);
  ASSERT_EQ(st3, st1);
  const ComposableType::ComposableFieldTypeVector& st4ContaineField = st3.getContainedFields();
  pointedType = std::get<ComposableField>(st4ContaineField[0]).getType()->asPointer()->getPointedType();
  ASSERT_EQ(st3.getFullDeclarationName(), pointedType->getFullDeclarationName());
  ASSERT_TRUE(pointedType->isIncompleteType());

  ComposableType::ComposableFieldTypeVector fieldVector{};
  fieldVector.emplace_back(ComposableField(CTYPE_INT, "i"));
  StructType st4("s", ComposableType::ComposableFieldTypeVector(std::move(fieldVector)), isEmbeddedInOtherType);
  ASSERT_NE(st4, st1);
  st4 = std::move(st3);
  ASSERT_EQ(st4, st1);
  const ComposableType::ComposableFieldTypeVector& st6ContaineField = st4.getContainedFields();
  pointedType = std::get<ComposableField>(st6ContaineField[0]).getType()->asPointer()->getPointedType();
  ASSERT_EQ(st4.getFullDeclarationName(), pointedType->getFullDeclarationName());
  ASSERT_TRUE(pointedType->isIncompleteType());
}

TEST(moveCopy, StructTypeSubFieldRecursive)
{
  bool isEmbeddedInOtherType = true;
  auto getStructToTest = [&isEmbeddedInOtherType]()
  {
    StructType st1("recurs1", isEmbeddedInOtherType);
    auto subSt = std::make_shared<StructType>("subSt", isEmbeddedInOtherType);
    subSt->addField(ComposableField(std::make_shared<Pointer>(std::make_shared<IncompleteType>(st1, IncompleteType::Type::STRUCT)), "rfield"));
    st1.addField(ComposableField(std::move(subSt), "subField"));
    subSt = nullptr; //Dereference, pointer is not usable here anymore

    return st1;
  };

  StructType st1 = getStructToTest();
  StructType st2 = getStructToTest();
  ASSERT_EQ(st1, st2);

  const TypeItf *pointedType = nullptr;
  const ComposableType::ComposableFieldTypeVector& st1ContaineField = st1.getContainedFields();
  const ComposableType::ComposableFieldTypeVector& st1SubStContainerField = std::get<ComposableField>(st1ContaineField[0]).getType()->asComposableType()->getContainedFields();
  pointedType = std::get<ComposableField>(st1SubStContainerField[0]).getType()->asPointer()->getPointedType();
  ASSERT_EQ(st1.getFullDeclarationName(), pointedType->getFullDeclarationName());
  ASSERT_TRUE(pointedType->isIncompleteType());
  const ComposableType::ComposableFieldTypeVector& st2ContaineField = st2.getContainedFields();
  const ComposableType::ComposableFieldTypeVector& st2SubStContainerField = std::get<ComposableField>(st2ContaineField[0]).getType()->asComposableType()->getContainedFields();
  pointedType = std::get<ComposableField>(st2SubStContainerField[0]).getType()->asPointer()->getPointedType();
  ASSERT_EQ(st2.getFullDeclarationName(), pointedType->getFullDeclarationName());
  ASSERT_TRUE(pointedType->isIncompleteType());

  StructType st3 = std::move(st2);
  ASSERT_EQ(st3, st1);
  const ComposableType::ComposableFieldTypeVector& st4ContainedField = st3.getContainedFields();
  const ComposableType::ComposableFieldTypeVector& st4SubStContainerField = std::get<ComposableField>(st4ContainedField[0]).getType()->asComposableType()->getContainedFields();
  pointedType = std::get<ComposableField>(st4SubStContainerField[0]).getType()->asPointer()->getPointedType();
  ASSERT_EQ(st3.getFullDeclarationName(), pointedType->getFullDeclarationName());
  ASSERT_TRUE(pointedType);

  ComposableType::ComposableFieldTypeVector fieldVector{};
  fieldVector.emplace_back(ComposableField(CTYPE_INT, "i"));
  StructType st4("s", std::move(fieldVector), isEmbeddedInOtherType);
  ASSERT_NE(st4, st1);
  st4 = std::move(st3);
  ASSERT_EQ(st4, st1);
  const ComposableType::ComposableFieldTypeVector& st6ContaineField = st4.getContainedFields();
  const ComposableType::ComposableFieldTypeVector& st6SubStContainerField = std::get<ComposableField>(st6ContaineField[0]).getType()->asComposableType()->getContainedFields();
  pointedType = std::get<ComposableField>(st6SubStContainerField[0]).getType()->asPointer()->getPointedType();
  ASSERT_EQ(st4.getFullDeclarationName(), pointedType->getFullDeclarationName());
  ASSERT_TRUE(pointedType);
}

/*
 * struct si1; //Or union
 *
 * struct s1 { //Or union
 *    struct s1 *s1SubS1;
 *    struct si1 *s1SubS2;
 * }
 *
 * struct si1 { //Or union
 *    struct s1 s2SubS1;
 * }
 *
 * test moveCopy(si1);
 */

template <class T>
static void runTypeTwoRecursiveTypes(T &si1, T &si2)
{
  bool isEmbeddedInOtherType = false;
  {
    auto s1 = std::make_shared<T>("s1", isEmbeddedInOtherType);
    s1->addField(ComposableField(std::make_shared<Pointer>(std::make_shared<IncompleteType>(*s1, IncompleteType::Type::STRUCT)), "s1SubS1"));
    s1->addField(ComposableField(std::make_shared<Pointer>(std::make_shared<IncompleteType>(si1, IncompleteType::Type::STRUCT)), "s1SubS2"));
    si1.addField(ComposableField(std::move(s1), "s2SubS1"));
  }

  {
    auto s2 = std::make_shared<T>("s1", isEmbeddedInOtherType);
    s2->addField(ComposableField(std::make_shared<Pointer>(std::make_shared<IncompleteType>(*s2, IncompleteType::Type::STRUCT)), "s1SubS1"));
    s2->addField(ComposableField(std::make_shared<Pointer>(std::make_shared<IncompleteType>(si2, IncompleteType::Type::STRUCT)), "s1SubS2"));
    si2.addField(ComposableField(std::move(s2), "s2SubS1"));
  }

  testComposableType(si1, si2);
}

TEST(moveCopy, StructTypeTwoRecursiveTypes)
{
  bool isEmbeddedInOtherType = false;
  StructType s1("s2", isEmbeddedInOtherType);
  StructType s2("s2", isEmbeddedInOtherType);

  runTypeTwoRecursiveTypes(s1, s2);
}

TEST(moveCopy, UnionTypeTwoRecursiveTypes)
{
  bool isEmbeddedInOtherType = false;
  UnionType u1("u2", isEmbeddedInOtherType);
  UnionType u2("u2", isEmbeddedInOtherType);

  runTypeTwoRecursiveTypes(u1, u2);
}

static void testTypedefType(TypedefType& p1, TypedefType& p2)
{
  TypedefType p3 = std::move(p2);
  ASSERT_EQ(p3, p1);

  TypedefType p4("char_t", std::make_shared<CType>(CTYPE_DOUBLE));
  ASSERT_NE(p4, p1);
  p4 = std::move(p3);
  ASSERT_EQ(p4, p1);
}

TEST(moveCopy, StructTypedAnonymousTypedDef)
{
  bool isEmbeddedInOtherType = false;

  TypedefType s1 { "Anonymous", std::make_shared<StructType>("", isEmbeddedInOtherType) };
  TypedefType s2 { "Anonymous", std::make_shared<StructType>("", isEmbeddedInOtherType) };

  testTypedefType(s1, s2);
}

TEST(moveCopy, UnionTypedAnonymousTypedDef)
{
  bool isEmbeddedInOtherType = false;

  TypedefType u1 { "Anonymous", std::make_shared<UnionType>("", isEmbeddedInOtherType) };
  TypedefType u2 { "Anonymous", std::make_shared<UnionType>("", isEmbeddedInOtherType) };

  testTypedefType(u1, u2);
}


TEST(moveCopy, StructTypedTypedDef)
{
  bool isEmbeddedInOtherType = false;

  TypedefType s1 { "NotAnonymous", std::make_shared<StructType>("foo", isEmbeddedInOtherType) };
  TypedefType s2 { "NotAnonymous", std::make_shared<StructType>("foo", isEmbeddedInOtherType) };

  testTypedefType(s1, s2);
}

TEST(moveCopy, UnionTypedTypedDef)
{
  bool isEmbeddedInOtherType = false;

  TypedefType u1 { "NotAnonymous", std::make_shared<UnionType>("foo", isEmbeddedInOtherType) };
  TypedefType u2 { "NotAnonymous", std::make_shared<UnionType>("foo", isEmbeddedInOtherType) };

  testTypedefType(u1, u2);
}

TEST(moveCopy, StructEmbeddedInOtherType)
{
  bool isEmbeddedInOtherType = true;

  TypedefType s1 { "NotAnonymous", std::make_shared<StructType>("foo", isEmbeddedInOtherType) };
  TypedefType s2 { "NotAnonymous", std::make_shared<StructType>("foo", isEmbeddedInOtherType) };

  testTypedefType(s1, s2);
}

TEST(moveCopy, UnionEmbeddedInOtherType)
{
  bool isEmbeddedInOtherType = true;

  TypedefType u1 { "NotAnonymous", std::make_shared<UnionType>("foo", isEmbeddedInOtherType) };
  TypedefType u2 { "NotAnonymous", std::make_shared<UnionType>("foo", isEmbeddedInOtherType) };

  testTypedefType(u1, u2);
}

TEST(moveCopy, fromSTDIO)
{
  auto getFuntoTest = []()
  {
    bool isEmbeddedInOtherType = false;
    auto tFILE_T = std::make_shared<TypedefType>("T_MY_IO_FILE" ,std::make_shared<StructType>("MY_IO_FILE", isEmbeddedInOtherType));
    StructType *FILE_T = static_cast<StructType*>(tFILE_T->getTypee());
    auto IO_MARK = std::make_shared<StructType>("MY_IO_MARK", isEmbeddedInOtherType);

    IO_MARK->addField(ComposableField(std::make_shared<Pointer>(std::make_shared<IncompleteType>(*IO_MARK, IncompleteType::Type::STRUCT)), "_next"));
    IO_MARK->addField(ComposableField(std::make_shared<Pointer>(std::make_shared<IncompleteType>(*tFILE_T, IncompleteType::Type::STRUCT)), "_sbuf"));

    FILE_T->addField(ComposableField(std::make_shared<Pointer>(std::move(IO_MARK)), "_markers"));
    FILE_T->addField(ComposableField(std::make_shared<Pointer>(std::make_shared<IncompleteType>(*tFILE_T, IncompleteType::Type::STRUCT)), "_chain"));

    Parameter p = Parameter(std::make_shared<Pointer>(std::move(tFILE_T)), "file");
    Parameter::Vector pv{};
    pv.emplace_back(std::move(p));
    Function f1("structFileFromStdio", TypedReturnValue(CTYPE_VOID), std::move(pv));

    return f1;
  };

  Function f1 = getFuntoTest();
  Function f2 = getFuntoTest();

  ASSERT_EQ(f1, f2);

  Function f3 = std::move(f2);
  ASSERT_EQ(f1, f3);
}

static void testMoveCopyParameter(Parameter &p1, Parameter &p2)
{
  ASSERT_EQ(p1, p2);

  Parameter p3 = std::move(p2);
  ASSERT_EQ(p3, p1);

  Parameter p4(std::make_shared<CType>(CTYPE_CHAR), "c");
  ASSERT_NE(p4, p3);
  p4 = std::move(p3);
  ASSERT_EQ(p4, p1);
}

TEST(moveCopy, Parameter)
{
  Parameter p1(std::make_shared<CType>(CTYPE_VOID), "v");
  Parameter p2(std::make_shared<CType>(CTYPE_VOID), "v");

  testMoveCopyParameter(p1, p2);
}

TEST(moveCopy, ParameterPointer)
{
  Parameter p1(std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_VOID)), "v");
  Parameter p2(std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_VOID)), "v");

  testMoveCopyParameter(p1, p2);
}

TEST(moveCopy, ParameterPointerConst)
{
  Parameter p1 { std::make_shared<Pointer>(std::make_shared<ConstQualifiedType>(std::make_shared<CType>(CTYPE_INT))), "v" };
  Parameter p2 { std::make_shared<Pointer>(std::make_shared<ConstQualifiedType>(std::make_shared<CType>(CTYPE_INT))), "v" };

  testMoveCopyParameter(p1, p2);
}

TEST(moveCopy, ParameterPointerDeclareString)
{
  Parameter p1(std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_INT)), "v");
  p1.setDeclareString("fromDefine");
  Parameter p2(std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_INT)), "v");
  p2.setDeclareString("fromDefine");

  testMoveCopyParameter(p1, p2);
}

TEST(moveCopy, ParameterWithStructSubRecursive)
{
  auto getParamToTest = []()
  {
    bool isEmbeddedInOtherType = false;
    auto st1 = std::make_shared<StructType>("st1", isEmbeddedInOtherType);
    auto st2 = std::make_shared<StructType>("st2", isEmbeddedInOtherType);
    st1->addField(ComposableField(st2, "st1SubSt2"));
    //st1 is recursive in st2 because it is access via the parameter "st1Val" which is type st2 and has a st1 as field member
    st2->addField(ComposableField(std::make_shared<Pointer>(std::make_shared<IncompleteType>(*st1, IncompleteType::Type::STRUCT)), "st2SubSt1"));
    st2->addField(ComposableField(std::make_shared<Pointer>(std::make_shared<IncompleteType>(*st2, IncompleteType::Type::STRUCT)), "st2SubSt2"));
    Parameter p1(std::move(st1), "st1Val");

    return p1;
  };

  Parameter p1 = getParamToTest();
  Parameter p2 = getParamToTest();
  testMoveCopyParameter(p1, p2);
}

TEST(moveCopy, ParameterWithPointerToStructSubRecursive)
{
  auto getParamToTest = []()
  {
    bool isEmbeddedInOtherType = false;
    auto st1 = std::make_shared<StructType>("st1", isEmbeddedInOtherType);
    auto st2 = std::make_shared<StructType>("st2", isEmbeddedInOtherType);
    st1->addField(ComposableField(st2, "st1SubSt2"));
    //st1 is recursive in st2 because it is access via the parameter "st1Val" which is type st2 and has a st1 as field member
    st2->addField(ComposableField(std::make_shared<Pointer>(std::make_shared<IncompleteType>(*st1, IncompleteType::Type::STRUCT)), "st2SubSt1"));
    st2->addField(ComposableField(std::make_shared<Pointer>(std::make_shared<IncompleteType>(*st2, IncompleteType::Type::STRUCT)), "st2SubSt2"));
    Parameter p1(std::make_shared<Pointer>(std::move(st1)), "st1Val");

    return p1;
  };

  Parameter p1 = getParamToTest();
  Parameter p2 = getParamToTest();

  testMoveCopyParameter(p1, p2);
}

static void testMoveCopyReturnValue(ReturnValue& rv1, ReturnValue& rv2)
{
  bool isEmbeddedInOtherType = false;
  ASSERT_EQ(rv1, rv2);

  ReturnValue rv3 = std::move(rv2);
  ASSERT_EQ(rv3, rv1);

  ComposableType::ComposableFieldTypeVector fieldVector{};
  fieldVector.emplace_back(ComposableField(CTYPE_INT, "a"));
  ReturnValue rv4 = StructReturnValue(std::make_shared<StructType>("s1", std::move(fieldVector), isEmbeddedInOtherType));
  ASSERT_NE(rv4, rv1);
  rv4 = std::move(rv3);
  ASSERT_EQ(rv4, rv1);
}

TEST(moveCopy, ReturnValue)
{
  ReturnValue rv1 = VoidReturnValue();
  ReturnValue rv2 = VoidReturnValue();

  testMoveCopyReturnValue(rv1, rv2);
}

TEST(moveCopy, ReturnValuePointer)
{
  bool isPointer = true;
  ReturnValue rv1 = VoidReturnValue(isPointer);
  ReturnValue rv2 = VoidReturnValue(isPointer);

  testMoveCopyReturnValue(rv1, rv2);
}

TEST(moveCopy, ReturnValueConst)
{
  ReturnValue rv1 { std::make_shared<ConstQualifiedType>(std::make_shared<CType>(CTYPE_INT)) };
  ReturnValue rv2 { std::make_shared<ConstQualifiedType>(std::make_shared<CType>(CTYPE_INT)) };

  testMoveCopyReturnValue(rv1, rv2);
}

TEST(moveCopy, ReturnValueDeclareString)
{
  ReturnValue rv1(std::make_shared<CType>(CTYPE_INT));
  rv1.setDeclareString("fromDefine");
  ReturnValue rv2(std::make_shared<CType>(CTYPE_INT));
  rv2.setDeclareString("fromDefine");

  testMoveCopyReturnValue(rv1, rv2);
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
  Enum etype2("e1");
  etype2.addEnumValue(0, "ZERO");
  etype2.addEnumValue(1, "ONE");
  ASSERT_EQ(etype1, etype2);

  Enum etype3 = std::move(etype2);
  ASSERT_EQ(etype3, etype1);

  Enum etype4("e4");
  ASSERT_NE(etype4, etype3);
  etype4 = std::move(etype1);
  ASSERT_EQ(etype4, etype3);
}

void testComposableField(ComposableBitfield& bf1, ComposableBitfield &bf2)
{
  ASSERT_EQ(bf1, bf2);

  ComposableBitfield bf3 = std::move(bf2);
  ASSERT_EQ(bf3, bf1);

  ComposableBitfield bf4(CTYPE_CHAR, "bar", 3);
  ASSERT_NE(bf4, bf3);
  bf4 = std::move(bf3);
  ASSERT_EQ(bf4, bf1);

}

TEST(moveCopy, ComposableBitfield)
{
  ComposableBitfield bf1(CTYPE_UCHAR, "foo", 3);
  ComposableBitfield bf2(CTYPE_UCHAR, "foo", 3);

  testComposableField(bf1, bf2);
}

TEST(moveCopy, ComposableBitfieldTypedef)
{
  auto typedefType1 = std::make_shared<TypedefType>("t_uint", std::make_shared<CType>(CTYPE_UINT) );
  ComposableBitfield bf1{std::move(typedefType1), "foo", 3 };
  auto typedefType2 = std::make_shared<TypedefType>("t_uint", std::make_shared<CType>(CTYPE_UINT) );
  ComposableBitfield bf2{std::move(typedefType2), "foo", 3 };
  testComposableField(bf1, bf2);
}

TEST(moveCopy, ConstQualifiedType)
{
  auto uChar1 = std::make_shared<TypedefType>("foo", std::make_shared<CType>(CTYPE_UCHAR));
  ConstQualifiedType cc1 {std::move(uChar1)};
  auto uChar2 = std::make_shared<TypedefType>("foo", std::make_shared<CType>(CTYPE_UCHAR));
  ConstQualifiedType cc2 {std::move(uChar2)};
  ASSERT_EQ(cc1, cc2);

  ConstQualifiedType cc3 = std::move(cc2);
  ASSERT_EQ(cc3, cc1);

  auto uChar3 = std::make_shared<TypedefType>("bar", std::make_shared<CType>(CTYPE_CHAR));
  ConstQualifiedType cc4 {std::move(uChar3)};
  ASSERT_NE(cc4, cc3);
  cc4 = std::move(cc3);
  ASSERT_EQ(cc4, cc1);
}
