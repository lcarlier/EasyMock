#include <gtest/gtest.h>
#include <EasyMock_CType.h>
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
#include <ComposableBitfield.h>
#include <ConstQualifiedType.h>
#include <TypedefType.h>

#include "common.h"

#include <tuple>
#include <type_traits>

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
    testStruct.testFun(f1Param, \
                    f2Param); \
  } \
  else \
  { \
    testStruct.testFun("foo", f1Param, \
                    "foo", f2Param); \
  } \
}
}

template<typename T1, typename T2>
inline void typeEq(T1& t1, T2& t2)
{
  ASSERT_EQ(t1, t2);
  if constexpr(std::is_base_of<TypeItf, T1>::value)
  {
    ASSERT_TRUE(t1.isEqual(t2));
  }
  ASSERT_EQ(t1.getHash(), t2.getHash());
}

template<typename T1, typename T2>
inline void typeNe(T1& t1, T2& t2)
{
  ASSERT_NE(t1, t2);
  if constexpr(std::is_base_of<TypeItf, T1>::value)
  {
    ASSERT_FALSE(t1.isEqual(t2));
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
  Pointer p1 { new ConstQualifiedType(new CType(CTYPE_INT)) };
  Pointer p2 { new CType(CTYPE_INT) };
  Pointer p3 { new ConstQualifiedType(new CType(CTYPE_INT)) };

  typeNe(p1, p2);
  typeNe(static_cast<Pointer&>(p1), static_cast<Pointer&>(p2));
  typeEq(p1, p3);
  typeEq(static_cast<Pointer&>(p1), static_cast<Pointer&>(p3));
}

TEST(equality, ConstPointerSame)
{
  ConstQualifiedType ctp1 { new Pointer (new CType(CTYPE_INT)) };
  Pointer p1 { new CType(CTYPE_INT) };
  ConstQualifiedType ctp2 { new Pointer (new CType(CTYPE_INT)) };

  typeNe(static_cast<TypeItf&>(ctp1), static_cast<TypeItf&>(p1));
  typeEq(ctp1, ctp2);
}

#define f1Param VoidReturnValue(), Parameter::Vector({NamedParameter(CTYPE_INT, "foo")})
#define f2Param VoidReturnValue(), Parameter::Vector({NamedParameter(CTYPE_DOUBLE, "foo")})

  DECLARE_FUNCTION_TEST_FUNCTION(functionWithDifferentParams, testNe)

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

#define f1Param VoidReturnValue(), Parameter::Vector({NamedParameter(CTYPE_INT, "foo")})
#define f2Param VoidReturnValue(), Parameter::Vector({NamedParameter(CTYPE_INT, "bar")})

  DECLARE_FUNCTION_TEST_FUNCTION(functionWithSameParamsButWithDifferentName, testEq)

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

#define f1Param TypedReturnValue(CTYPE_INT), Parameter::Vector({NamedParameter(CTYPE_INT, "foo")})
#define f2Param TypedReturnValue(CTYPE_DOUBLE), Parameter::Vector({NamedParameter(CTYPE_INT, "bar")})

  DECLARE_FUNCTION_TEST_FUNCTION(functionWithSameParamsButReturnValueIsDifferent, testNe)

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

#define f1Param VoidReturnValue(), Parameter::Vector({NamedParameter(CTYPE_INT, "aInt"), NamedParameter(CTYPE_DOUBLE, "aDouble")})
#define f2Param VoidReturnValue(), Parameter::Vector({NamedParameter(CTYPE_DOUBLE, "aDouble"), NamedParameter(CTYPE_INT, "aInt")})

  DECLARE_FUNCTION_TEST_FUNCTION(functionSameParamsSwaped, testNe)

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
  Parameter p1(new CType(CTYPE_VOID), "v1");
  Parameter p2(new CType(CTYPE_VOID), "v2");

  //Even though name is different parameters are the same
  typeEq(p1, p2);
  typeEq(static_cast<Declarator&>(p1), static_cast<Declarator&>(p2));
}

TEST(equality, ParameterPointerSameParam)
{
  Parameter p1(new Pointer(new CType(CTYPE_VOID)), "v1");
  Parameter p2(new Pointer(new CType(CTYPE_VOID)), "v2");

  //Even though name is different parameters are the same
  typeEq(p1, p2);
  typeEq(static_cast<Declarator&>(p1), static_cast<Declarator&>(p2));
}

TEST(equality, ParameterConstSameParam)
{
  Parameter p1 { new ConstQualifiedType(new CType(CTYPE_VOID)), "v1" };
  Parameter p2 { new ConstQualifiedType(new CType(CTYPE_VOID)), "v2" };

  //Even though name is different parameters are the same
  typeEq(p1, p2);
  typeEq(static_cast<Declarator&>(p1), static_cast<Declarator&>(p2));
}

TEST(equality, ParameterDeclareStringSameParam)
{
  Parameter p1(new CType(CTYPE_VOID), "v1");
  Parameter p2(new CType(CTYPE_VOID), "v2");
  p1.setDeclareString(p1.getType()->getFullDeclarationName());
  p2.setDeclareString(p2.getType()->getFullDeclarationName());

  //Even though name is different parameters are the same
  typeEq(p1, p2);
  typeEq(static_cast<Declarator&>(p1), static_cast<Declarator&>(p2));
}

TEST(equality, ParameterDifferentParam)
{
  Parameter p1(new CType(CTYPE_INT), "p1");
  Parameter p2(new CType(CTYPE_VOID), "p1");

  typeNe(p1, p2);
  typeNe(static_cast<Declarator&>(p1), static_cast<Declarator&>(p2));
}

TEST(equality, ParameterPointerDifferentParam)
{
  Parameter p1(new Pointer(new CType(CTYPE_INT)), "p1");
  Parameter p2(new Pointer(new CType(CTYPE_VOID)), "p1");

  typeNe(p1, p2);
  typeNe(static_cast<Declarator&>(p1), static_cast<Declarator&>(p2));

  Parameter p3(new Pointer(new CType(CTYPE_INT)), "p1");
  Parameter p4(new CType(CTYPE_INT), "p1");

  typeNe(p3, p4);
  typeNe(static_cast<Declarator&>(p3), static_cast<Declarator&>(p4));
}

TEST(equality, ParameterConstDifferentParam)
{
  Parameter p1 { new ConstQualifiedType(new CType(CTYPE_INT)), "p1" };
  Parameter p2 { new ConstQualifiedType(new CType(CTYPE_VOID)), "p1" };

  typeNe(p1, p2);
  typeNe(static_cast<Declarator&>(p1), static_cast<Declarator&>(p2));

  Parameter p3 { new ConstQualifiedType(new CType(CTYPE_INT)), "p1" };
  Parameter p4 { new CType(CTYPE_INT), "p1" };

  typeNe(p3, p4);
  typeNe(static_cast<Declarator&>(p3), static_cast<Declarator&>(p4));
}

TEST(equality, ParameterDeclareStringDifferentParam)
{
  Parameter p1(new CType(CTYPE_INT), "p1");
  Parameter p2(new CType(CTYPE_INT), "p1");
  p1.setDeclareString("fromDefine");

  typeNe(p1, p2);
  typeNe(static_cast<Declarator&>(p1), static_cast<Declarator&>(p2));

  Parameter p3(new CType(CTYPE_INT), "p1");
  Parameter p4(new CType(CTYPE_INT), "p1");
  p3.setDeclareString(p3.getType()->getFullDeclarationName());
  p4.setDeclareString("FromDefine");

  typeNe(p3, p4);
  typeNe(static_cast<Declarator&>(p3), static_cast<Declarator&>(p4));
}

TEST(equality, ReturnValueSame)
{
  ReturnValue rv1(new CType(CTYPE_INT));
  ReturnValue rv2(new CType(CTYPE_INT));

  typeEq(rv1, rv2);
  typeEq(static_cast<Declarator&>(rv1), static_cast<Declarator&>(rv2));
}

TEST(equality, ReturnValuePointerSame)
{
  ReturnValue rv1(new Pointer(new CType(CTYPE_INT)));
  ReturnValue rv2(new Pointer(new CType(CTYPE_INT)));

  typeEq(rv1, rv2);
  typeEq(static_cast<Declarator&>(rv1), static_cast<Declarator&>(rv2));
}

TEST(equality, ReturnValueConstSame)
{
  ReturnValue rv1 { new ConstQualifiedType(new CType(CTYPE_INT)) };
  ReturnValue rv2 { new ConstQualifiedType(new CType(CTYPE_INT)) };

  typeEq(rv1, rv2);
  typeEq(static_cast<Declarator&>(rv1), static_cast<Declarator&>(rv2));
}

TEST(equality, ReturnValueDeclareStringSame)
{
  ReturnValue rv1(new CType(CTYPE_INT));
  ReturnValue rv2(new CType(CTYPE_INT));
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
  ReturnValue rv2 = ReturnValue { new ConstQualifiedType(new CType(CTYPE_INT)) };

  typeNe(rv1, rv2);
  typeNe(static_cast<Declarator&>(rv1), static_cast<Declarator&>(rv2));

  ReturnValue rv3 = ReturnValue { new ConstQualifiedType(new CType(CTYPE_INT)) };
  ReturnValue rv4 = ReturnValue { new CType(CTYPE_INT) };

  typeNe(rv3, rv4);
  typeNe(static_cast<Declarator&>(rv3), static_cast<Declarator&>(rv4));
}

TEST(equality, ReturnValueDeclareStringDifferent)
{
  ReturnValue rv1(new CType(CTYPE_INT));
  ReturnValue rv2(new CType(CTYPE_INT));
  rv1.setDeclareString("FromDefine");

  typeNe(rv1, rv2);
  typeNe(static_cast<Declarator&>(rv1), static_cast<Declarator&>(rv2));

  ReturnValue rv3(new CType(CTYPE_INT));
  ReturnValue rv4(new CType(CTYPE_INT));
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
  ComposableField f3(new StructType("s", ComposableFieldItf::Vector({new ComposableField(CTYPE_INT, "c"), new ComposableField(CTYPE_INT, "d")}), isEmbeddedInOtherType), "e");
  ComposableField f4(new StructType("s", ComposableFieldItf::Vector({new ComposableField(CTYPE_INT, "c"), new ComposableField(CTYPE_INT, "d")}), isEmbeddedInOtherType), "e");

  typeEq(f3, f4);
  typeEq(static_cast<Declarator&>(f3), static_cast<Declarator&>(f4));
}

TEST(equality, StructFieldPointerSame)
{
  ComposableField f1( new Pointer(new CType(CTYPE_INT)), "a");
  ComposableField f2(new Pointer(new CType(CTYPE_INT)), "a");

  typeEq(f1, f2);
  typeEq(static_cast<Declarator&>(f1), static_cast<Declarator&>(f2));

  bool isEmbeddedInOtherType = false;
  ComposableField f3(new StructType("s", ComposableFieldItf::Vector({new ComposableField(CTYPE_INT, "c"), new ComposableField(new Pointer(new CType(CTYPE_INT)), "d")}), isEmbeddedInOtherType), "e");
  ComposableField f4(new StructType("s", ComposableFieldItf::Vector({new ComposableField(CTYPE_INT, "c"), new ComposableField(new Pointer(new CType(CTYPE_INT)), "d")}), isEmbeddedInOtherType), "e");

  typeEq(f3, f4);
  typeEq(static_cast<Declarator&>(f3), static_cast<Declarator&>(f4));

  dynamic_cast<ComposableField&>(f3.getType()->getContainedFields()[1]).setArraySize(10);
  typeNe(f3, f4);
  typeNe(static_cast<Declarator&>(f3), static_cast<Declarator&>(f4));
  dynamic_cast<ComposableField&>(f4.getType()->getContainedFields()[1]).setArraySize(10);
  typeEq(f3, f4);
  typeEq(static_cast<Declarator&>(f3), static_cast<Declarator&>(f4));
}

TEST(equality, StructFieldConstSame)
{
  ComposableField f1 { new ConstQualifiedType(new CType(CTYPE_INT)), "a" };
  ComposableField f2 { new ConstQualifiedType(new CType(CTYPE_INT)), "a" };

  typeEq(f1, f2);
  typeEq(static_cast<Declarator&>(f1), static_cast<Declarator&>(f2));
}

TEST(equality, StructFieldDeclStringSame)
{
  ComposableField f1(new CType(CTYPE_INT), "a");
  ComposableField f2(new CType(CTYPE_INT), "a");
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
  ComposableField f3(new StructType("s", ComposableFieldItf::Vector({new ComposableField(CTYPE_INT, "c"), new ComposableField(CTYPE_INT, "d")}), isEmbeddedInOtherType), "e");
  ComposableField f4(new StructType("s", ComposableFieldItf::Vector({new ComposableField(CTYPE_INT, "c"), new ComposableField(CTYPE_DOUBLE, "d")}), isEmbeddedInOtherType), "e");

  typeNe(f3, f4);
  typeNe(static_cast<Declarator&>(f3), static_cast<Declarator&>(f4));
}

TEST(equality, StructFieldConstDifferent)
{
  ComposableField f1 { new CType(CTYPE_INT), "a" };
  ComposableField f2 { new ConstQualifiedType(new CType(CTYPE_INT)), "a" };

  typeNe(f1, f2);
  typeNe(static_cast<Declarator&>(f1), static_cast<Declarator&>(f2));
}

TEST(equality, StructFieldDeclStringDifferent)
{
  ComposableField f1(new CType(CTYPE_INT), "a");
  ComposableField f2(new CType(CTYPE_INT), "a");
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
    T s3("s", ComposableFieldItf::Vector({new ComposableField(CTYPE_CHAR, "f")}), isEmbeddedInOtherType);
    T s4("s", ComposableFieldItf::Vector({new ComposableField(CTYPE_CHAR, "f")}), isEmbeddedInOtherType);

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
  StructType s1("s", ComposableFieldItf::Vector({}), isEmbeddedInOtherType);
  StructType s2("s", ComposableFieldItf::Vector({}), isEmbeddedInOtherType);

  runComposableTypeSame(s1, s2);
}

TEST(equality, UnionTypeSame)
{
  bool isEmbeddedInOtherType = true;
  UnionType u1("s", ComposableFieldItf::Vector({}), isEmbeddedInOtherType);
  UnionType u2("s", ComposableFieldItf::Vector({}), isEmbeddedInOtherType);

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
  StructType s1("s", ComposableFieldItf::Vector({}), isEmbeddedInOtherType);
  StructType s2("s", ComposableFieldItf::Vector({new ComposableField(CTYPE_CHAR, "f")}), isEmbeddedInOtherType);

  runComposableTypeDifferent(s1, s2);
}

TEST(equality, UnionTypeDifferent)
{
  bool isEmbeddedInOtherType = false;
  UnionType u1("s", ComposableFieldItf::Vector({}), isEmbeddedInOtherType);
  UnionType u2("s", ComposableFieldItf::Vector({new ComposableField(CTYPE_CHAR, "f")}), isEmbeddedInOtherType);

  runComposableTypeDifferent(u1, u2);
}

TEST(equality, StructTypedDefEqual)
{
  bool isEmbeddedInOtherType = false;

  TypedefType s1 { "typeS1", new StructType("s1", isEmbeddedInOtherType) };
  TypedefType s2 { "typeS1", new StructType("s1", isEmbeddedInOtherType) };

  runComposableTypeSame(s1, s2);
}

TEST(equality, UnionTypedDefEqual)
{
  bool isEmbeddedInOtherType = false;

  TypedefType u1 { "typeU1", new UnionType("u1", isEmbeddedInOtherType) };
  TypedefType u2 { "typeU1", new UnionType("u1", isEmbeddedInOtherType) };

  runComposableTypeSame(u1, u2);
}

TEST(equality, StructTypedDefDifferent)
{
  bool isEmbeddedInOtherType = false;

  StructType s1("s1", isEmbeddedInOtherType);
  TypedefType s2 { "s1", new StructType("", isEmbeddedInOtherType) };

  runComposableTypeDifferent(s1, s2);
}

TEST(equality, UnionTypedDefDifferent)
{
  bool isEmbeddedInOtherType = false;

  UnionType u1("u1", isEmbeddedInOtherType);
  TypedefType u2 { "u1", new UnionType("", isEmbeddedInOtherType) };

  runComposableTypeDifferent(u1, u2);
}

TEST(equality, StructEmbeddedInOtherTypeDifferent)
{
  bool isEmbeddedInOtherType = false;

  TypedefType s1 { "typeS1", new StructType("s1", isEmbeddedInOtherType) };
  TypedefType s2 { "typeS1", new StructType("s1", !isEmbeddedInOtherType) };

  runComposableTypeDifferent(s1, s2);
}

TEST(equality, UnionEmbeddedInOtherTypeDifferent)
{
  bool isEmbeddedInOtherType = false;

  TypedefType u1 { "typeU1", new UnionType("u1", isEmbeddedInOtherType) };
  TypedefType u2 { "typeU1", new UnionType("u1", !isEmbeddedInOtherType) };

  runComposableTypeDifferent(u1, u2);
}

TEST(equality, AnonymousTypedefDifferentWithSameField)
{
  bool isEmbeddedInOtherType = false;

  TypedefType tst1 { "TypedDefAnonymousStruct", new StructType("", isEmbeddedInOtherType) };
  StructType *st1 = dynamic_cast<StructType*>(tst1.getTypee());
  st1->addField(new ComposableField(CTYPE_INT, "a"));

  TypedefType tst2 { "TypedDefAnonymousStruct2", new StructType("", isEmbeddedInOtherType) };
  StructType *st2 = dynamic_cast<StructType*>(tst2.getTypee());
  st2->addField(new ComposableField(CTYPE_INT, "a"));

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

TEST(equality, AutoCleanVectorSame)
{
  AutoCleanVectorPtr<int> v1({new int(1), new int(2)});
  AutoCleanVectorPtr<int> v2({new int(1), new int(2)});

  typeEq(v1, v2);
}

TEST(equality, AutoCleanVectorDifferent)
{
  AutoCleanVectorPtr<int> v1({new int(1), new int(2)});
  AutoCleanVectorPtr<int> v2({new int(2), new int(1)});

  typeNe(v1, v2);
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
  TypedefType t1("t1", new CType(CTYPE_INT));
  TypedefType t2("t1", new CType(CTYPE_INT));
  TypedefType t3("t2", new CType(CTYPE_INT));

  typeEq(t1, t2);
  typeNe(t1, t3);

  TypeItf &tt1 = t1;
  TypeItf &tt2 = t2;
  TypeItf &tt3 = t3;

  typeEq(tt1, tt2);
  typeNe(tt1, tt3);
}
