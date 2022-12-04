#include <gtest/gtest.h>
#include <EasyMock_CType.h>
#include <Function.h>
#include <Parameter.h>
#include <ReturnValue.h>
#include <StructType.h>
#include <UnionType.h>
#include <ClassType.h>
#include <ComposableField.h>
#include <Pointer.h>
#include <Reference.h>
#include <FunctionType.h>
#include <FunctionDeclaration.h>
#include <Enum.h>
#include <ComposableBitfield.h>
#include <ConstQualifiedType.h>
#include <TypedefType.h>
#include <Namespace.h>
#include <PrintObjects.h>

#include "common.h"

#include <tuple>
#include <type_traits>
#include <memory>

namespace
{
template<typename ...>
struct TestFunctionWrapper;


template<typename T, typename ... Param>
struct TestFunctionWrapper<T, std::tuple<Param ...>>
{
  void testEq(Param &&... p1, Param &&... p2)
  {
    T f1(std::forward<Param>(p1)...);
    T f2(std::forward<Param>(p2)...);
    typeEq(f1, f2);
  }
  void testNe(Param &&... p1, Param &&... p2)
  {
    T f1(std::forward<Param>(p1)...);
    T f2(std::forward<Param>(p2)...);
    typeNe(f1, f2);
  }
};

#define DECLARE_FUNCTION_TEST_FUNCTION(funName, testFun) \
template<typename T, typename ... Param> \
void funName() \
{ \
  TestFunctionWrapper<T, Param...> testStruct{}; \
  if constexpr(std::is_base_of<FunctionType, T>::value) \
  { \
    Parameter::Vector f1ParamVect{}; \
    Parameter::Vector f2ParamVect{}; \
    f1Param; \
    f2Param; \
    testStruct.testFun(f1RetType, std::move(f1ParamVect), \
                    f2RetType, std::move(f2ParamVect)); \
  } \
  else \
  { \
    Parameter::Vector f1ParamVect{}; \
    Parameter::Vector f2ParamVect{}; \
    f1Param; \
    f2Param; \
    testStruct.testFun("foo", f1RetType, std::move(f1ParamVect), \
                    "foo", f2RetType, std::move(f2ParamVect)); \
  } \
}
}

template<typename T1, typename T2>
inline void typeEq(T1& t1, T2& t2)
{
  ASSERT_EQ(t1, t2);
  if constexpr(std::is_base_of<TypeItf, T1>::value)
  {
    ASSERT_TRUE(t1.operator==(t2));
  }
  ASSERT_EQ(t1.getHash(), t2.getHash());
}

template<typename T1, typename T2>
inline void typeNe(T1& t1, T2& t2)
{
  ASSERT_NE(t1, t2);
  if constexpr(std::is_base_of<TypeItf, T1>::value)
  {
    ASSERT_FALSE(t1.operator==(t2));
  }
  ASSERT_NE(t1.getHash(), t2.getHash());
}

TEST(equality, CType)
{
  CType c1(CTYPE_INT);
  CType c2(CTYPE_INT);
  CType c3(CTYPE_DOUBLE);

  typeEq(c1,c2);
  typeNe(c1,c3);
  typeNe(c2,c3);

  TypeItf &tiC1 = c1;
  TypeItf &tiC2 = c2;
  TypeItf &tiC3 = c3;
  typeEq(tiC1,tiC2);
  typeNe(tiC1,tiC3);
  typeNe(tiC2,tiC3);
}

TEST(equality, PointerToConstSame)
{
  Pointer p1 { std::make_shared<ConstQualifiedType>(std::make_shared<CType>(CTYPE_INT)) };
  Pointer p2 { std::make_shared<CType>(CTYPE_INT) };
  Pointer p3 { std::make_shared<ConstQualifiedType>(std::make_shared<CType>(CTYPE_INT)) };

  typeNe(p1, p2);
  typeNe(static_cast<Pointer&>(p1), static_cast<Pointer&>(p2));
  typeEq(p1, p3);
  typeEq(static_cast<Pointer&>(p1), static_cast<Pointer&>(p3));
}

TEST(equality, ConstPointerSame)
{
  ConstQualifiedType ctp1 { std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_INT)) };
  Pointer p1 { std::make_shared<CType>(CTYPE_INT) };
  ConstQualifiedType ctp2 { std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_INT)) };

  typeNe(static_cast<TypeItf&>(ctp1), static_cast<TypeItf&>(p1));
  typeEq(ctp1, ctp2);
}

#define f1RetType VoidReturnValue()
#define f1Param f1ParamVect.emplace_back(NamedParameter(CTYPE_INT, "foo"))

#define f2RetType VoidReturnValue()
#define f2Param f2ParamVect.emplace_back(NamedParameter(CTYPE_DOUBLE, "foo"))

  DECLARE_FUNCTION_TEST_FUNCTION(functionWithDifferentParams, testNe)

#undef f1RetType
#undef f2RetType
#undef f1Param
#undef f2Param

TEST(equality, FunctionWithDifferentParams)
{
  functionWithDifferentParams<Function, functionTuple>();
}

TEST(equality, FunctionTypeWithDifferentParams)
{
  functionWithDifferentParams<FunctionType, functionTypeTuple>();
}

TEST(equality, FunctionDeclarationWithDifferentParams)
{
  functionWithDifferentParams<FunctionDeclaration, functionTuple>();
}

#define f1RetType VoidReturnValue()
#define f1Param f1ParamVect.emplace_back(NamedParameter(CTYPE_INT, "foo"))

#define f2RetType VoidReturnValue()
#define f2Param f2ParamVect.emplace_back(NamedParameter(CTYPE_INT, "bar"))

  DECLARE_FUNCTION_TEST_FUNCTION(functionWithSameParamsButWithDifferentName, testEq)

#undef f1RetType
#undef f2RetType
#undef f1Param
#undef f2Param

TEST(equality, FunctionWithSameParamsButWithDifferentName)
{
  functionWithSameParamsButWithDifferentName<Function, functionTuple>();
}

TEST(equality, FunctionTypeWithSameParamsButWithDifferentName)
{
  functionWithSameParamsButWithDifferentName<FunctionType, functionTypeTuple>();
}

TEST(equality, FunctionDeclarationWithSameParamsButWithDifferentName)
{
  functionWithSameParamsButWithDifferentName<FunctionDeclaration, functionTuple>();
}

#define f1RetType TypedReturnValue(CTYPE_INT)
#define f1Param f1ParamVect.emplace_back(NamedParameter(CTYPE_INT, "foo"))

#define f2RetType TypedReturnValue(CTYPE_DOUBLE)
#define f2Param f2ParamVect.emplace_back(NamedParameter(CTYPE_INT, "bar"))

  DECLARE_FUNCTION_TEST_FUNCTION(functionWithSameParamsButReturnValueIsDifferent, testNe)

#undef f1RetType
#undef f2RetType
#undef f1Param
#undef f2Param

TEST(equality, FunctionWithSameParamsButReturnValueIsDifferent)
{
  functionWithSameParamsButReturnValueIsDifferent<Function, functionTuple>();
}

TEST(equality, FunctionTypeWithSameParamsButReturnValueIsDifferent)
{
  functionWithSameParamsButReturnValueIsDifferent<FunctionType, functionTypeTuple>();
}

TEST(equality, FunctionDeclarationWithSameParamsButReturnValueIsDifferent)
{
  functionWithSameParamsButReturnValueIsDifferent<FunctionDeclaration, functionTuple>();
}

#define f1RetType VoidReturnValue()
#define f1Param f1ParamVect.emplace_back(NamedParameter(CTYPE_INT, "aInt")); \
                f1ParamVect.emplace_back(NamedParameter(CTYPE_DOUBLE, "aDouble"))

#define f2RetType VoidReturnValue()
#define f2Param f2ParamVect.emplace_back(NamedParameter(CTYPE_DOUBLE, "aDouble")); \
                f2ParamVect.emplace_back(NamedParameter(CTYPE_INT, "aInt"))

  DECLARE_FUNCTION_TEST_FUNCTION(functionSameParamsSwaped, testNe)

#undef f1RetType
#undef f2RetType
#undef f1Param
#undef f2Param

TEST(equality, FunctionSameParamsSwaped)
{
  functionSameParamsSwaped<Function, functionTuple>();
}

TEST(equality, FunctionTypeSameParamsSwaped)
{
  functionSameParamsSwaped<FunctionType, functionTypeTuple>();
}

TEST(equality, FunctionDeclarationSameParamsSwaped)
{
  functionSameParamsSwaped<FunctionDeclaration, functionTuple>();
}

TEST(equality, ParameterSameParam)
{
  Parameter p1(std::make_shared<CType>(CTYPE_VOID), "v1");
  Parameter p2(std::make_shared<CType>(CTYPE_VOID), "v2");

  //Even though name is different parameters are the same
  typeEq(p1, p2);
  typeEq(static_cast<Declarator&>(p1), static_cast<Declarator&>(p2));
}

TEST(equality, ParameterPointerSameParam)
{
  Parameter p1(std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_VOID)), "v1");
  Parameter p2(std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_VOID)), "v2");

  //Even though name is different parameters are the same
  typeEq(p1, p2);
  typeEq(static_cast<Declarator&>(p1), static_cast<Declarator&>(p2));
}

TEST(equality, ParameterConstSameParam)
{
  Parameter p1 {std::make_shared<ConstQualifiedType>(std::make_shared<CType>(CTYPE_VOID)), "v1" };
  Parameter p2 {std::make_shared<ConstQualifiedType>(std::make_shared<CType>(CTYPE_VOID)), "v2" };

  //Even though name is different parameters are the same
  typeEq(p1, p2);
  typeEq(static_cast<Declarator&>(p1), static_cast<Declarator&>(p2));
}

TEST(equality, ParameterDeclareStringSameParam)
{
  Parameter p1(std::make_shared<CType>(CTYPE_VOID), "v1");
  Parameter p2(std::make_shared<CType>(CTYPE_VOID), "v2");
  p1.setDeclareString(p1.getType()->getFullDeclarationName());
  p2.setDeclareString(p2.getType()->getFullDeclarationName());

  //Even though name is different parameters are the same
  typeEq(p1, p2);
  typeEq(static_cast<Declarator&>(p1), static_cast<Declarator&>(p2));
}

TEST(equality, ParameterDifferentParam)
{
  Parameter p1(std::make_shared<CType>(CTYPE_INT), "p1");
  Parameter p2(std::make_shared<CType>(CTYPE_VOID), "p1");

  typeNe(p1, p2);
  typeNe(static_cast<Declarator&>(p1), static_cast<Declarator&>(p2));
}

TEST(equality, ParameterPointerDifferentParam)
{
  Parameter p1(std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_INT)), "p1");
  Parameter p2(std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_VOID)), "p1");

  typeNe(p1, p2);
  typeNe(static_cast<Declarator&>(p1), static_cast<Declarator&>(p2));

  Parameter p3(std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_INT)), "p1");
  Parameter p4(std::make_shared<CType>(CTYPE_INT), "p1");

  typeNe(p3, p4);
  typeNe(static_cast<Declarator&>(p3), static_cast<Declarator&>(p4));
}

TEST(equality, ParameterConstDifferentParam)
{
  Parameter p1 { std::make_shared<ConstQualifiedType>(std::make_shared<CType>(CTYPE_INT)), "p1" };
  Parameter p2 { std::make_shared<ConstQualifiedType>(std::make_shared<CType>(CTYPE_VOID)), "p1" };

  typeNe(p1, p2);
  typeNe(static_cast<Declarator&>(p1), static_cast<Declarator&>(p2));

  Parameter p3 { std::make_shared<ConstQualifiedType>(std::make_shared<CType>(CTYPE_INT)), "p1" };
  Parameter p4 { std::make_shared<CType>(CTYPE_INT), "p1" };

  typeNe(p3, p4);
  typeNe(static_cast<Declarator&>(p3), static_cast<Declarator&>(p4));
}

TEST(equality, ParameterDeclareStringDifferentParam)
{
  Parameter p1(std::make_shared<CType>(CTYPE_INT), "p1");
  Parameter p2(std::make_shared<CType>(CTYPE_INT), "p1");
  p1.setDeclareString("fromDefine");

  typeNe(p1, p2);
  typeNe(static_cast<Declarator&>(p1), static_cast<Declarator&>(p2));

  Parameter p3(std::make_shared<CType>(CTYPE_INT), "p1");
  Parameter p4(std::make_shared<CType>(CTYPE_INT), "p1");
  p3.setDeclareString(p3.getType()->getFullDeclarationName());
  p4.setDeclareString("FromDefine");

  typeNe(p3, p4);
  typeNe(static_cast<Declarator&>(p3), static_cast<Declarator&>(p4));
}

TEST(equality, ReturnValueSame)
{
  ReturnValue rv1(std::make_shared<CType>(CTYPE_INT));
  ReturnValue rv2(std::make_shared<CType>(CTYPE_INT));

  typeEq(rv1, rv2);
  typeEq(static_cast<Declarator&>(rv1), static_cast<Declarator&>(rv2));
}

TEST(equality, ReturnValuePointerSame)
{
  ReturnValue rv1(std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_INT)));
  ReturnValue rv2(std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_INT)));

  typeEq(rv1, rv2);
  typeEq(static_cast<Declarator&>(rv1), static_cast<Declarator&>(rv2));
}

TEST(equality, ReturnValueConstSame)
{
  ReturnValue rv1 { std::make_shared<ConstQualifiedType>(std::make_shared<CType>(CTYPE_INT)) };
  ReturnValue rv2 { std::make_shared<ConstQualifiedType>(std::make_shared<CType>(CTYPE_INT)) };

  typeEq(rv1, rv2);
  typeEq(static_cast<Declarator&>(rv1), static_cast<Declarator&>(rv2));
}

TEST(equality, ReturnValueDeclareStringSame)
{
  ReturnValue rv1(std::make_shared<CType>(CTYPE_INT));
  ReturnValue rv2(std::make_shared<CType>(CTYPE_INT));
  rv1.setDeclareString(rv1.getType()->getFullDeclarationName());
  rv2.setDeclareString(rv2.getType()->getFullDeclarationName());

  typeEq(rv1, rv2);
  typeEq(static_cast<Declarator&>(rv1), static_cast<Declarator&>(rv2));
}

TEST(equality, ReturnValueDifferent)
{
  ReturnValue rv1 = VoidReturnValue();
  ReturnValue rv2 = TypedReturnValue(CTYPE_INT);

  typeNe(rv1, rv2);
  typeNe(static_cast<Declarator&>(rv1), static_cast<Declarator&>(rv2));
}

TEST(equality, ReturnValuePointerDifferent)
{
  bool isPointer = true;
  ReturnValue rv1 = VoidReturnValue(isPointer);
  ReturnValue rv2 = TypedReturnValue(CTYPE_INT, isPointer);

  typeNe(rv1, rv2);
  typeNe(static_cast<Declarator&>(rv1), static_cast<Declarator&>(rv2));

  isPointer = true;
  ReturnValue rv3 = TypedReturnValue(CTYPE_INT, isPointer);
  isPointer = false;
  ReturnValue rv4 = TypedReturnValue(CTYPE_INT, isPointer);

  typeNe(rv3, rv4);
  typeNe(static_cast<Declarator&>(rv3), static_cast<Declarator&>(rv4));
}

TEST(equality, ReturnValueConstDifferent)
{
  ReturnValue rv1 = VoidReturnValue();
  ReturnValue rv2 = ReturnValue { std::make_shared<ConstQualifiedType>(std::make_shared<CType>(CTYPE_INT)) };

  typeNe(rv1, rv2);
  typeNe(static_cast<Declarator&>(rv1), static_cast<Declarator&>(rv2));

  ReturnValue rv3 = ReturnValue { std::make_shared<ConstQualifiedType>(std::make_shared<CType>(CTYPE_INT)) };
  ReturnValue rv4 = ReturnValue { std::make_shared<CType>(CTYPE_INT) };

  typeNe(rv3, rv4);
  typeNe(static_cast<Declarator&>(rv3), static_cast<Declarator&>(rv4));
}

TEST(equality, ReturnValueDeclareStringDifferent)
{
  ReturnValue rv1(std::make_shared<CType>(CTYPE_INT));
  ReturnValue rv2(std::make_shared<CType>(CTYPE_INT));
  rv1.setDeclareString("FromDefine");

  typeNe(rv1, rv2);
  typeNe(static_cast<Declarator&>(rv1), static_cast<Declarator&>(rv2));

  ReturnValue rv3(std::make_shared<CType>(CTYPE_INT));
  ReturnValue rv4(std::make_shared<CType>(CTYPE_INT));
  rv3.setDeclareString(rv3.getType()->getFullDeclarationName());
  rv4.setDeclareString("FromDefine");

  typeNe(rv3, rv4);
  typeNe(static_cast<Declarator&>(rv3), static_cast<Declarator&>(rv4));
}

TEST(equality, StructFieldSame)
{
  ComposableField f1(CTYPE_INT, "a");
  ComposableField f2(CTYPE_INT, "a");

  typeEq(f1, f2);
  typeEq(static_cast<Declarator&>(f1), static_cast<Declarator&>(f2));

  bool isEmbeddedInOtherType = false;
  auto getFieldVector = []()
  {
    ComposableType::ComposableFieldTypeVector fieldVectorF3{};
    fieldVectorF3.emplace_back(ComposableField(CTYPE_INT, "c"));
    fieldVectorF3.emplace_back(ComposableField(CTYPE_INT, "d"));

    return fieldVectorF3;
  };
  ComposableField f3(std::make_shared<StructType>("s", getFieldVector(), isEmbeddedInOtherType), "e");
  ComposableField f4(std::make_shared<StructType>("s", getFieldVector(), isEmbeddedInOtherType), "e");

  typeEq(f3, f4);
  typeEq(static_cast<Declarator&>(f3), static_cast<Declarator&>(f4));
}

TEST(equality, StructFieldPointerSame)
{
  ComposableField f1(std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_INT)), "a");
  ComposableField f2(std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_INT)), "a");

  typeEq(f1, f2);
  typeEq(static_cast<Declarator&>(f1), static_cast<Declarator&>(f2));

  bool isEmbeddedInOtherType = false;
  auto getFieldVector = []()
  {
    ComposableType::ComposableFieldTypeVector fieldVector{};
    fieldVector.emplace_back(ComposableField{CTYPE_INT, "c"});
    fieldVector.emplace_back(ComposableField{CTYPE_INT, "d"});

    return fieldVector;
  };
  ComposableField f3(std::make_shared<StructType>("s", getFieldVector(), isEmbeddedInOtherType), "e");
  ComposableField f4(std::make_shared<StructType>("s", getFieldVector(), isEmbeddedInOtherType), "e");

  typeEq(f3, f4);
  typeEq(static_cast<Declarator&>(f3), static_cast<Declarator&>(f4));

  std::get<ComposableField>(f3.getType()->asComposableType()->getContainedFields()[1]).setArraySize(10);
  typeNe(f3, f4);
  typeNe(static_cast<Declarator&>(f3), static_cast<Declarator&>(f4));
  std::get<ComposableField>(f4.getType()->asComposableType()->getContainedFields()[1]).setArraySize(10);
  typeEq(f3, f4);
  typeEq(static_cast<Declarator&>(f3), static_cast<Declarator&>(f4));
}

TEST(equality, StructFieldConstSame)
{
  ComposableField f1 { std::make_shared<ConstQualifiedType>(std::make_shared<CType>(CTYPE_INT)), "a" };
  ComposableField f2 { std::make_shared<ConstQualifiedType>(std::make_shared<CType>(CTYPE_INT)), "a" };

  typeEq(f1, f2);
  typeEq(static_cast<Declarator&>(f1), static_cast<Declarator&>(f2));
}

TEST(equality, StructFieldDeclStringSame)
{
  ComposableField f1(std::make_shared<CType>(CTYPE_INT), "a");
  ComposableField f2(std::make_shared<CType>(CTYPE_INT), "a");
  f1.setDeclareString(f1.getType()->getFullDeclarationName());
  f2.setDeclareString(f2.getType()->getFullDeclarationName());

  typeEq(f1, f2);
  typeEq(static_cast<Declarator&>(f1), static_cast<Declarator&>(f2));
}

TEST(equality, StructFieldDifferent)
{
  ComposableField f1(CTYPE_INT, "a");
  ComposableField f2(CTYPE_DOUBLE, "a");

  typeNe(f1, f2);
  typeNe(static_cast<Declarator&>(f1), static_cast<Declarator&>(f2));

  bool isEmbeddedInOtherType = false;
  ComposableType::ComposableFieldTypeVector fieldVectorF3{};
  fieldVectorF3.emplace_back(ComposableField{CTYPE_INT, "c"});
  fieldVectorF3.emplace_back(ComposableField{CTYPE_INT, "d"});
  ComposableField f3(std::make_shared<StructType>("s", std::move(fieldVectorF3), isEmbeddedInOtherType), "e");

  ComposableType::ComposableFieldTypeVector fieldVectorF4{};
  fieldVectorF4.emplace_back(ComposableField{CTYPE_INT, "c"});
  fieldVectorF4.emplace_back(ComposableField{CTYPE_DOUBLE, "d"});
  ComposableField f4(std::make_shared<StructType>("s", std::move(fieldVectorF4), isEmbeddedInOtherType), "e");

  typeNe(f3, f4);
  typeNe(static_cast<Declarator&>(f3), static_cast<Declarator&>(f4));
}

TEST(equality, StructFieldConstDifferent)
{
  ComposableField f1 { std::make_shared<CType>(CTYPE_INT), "a" };
  ComposableField f2 { std::make_shared<ConstQualifiedType>(std::make_shared<CType>(CTYPE_INT)), "a" };

  typeNe(f1, f2);
  typeNe(static_cast<Declarator&>(f1), static_cast<Declarator&>(f2));
}

TEST(equality, StructFieldDeclStringDifferent)
{
  ComposableField f1(std::make_shared<CType>(CTYPE_INT), "a");
  ComposableField f2(std::make_shared<CType>(CTYPE_INT), "a");
  f1.setDeclareString(f1.getType()->getFullDeclarationName());
  f2.setDeclareString("FromMacro");

  typeNe(f1, f2);
  typeNe(static_cast<Declarator&>(f1), static_cast<Declarator&>(f2));
}

template <class T>
static void runComposableTypeSame(T &s1, T &s2)
{
  typeEq(s1, s2);
  //Test from base class to make sure that the comparison overload is working
  TypeItf &sTitfS1 = s1;
  TypeItf &sTitfS2 = s2;
  typeEq(sTitfS1, sTitfS2);

  if constexpr(std::is_base_of<ComposableType, T>::value)
  {
    bool isEmbeddedInOtherType = false;
    auto getFieldVector = []()
    {
      ComposableType::ComposableFieldTypeVector fieldVector;
      fieldVector.emplace_back(ComposableField{CTYPE_CHAR, "f"});

      return fieldVector;
    };
    T s3("s", getFieldVector(), isEmbeddedInOtherType);
    T s4("s", getFieldVector(), isEmbeddedInOtherType);

    typeEq(s3, s4);
    //Test from base class to make sure that the comparison overload is working
    TypeItf &sTitfS3 = s3;
    TypeItf &sTitfS4 = s4;
    typeEq(sTitfS3, sTitfS4);
  }
}

TEST(equality, StructTypeSame)
{
  bool isEmbeddedInOtherType = false;
  StructType s1("s", {}, isEmbeddedInOtherType);
  StructType s2("s", {}, isEmbeddedInOtherType);

  runComposableTypeSame(s1, s2);
}

TEST(equality, UnionTypeSame)
{
  bool isEmbeddedInOtherType = true;
  UnionType u1("s", {}, isEmbeddedInOtherType);
  UnionType u2("s", {}, isEmbeddedInOtherType);

  runComposableTypeSame(u1, u2);
}

template <class T1, class T2>
static void runComposableTypeDifferent(T1 &s1, T2 &s2)
{
  typeNe(s1,s2);
  //Test from base class to make sure that the comparison overload is working
  TypeItf &sTitfS1 = s1;
  TypeItf &sTitfS2 = s2;
  typeNe(sTitfS1, sTitfS2);
}

TEST(equality, StructTypeDifferent)
{
  bool isEmbeddedInOtherType = false;
  StructType s1("s", {}, isEmbeddedInOtherType);
  ComposableType::ComposableFieldTypeVector fieldVector{};
  fieldVector.emplace_back(ComposableField{CTYPE_CHAR, "f"});
  StructType s2("s", std::move(fieldVector), isEmbeddedInOtherType);

  runComposableTypeDifferent(s1, s2);
}

TEST(equality, UnionTypeDifferent)
{
  bool isEmbeddedInOtherType = false;
  UnionType u1("s", {}, isEmbeddedInOtherType);
  ComposableType::ComposableFieldTypeVector fieldVector{};
  fieldVector.emplace_back(ComposableField{CTYPE_CHAR, "f"});
  UnionType u2("s", std::move(fieldVector), isEmbeddedInOtherType);

  runComposableTypeDifferent(u1, u2);
}

TEST(equality, StructTypedDefEqual)
{
  bool isEmbeddedInOtherType = false;

  TypedefType s1 { "typeS1", std::make_shared<StructType>("s1", isEmbeddedInOtherType) };
  TypedefType s2 { "typeS1", std::make_shared<StructType>("s1", isEmbeddedInOtherType) };

  runComposableTypeSame(s1, s2);
}

TEST(equality, UnionTypedDefEqual)
{
  bool isEmbeddedInOtherType = false;

  TypedefType u1 { "typeU1", std::make_shared<UnionType>("u1", isEmbeddedInOtherType) };
  TypedefType u2 { "typeU1", std::make_shared<UnionType>("u1", isEmbeddedInOtherType) };

  runComposableTypeSame(u1, u2);
}

TEST(equality, StructTypedDefDifferent)
{
  bool isEmbeddedInOtherType = false;

  StructType s1("s1", isEmbeddedInOtherType);
  TypedefType s2 { "s1", std::make_shared<StructType>("", isEmbeddedInOtherType) };

  runComposableTypeDifferent(s1, s2);
}

TEST(equality, UnionTypedDefDifferent)
{
  bool isEmbeddedInOtherType = false;

  UnionType u1("u1", isEmbeddedInOtherType);
  TypedefType u2 { "u1", std::make_shared<UnionType>("", isEmbeddedInOtherType) };

  runComposableTypeDifferent(u1, u2);
}

TEST(equality, StructEmbeddedInOtherTypeDifferent)
{
  bool isEmbeddedInOtherType = false;

  TypedefType s1 { "typeS1", std::make_shared<StructType>("s1", isEmbeddedInOtherType) };
  TypedefType s2 { "typeS1", std::make_shared<StructType>("s1", !isEmbeddedInOtherType) };

  runComposableTypeDifferent(s1, s2);
}

TEST(equality, UnionEmbeddedInOtherTypeDifferent)
{
  bool isEmbeddedInOtherType = false;

  TypedefType u1 { "typeU1", std::make_shared<UnionType>("u1", isEmbeddedInOtherType) };
  TypedefType u2 { "typeU1", std::make_shared<UnionType>("u1", !isEmbeddedInOtherType) };

  runComposableTypeDifferent(u1, u2);
}

TEST(equality, AnonymousTypedefDifferentWithSameField)
{
  bool isEmbeddedInOtherType = false;

  TypedefType tst1 { "TypedDefAnonymousStruct", std::make_shared<StructType>("", isEmbeddedInOtherType) };
  ComposableType *st1 = tst1.getTypee()->asComposableType();
  st1->addField(ComposableField{CTYPE_INT, "a"});

  TypedefType tst2 { "TypedDefAnonymousStruct2", std::make_shared<StructType>("", isEmbeddedInOtherType) };
  ComposableType *st2 = tst2.getTypee()->asComposableType();
  st2->addField(ComposableField{CTYPE_INT, "a"});

  runComposableTypeDifferent(tst1, tst2);
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

  typeNe(s1, u1);

  TypeItf &tS1 = s1;
  TypeItf &tU1 = u1;

  typeNe(tS1, tU1);
}

TEST(equality, Enum)
{
  Enum e1("e1");
  e1.addEnumValue(0, "ZERO");
  e1.addEnumValue(1, "ONE");
  Enum e2("e1");
  e2.addEnumValue(0, "ZERO");
  e2.addEnumValue(1, "ONE");
  Enum e3("e2");
  e3.addEnumValue(0, "ZERO");
  e3.addEnumValue(1, "ONE");
  Enum e4("e2");
  e4.addEnumValue(0, "ZERO");
  e4.addEnumValue(2, "ONE");
  Enum e5("e2");
  e4.addEnumValue(0, "ZERO");
  e4.addEnumValue(1, "TWO");

  typeEq(e1,e2);
  typeNe(e1,e3);
  typeNe(e2,e3);
  typeNe(e3,e4);
  typeNe(e3,e5);

  TypeItf &tiC1 = e1;
  TypeItf &tiC2 = e2;
  TypeItf &tiC3 = e3;
  TypeItf &tiC4 = e4;
  TypeItf &tiC5 = e5;
  typeEq(tiC1,tiC2);
  typeNe(tiC1,tiC3);
  typeNe(tiC2,tiC3);
  typeNe(tiC3,tiC4);
  typeNe(tiC3,tiC5);
}

TEST(equality, ComposableBitfield)
{
  ComposableBitfield f1(CTYPE_INT, "foo", 3);
  ComposableBitfield f2(CTYPE_INT, "foo", 3);
  typeEq(f1, f2);

  ComposableBitfield f3(CTYPE_UINT, "foo", 3);
  typeNe(f3, f1);

  ComposableBitfield f4(CTYPE_INT, "bar", 3);
  typeNe(f4, f1);

  ComposableBitfield f5(CTYPE_INT, "foo", 4);
  typeNe(f5, f1);
}

TEST(equality, TypeItf)
{
  TypedefType t1("t1", std::make_shared<CType>(CTYPE_INT));
  TypedefType t2("t1", std::make_shared<CType>(CTYPE_INT));
  TypedefType t3("t2", std::make_shared<CType>(CTYPE_INT));

  typeEq(t1, t2);
  typeNe(t1, t3);

  TypeItf &tt1 = t1;
  TypeItf &tt2 = t2;
  TypeItf &tt3 = t3;

  typeEq(tt1, tt2);
  typeNe(tt1, tt3);
}

TEST(equality, FunctionAttributeEqual)
{
  Function f1{"foo", VoidReturnValue(), Parameter::Vector{}};
  Function f2{"foo", VoidReturnValue(), Parameter::Vector{}};

  FunctionAttribute fa1{"printf", FunctionAttribute::ParametersList {"1", "2"}};
  f1.addAttribute(std::move(fa1));

  FunctionAttribute fa2{"printf", FunctionAttribute::ParametersList {"1", "2"}};
  f2.addAttribute(std::move(fa2));

  ASSERT_EQ(f1, f2);
}


TEST(equality, FunctionAttributeDifferent)
{
  Function f1{"foo", VoidReturnValue(), Parameter::Vector{}};
  Function f2{"foo", VoidReturnValue(), Parameter::Vector{}};

  FunctionAttribute fa1{"printf", FunctionAttribute::ParametersList {"1", "2"}};
  f1.addAttribute(std::move(fa1));

  FunctionAttribute fa2{"printf2", FunctionAttribute::ParametersList {"1", "2"}};
  f2.addAttribute(std::move(fa2));

  ASSERT_NE(f1, f2);
}

TEST(equality, FunctionAttributeParamDifferent)
{
  Function f1{"foo", VoidReturnValue(), Parameter::Vector{}};
  Function f2{"foo", VoidReturnValue(), Parameter::Vector{}};

  FunctionAttribute fa1{"printf", FunctionAttribute::ParametersList {"1", "2"}};
  f1.addAttribute(std::move(fa1));

  FunctionAttribute fa2{"printf", FunctionAttribute::ParametersList {"2", "3"}};
  f2.addAttribute(std::move(fa2));

  ASSERT_NE(f1, f2);
}

TEST(equality, FunctionAttributeAgainstFunctionNoAttribute)
{
  FunctionDeclaration f1{"foo", VoidReturnValue(), Parameter::Vector{}};
  FunctionAttribute fa1{"printf", FunctionAttribute::ParametersList {"1", "2"}};
  f1.addAttribute(std::move(fa1));

  FunctionDeclaration f2{"foo", VoidReturnValue(), Parameter::Vector{}};

  ASSERT_NE(f1, f2);
}

TEST(equality, FunctionDeclHasBodySame)
{
  FunctionDeclaration f1{"foo", VoidReturnValue(), {}};
  FunctionDeclaration f2{"foo", VoidReturnValue(), {}};

  f1.setDoesThisDeclarationHasABody(true);
  f2.setDoesThisDeclarationHasABody(true);

  ASSERT_EQ(f1, f2);
  ASSERT_EQ(f1.getHash(), f2.getHash());

  f1.setDoesThisDeclarationHasABody(false);
  f2.setDoesThisDeclarationHasABody(false);

  ASSERT_EQ(f1, f2);
  ASSERT_EQ(f1.getHash(), f2.getHash());
}

TEST(equality, FunctionDeclHasBodyDifferent)
{
  FunctionDeclaration f1{"foo", VoidReturnValue(), {}};
  FunctionDeclaration f2{"foo", VoidReturnValue(), {}};

  f1.setDoesThisDeclarationHasABody(true);
  f2.setDoesThisDeclarationHasABody(false);

  ASSERT_NE(f1, f2);
  ASSERT_NE(f1.getHash(), f2.getHash());

  f1.setDoesThisDeclarationHasABody(false);
  f2.setDoesThisDeclarationHasABody(true);

  ASSERT_NE(f1, f2);
  ASSERT_NE(f1.getHash(), f2.getHash());
}

TEST(equality, FunctionRawHash_typedef_SameOnParam)
{
  Parameter::Vector pvf1{};
  pvf1.emplace_back(std::make_shared<CType>(CTYPE_INT), "p");
  FunctionDeclaration f1{"foo", VoidReturnValue(), std::move(pvf1)};

  auto tInt = std::make_shared<TypedefType>("tint", std::make_shared<CType>(CTYPE_INT));
  Parameter::Vector pvf2{};
  pvf2.emplace_back(std::move(tInt), "p");
  FunctionDeclaration f2{"foo", VoidReturnValue(), std::move(pvf2)};

  ASSERT_NE(f1, f2);
  ASSERT_EQ(f1.getRawHash(), f2.getRawHash());
}

TEST(equality, FunctionRawHash_typedef_SameOnReturnValue)
{
  auto tInt = std::make_shared<TypedefType>("tint", std::make_shared<CType>(CTYPE_INT));
  ReturnValue frv1{std::make_shared<CType>(CTYPE_INT)};
  ReturnValue frv2{std::move(tInt)};

  FunctionDeclaration f1{"foo", std::move(frv1), {}};
  FunctionDeclaration f2{"foo", std::move(frv2), {}};

  ASSERT_NE(f1, f2);
  ASSERT_EQ(f1.getRawHash(), f2.getRawHash());
}

TEST(equality, FunctionRawHash_pointer_differentParam)
{
  auto pInt = std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_INT));

  Parameter::Vector pvf1{};
  pvf1.emplace_back(Parameter{std::make_shared<CType>(CTYPE_INT), "p"});
  FunctionDeclaration f1{"foo", VoidReturnValue(), std::move(pvf1)};
  Parameter::Vector pvf2{};
  pvf2.emplace_back(Parameter{std::move(pInt), "p"});
  FunctionDeclaration f2{"foo", VoidReturnValue(), std::move(pvf2)};

  ASSERT_NE(f1, f2);
  ASSERT_NE(f1.getRawHash(), f2.getRawHash());
}

TEST(equality, Namespace_global)
{
  auto g1 = getGlobalNamespace();
  auto g2 = getGlobalNamespace();

  // Check whether they are actually pointing to the same object
  ASSERT_EQ(g1, g2);
}

TEST(equality, Namespace_simple)
{
  Namespace l1{"L1"};
  Namespace l2{"L1"};

  ASSERT_EQ(l1, l2);
}

TEST(equality, Namespace_double_different_shared_ptr_parent)
{
  Namespace l1l2_left{"L2", std::make_shared<const Namespace>("L1")};
  Namespace l1l2_right{"L2", std::make_shared<const Namespace>("L1")};

  ASSERT_EQ(l1l2_left, l1l2_right);
  ASSERT_EQ(l1l2_left.getHash(), l1l2_right.getHash());
}

TEST(equality, Namespace_double_same_shared_ptr_parent)
{
  auto l1 = std::make_shared<const Namespace>("L1");
  Namespace l1l2_left{"L2", l1};
  Namespace l1l2_right{"L2", l1};

  ASSERT_EQ(l1l2_left, l1l2_right);
}

TEST(equality, Function_namespace_vs_no_namespace)
{
  FunctionDeclaration f1{"foo", VoidReturnValue(), Parameter::Vector {}};
  FunctionDeclaration f2{"foo", VoidReturnValue(), Parameter::Vector {}, std::make_shared<const Namespace>("L1")};
  ASSERT_NE(f1, f2);
  ASSERT_NE(f1.getHash(), f2.getHash());
}

TEST(equality, Function_namespace_vs_sub_namespace)
{
  auto L1Namespace = std::make_shared<const Namespace>("L1");
  FunctionDeclaration f1{"foo", VoidReturnValue(), Parameter::Vector {}, L1Namespace};
  auto L2Namespace = std::make_shared<const Namespace>("L2", std::move(L1Namespace));
  FunctionDeclaration f2{"foo", VoidReturnValue(), Parameter::Vector {}, L2Namespace};
  ASSERT_NE(f1, f2);
  ASSERT_NE(f1.getHash(), f2.getHash());
}

TEST(equality, cpp_class_equal)
{
  ClassType c1{"c1", false};
  c1.addFunction(getF1());
  c1.addFunction(getF2());
  ClassType c2{"c1", false};
  c2.addFunction(getF1());
  c2.addFunction(getF2());

  ASSERT_EQ(c1, c2);
  ASSERT_EQ(c1.getHash(), c2.getHash());
}

TEST(equality, cpp_class_not_equal_different_functions)
{
  ClassType c1{"c1", false};
  c1.addFunction(getF1());
  c1.addFunction(getF2());
  ClassType c2{"c1", false};
  c2.addFunction(getF1());

  ASSERT_NE(c1, c2);
  ASSERT_NE(c1.getHash(), c2.getHash());
}

TEST(equality, cpp_struct_not_equal_class)
{
  StructType s1{"c1", false};
  s1.addFunction(getF1());
  s1.addFunction(getF2());
  ClassType c1{"c1", false};
  c1.addFunction(getF1());
  c1.addFunction(getF2());

  ASSERT_NE(s1, c1);
  ASSERT_NE(s1.getHash(), c1.getHash());
}

TEST(equality, cpp_class_different_name)
{
  ClassType c1{"c1", false};
  c1.addFunction(getF1());
  c1.addFunction(getF2());
  ClassType c2{"c2", false};
  c2.addFunction(getF1());
  c2.addFunction(getF2());

  ASSERT_NE(c1, c2);
  ASSERT_NE(c1.getHash(), c2.getHash());
}

TEST(equality, cpp_function_class_const)
{
  auto c1 = std::make_shared<ClassType>("c1", false);
  FunctionDeclaration f1_1{"f1", VoidReturnValue(), Parameter::Vector {}, getGlobalNamespace(), c1};
  f1_1.setClassConst(true);

  FunctionDeclaration f1_2{"f1", VoidReturnValue(), Parameter::Vector {}, getGlobalNamespace(), c1};
  f1_2.setClassConst(true);

  EXPECT_EQ(f1_1, f1_2);
  EXPECT_EQ(f1_1.getHash(), f1_2.getHash());

  FunctionDeclaration f1_3{"f1", VoidReturnValue(), Parameter::Vector {}, getGlobalNamespace(), c1};
  EXPECT_NE(f1_1, f1_3);
  EXPECT_NE(f1_1.getHash(), f1_3.getHash());
}

TEST(equality, cpp_reference)
{
  Reference r1 {std::make_shared<CType>(CTYPE_INT)};
  Reference r2{std::make_shared<CType>(CTYPE_INT)};

  EXPECT_EQ(r1, r2);
  EXPECT_EQ(r1.getHash(), r2.getHash());

  Reference r3 {std::make_shared<CType>(CTYPE_FLOAT)};
  EXPECT_NE(r1, r3);
  EXPECT_NE(r1.getHash(), r3.getHash());
}

TEST(equality, cpp_reference_vs_pointer)
{
  Reference r1 {std::make_shared<CType>(CTYPE_INT)};
  Pointer p2{std::make_shared<CType>(CTYPE_INT)};

  EXPECT_NE(r1, p2);
  EXPECT_NE(p2, r1);
  EXPECT_NE(r1.getHash(), p2.getHash());
}