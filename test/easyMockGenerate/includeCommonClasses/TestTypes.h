#ifndef TESTTYPES_H
#define TESTTYPES_H

#include <gtest/gtest.h>

#include <VoidFunVoidFactory.h>
#include <CharFunCharFactory.h>
#include <IntFunVoidFactory.h>
#include <DoubleFunDoubleFactory.h>
#include <FloatFunFloatFactory.h>
#include <IntFunIntIntFactory.h>
#include <LongDoubleFunLongDoubleFactory.h>
#include <LongFunLongFactory.h>
#include <LongLongFunLongLongFactory.h>
#include <ShortFunShortFactory.h>
#include <UnsCharFunUnsCharFactory.h>
#include <UnsIntFunUnsIntIntFactory.h>
#include <UnsIntFunVoidFactory.h>
#include <UnsLongFunUnsLongFactory.h>
#include <UnsLongLongFunUnsLongLongFactory.h>
#include <UnsShortFunUnsShortFactory.h>
#include <StructFunStructFactory.h>
#include <PtrFunPtrGenericFactory.h>
#include <VoidFunStructPtrFactory.h>
#include <IntFunStructPtrIntCharPtrFactory.h>
#include <StructRecursiveMemberPtrTypeFactory.h>
#include <VoidFunStructWithArrayFactory.h>
#include <VoidFunIntArrayFactory.h>
#include <StructSubStructRecursiveTypeFactory.h>
#include <StructTypedDefFunStructTypedDefFactory.h>
#include <StructAnonymousTypedDefFunStructAnonymousTypedDefFactory.hpp>
#include <UnionFunUnionFactory.h>
#include <UnionTypedDefFunUnionTypedDefFactory.hpp>
#include <UnionAnonymousTypedDefFunUnionAnonymousTypedDefFactory.h>
#include <StructWithUnionFunStructWithUnionFactory.h>
#include <VoidFunStructWithEmbeddedStructFactory.h>
#include <VoidFunStructWithEmbeddedAnonymousStructFactory.h>
#include <VoidFunUnionWithEmbeddedUnionFactory.h>
#include <VoidFunUnionWithEmbeddedAnonymousUnionFactory.h>
#include <VoidFunStructWithAnonymousStructFieldFactory.h>
#include <VoidFunUnionWithAnonymousUnionFieldFactory.h>
#include <VoidFunStructWithFirstAnonymousStructFieldFactory.h>
#include <VoidFunUnionWithFirstAnonymousUnionFieldFactory.h>
#include <ConstIntFunConstIntFactory.h>
#include <VoidFunStructWithTypedefStructFactory.h>
#include <VoidFunStructRecusNonTypedefFactory.h>
#include <StructFileFromStdioFactory.h>
#include <CompileTwoFunctionsFactory.h>
#include <VariadicFunctionsFactory.h>
#include <MultipleDefinitionsFactory.h>
#include <FunctionVaArgsFactory.h>
#include <VoidFunParamNoNameFactory.h>
#include <VoidOutFactory.h>
#include <InlineVoidFactory.h>

/*
 * Note lcarlier:
 * Google test supports maximum 50 different classes when running class templated
 * UT. I have UT that have more than 50 classes so I extend Google test
 * here.
 * Note that I didn't understand how this works. I just copied/pasted the
 * needed part Google of the header file and extended the parameters.
 * I had to create a new type (BigTypes) because it is not possible to
 * redefine the initial Google type "::testing::internal::Types"
 * with more than 50 template parameters.
 * If you have to increase that number again, please extend BigTypes.
 * See also the inline comments for hints on what to do
 */
namespace testing
{
  namespace internal
  {
    template <typename T1, typename T2, typename T3, typename T4, typename T5,
        typename T6, typename T7, typename T8, typename T9, typename T10,
        typename T11, typename T12, typename T13, typename T14, typename T15,
        typename T16, typename T17, typename T18, typename T19, typename T20,
        typename T21, typename T22, typename T23, typename T24, typename T25,
        typename T26, typename T27, typename T28, typename T29, typename T30,
        typename T31, typename T32, typename T33, typename T34, typename T35,
        typename T36, typename T37, typename T38, typename T39, typename T40,
        typename T41, typename T42, typename T43, typename T44, typename T45,
        typename T46, typename T47, typename T48, typename T49, typename T50,
        typename T51>
    struct Types51 {
      typedef T1 Head;
      //Types50 takes 50 arguments from T2 to T51
      typedef Types50<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
          T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
          T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43,
          T44, T45, T46, T47, T48, T49, T50, T51> Tail;
    };

    template <typename T1, typename T2, typename T3, typename T4, typename T5,
        typename T6, typename T7, typename T8, typename T9, typename T10,
        typename T11, typename T12, typename T13, typename T14, typename T15,
        typename T16, typename T17, typename T18, typename T19, typename T20,
        typename T21, typename T22, typename T23, typename T24, typename T25,
        typename T26, typename T27, typename T28, typename T29, typename T30,
        typename T31, typename T32, typename T33, typename T34, typename T35,
        typename T36, typename T37, typename T38, typename T39, typename T40,
        typename T41, typename T42, typename T43, typename T44, typename T45,
        typename T46, typename T47, typename T48, typename T49, typename T50,
        typename T51, typename T52>
    struct Types52 {
      typedef T1 Head;
      //Types51 takes 51 arguments from T2 to T52
      typedef Types51<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
          T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
          T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43,
          T44, T45, T46, T47, T48, T49, T50, T51, T52> Tail;
    };

    template <typename T1, typename T2, typename T3, typename T4, typename T5,
        typename T6, typename T7, typename T8, typename T9, typename T10,
        typename T11, typename T12, typename T13, typename T14, typename T15,
        typename T16, typename T17, typename T18, typename T19, typename T20,
        typename T21, typename T22, typename T23, typename T24, typename T25,
        typename T26, typename T27, typename T28, typename T29, typename T30,
        typename T31, typename T32, typename T33, typename T34, typename T35,
        typename T36, typename T37, typename T38, typename T39, typename T40,
        typename T41, typename T42, typename T43, typename T44, typename T45,
        typename T46, typename T47, typename T48, typename T49, typename T50,
        typename T51, typename T52, typename T53>
    struct Types53 {
      typedef T1 Head;
      //Types52 takes 52 arguments from T2 to T53
      typedef Types52<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
          T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
          T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43,
          T44, T45, T46, T47, T48, T49, T50, T51, T52, T53> Tail;
    };

    template <typename T1, typename T2, typename T3, typename T4, typename T5,
        typename T6, typename T7, typename T8, typename T9, typename T10,
        typename T11, typename T12, typename T13, typename T14, typename T15,
        typename T16, typename T17, typename T18, typename T19, typename T20,
        typename T21, typename T22, typename T23, typename T24, typename T25,
        typename T26, typename T27, typename T28, typename T29, typename T30,
        typename T31, typename T32, typename T33, typename T34, typename T35,
        typename T36, typename T37, typename T38, typename T39, typename T40,
        typename T41, typename T42, typename T43, typename T44, typename T45,
        typename T46, typename T47, typename T48, typename T49, typename T50,
        typename T51, typename T52, typename T53, typename T54>
    struct Types54 {
      typedef T1 Head;
      //Types53 takes 53 arguments from T2 to T54
      typedef Types53<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
          T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
          T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43,
          T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54> Tail;
    };

    template <typename T1, typename T2, typename T3, typename T4, typename T5,
        typename T6, typename T7, typename T8, typename T9, typename T10,
        typename T11, typename T12, typename T13, typename T14, typename T15,
        typename T16, typename T17, typename T18, typename T19, typename T20,
        typename T21, typename T22, typename T23, typename T24, typename T25,
        typename T26, typename T27, typename T28, typename T29, typename T30,
        typename T31, typename T32, typename T33, typename T34, typename T35,
        typename T36, typename T37, typename T38, typename T39, typename T40,
        typename T41, typename T42, typename T43, typename T44, typename T45,
        typename T46, typename T47, typename T48, typename T49, typename T50,
        typename T51, typename T52, typename T53, typename T54, typename T55>
    struct Types55 {
      typedef T1 Head;
      //Types54 takes 54 arguments from T2 to T55
      typedef Types54<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
          T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
          T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43,
          T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54, T55> Tail;
    };

    template <typename T1, typename T2, typename T3, typename T4, typename T5,
        typename T6, typename T7, typename T8, typename T9, typename T10,
        typename T11, typename T12, typename T13, typename T14, typename T15,
        typename T16, typename T17, typename T18, typename T19, typename T20,
        typename T21, typename T22, typename T23, typename T24, typename T25,
        typename T26, typename T27, typename T28, typename T29, typename T30,
        typename T31, typename T32, typename T33, typename T34, typename T35,
        typename T36, typename T37, typename T38, typename T39, typename T40,
        typename T41, typename T42, typename T43, typename T44, typename T45,
        typename T46, typename T47, typename T48, typename T49, typename T50,
        typename T51, typename T52, typename T53, typename T54, typename T55,
        typename T56>
    struct Types56 {
      typedef T1 Head;
      //Types55 takes 55 arguments from T2 to T56
      typedef Types55<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
          T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
          T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43,
          T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54, T55, T56> Tail;
    };

    template <typename T1, typename T2, typename T3, typename T4, typename T5,
        typename T6, typename T7, typename T8, typename T9, typename T10,
        typename T11, typename T12, typename T13, typename T14, typename T15,
        typename T16, typename T17, typename T18, typename T19, typename T20,
        typename T21, typename T22, typename T23, typename T24, typename T25,
        typename T26, typename T27, typename T28, typename T29, typename T30,
        typename T31, typename T32, typename T33, typename T34, typename T35,
        typename T36, typename T37, typename T38, typename T39, typename T40,
        typename T41, typename T42, typename T43, typename T44, typename T45,
        typename T46, typename T47, typename T48, typename T49, typename T50,
        typename T51, typename T52, typename T53, typename T54, typename T55,
        typename T56, typename T57>
    struct Types57 {
      typedef T1 Head;
      //Types56 takes 56 arguments from T2 to T57
      typedef Types56<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
          T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
          T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43,
          T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54, T55, T56, T57> Tail;
    };

    template <typename T1, typename T2, typename T3, typename T4, typename T5,
        typename T6, typename T7, typename T8, typename T9, typename T10,
        typename T11, typename T12, typename T13, typename T14, typename T15,
        typename T16, typename T17, typename T18, typename T19, typename T20,
        typename T21, typename T22, typename T23, typename T24, typename T25,
        typename T26, typename T27, typename T28, typename T29, typename T30,
        typename T31, typename T32, typename T33, typename T34, typename T35,
        typename T36, typename T37, typename T38, typename T39, typename T40,
        typename T41, typename T42, typename T43, typename T44, typename T45,
        typename T46, typename T47, typename T48, typename T49, typename T50,
        typename T51, typename T52, typename T53, typename T54, typename T55,
        typename T56, typename T57, typename T58>
    struct Types58 {
      typedef T1 Head;
      //Types57 takes 57 arguments from T2 to T58
      typedef Types57<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
          T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
          T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43,
          T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54, T55, T56, T57,
          T58> Tail;
    };

    template <typename T1, typename T2, typename T3, typename T4, typename T5,
        typename T6, typename T7, typename T8, typename T9, typename T10,
        typename T11, typename T12, typename T13, typename T14, typename T15,
        typename T16, typename T17, typename T18, typename T19, typename T20,
        typename T21, typename T22, typename T23, typename T24, typename T25,
        typename T26, typename T27, typename T28, typename T29, typename T30,
        typename T31, typename T32, typename T33, typename T34, typename T35,
        typename T36, typename T37, typename T38, typename T39, typename T40,
        typename T41, typename T42, typename T43, typename T44, typename T45,
        typename T46, typename T47, typename T48, typename T49, typename T50,
        typename T51, typename T52, typename T53, typename T54, typename T55,
        typename T56, typename T57, typename T58, typename T59>
    struct Types59 {
      typedef T1 Head;
      //Types58 takes 58 arguments from T2 to T59
      typedef Types58<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
          T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
          T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43,
          T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54, T55, T56, T57,
          T58, T59> Tail;
    };

    template <typename T1, typename T2, typename T3, typename T4, typename T5,
        typename T6, typename T7, typename T8, typename T9, typename T10,
        typename T11, typename T12, typename T13, typename T14, typename T15,
        typename T16, typename T17, typename T18, typename T19, typename T20,
        typename T21, typename T22, typename T23, typename T24, typename T25,
        typename T26, typename T27, typename T28, typename T29, typename T30,
        typename T31, typename T32, typename T33, typename T34, typename T35,
        typename T36, typename T37, typename T38, typename T39, typename T40,
        typename T41, typename T42, typename T43, typename T44, typename T45,
        typename T46, typename T47, typename T48, typename T49, typename T50,
        typename T51, typename T52, typename T53, typename T54, typename T55,
        typename T56, typename T57, typename T58, typename T59, typename T60>
    struct Types60 {
      typedef T1 Head;
      //Types59 takes 59 arguments from T2 to T60
      typedef Types59<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
          T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
          T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43,
          T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54, T55, T56, T57,
          T58, T59, T60> Tail;
    };

    template <typename T1, typename T2, typename T3, typename T4, typename T5,
        typename T6, typename T7, typename T8, typename T9, typename T10,
        typename T11, typename T12, typename T13, typename T14, typename T15,
        typename T16, typename T17, typename T18, typename T19, typename T20,
        typename T21, typename T22, typename T23, typename T24, typename T25,
        typename T26, typename T27, typename T28, typename T29, typename T30,
        typename T31, typename T32, typename T33, typename T34, typename T35,
        typename T36, typename T37, typename T38, typename T39, typename T40,
        typename T41, typename T42, typename T43, typename T44, typename T45,
        typename T46, typename T47, typename T48, typename T49, typename T50,
        typename T51, typename T52, typename T53, typename T54, typename T55,
        typename T56, typename T57, typename T58, typename T59, typename T60,
        typename T61>
    struct Types61 {
      typedef T1 Head;
      //Types60 takes 60 arguments from T2 to T61
      typedef Types60<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
          T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
          T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43,
          T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54, T55, T56, T57,
          T58, T59, T60, T61> Tail;
    };

    template <typename T1, typename T2, typename T3, typename T4, typename T5,
        typename T6, typename T7, typename T8, typename T9, typename T10,
        typename T11, typename T12, typename T13, typename T14, typename T15,
        typename T16, typename T17, typename T18, typename T19, typename T20,
        typename T21, typename T22, typename T23, typename T24, typename T25,
        typename T26, typename T27, typename T28, typename T29, typename T30,
        typename T31, typename T32, typename T33, typename T34, typename T35,
        typename T36, typename T37, typename T38, typename T39, typename T40,
        typename T41, typename T42, typename T43, typename T44, typename T45,
        typename T46, typename T47, typename T48, typename T49, typename T50,
        typename T51, typename T52, typename T53, typename T54, typename T55,
        typename T56, typename T57, typename T58, typename T59, typename T60,
        typename T61, typename T62>
    struct Types62 {
      typedef T1 Head;
      //Types61 takes 61 arguments from T2 to T62
      typedef Types61<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
          T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
          T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43,
          T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54, T55, T56, T57,
          T58, T59, T60, T61, T62> Tail;
    };

    /*
     * In case of a new template parameter is needed:
     * Copy paste this struct with a version with 1 template parameter more.
     * Increase by one any integer you see in type names.
     */
    template <typename T1, typename T2, typename T3, typename T4, typename T5,
        typename T6, typename T7, typename T8, typename T9, typename T10,
        typename T11, typename T12, typename T13, typename T14, typename T15,
        typename T16, typename T17, typename T18, typename T19, typename T20,
        typename T21, typename T22, typename T23, typename T24, typename T25,
        typename T26, typename T27, typename T28, typename T29, typename T30,
        typename T31, typename T32, typename T33, typename T34, typename T35,
        typename T36, typename T37, typename T38, typename T39, typename T40,
        typename T41, typename T42, typename T43, typename T44, typename T45,
        typename T46, typename T47, typename T48, typename T49, typename T50,
        typename T51, typename T52, typename T53, typename T54, typename T55,
        typename T56, typename T57, typename T58, typename T59, typename T60,
        typename T61, typename T62, typename T63>
    struct Types63 {
      typedef T1 Head;
      //Types62 takes 62 arguments from T2 to T63
      typedef Types62<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
          T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
          T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43,
          T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54, T55, T56, T57,
          T58, T59, T60, T61, T62, T63> Tail;
    };
  } //namespace internal

  /*
   * In case of a new template parameter is needed:
   * This is the struct to be extended. I.E: add one template parameter.
   * Use Types(x+1) iso Types(x)
   */
  template <typename T1 = internal::None, typename T2 = internal::None,
      typename T3 = internal::None, typename T4 = internal::None,
      typename T5 = internal::None, typename T6 = internal::None,
      typename T7 = internal::None, typename T8 = internal::None,
      typename T9 = internal::None, typename T10 = internal::None,
      typename T11 = internal::None, typename T12 = internal::None,
      typename T13 = internal::None, typename T14 = internal::None,
      typename T15 = internal::None, typename T16 = internal::None,
      typename T17 = internal::None, typename T18 = internal::None,
      typename T19 = internal::None, typename T20 = internal::None,
      typename T21 = internal::None, typename T22 = internal::None,
      typename T23 = internal::None, typename T24 = internal::None,
      typename T25 = internal::None, typename T26 = internal::None,
      typename T27 = internal::None, typename T28 = internal::None,
      typename T29 = internal::None, typename T30 = internal::None,
      typename T31 = internal::None, typename T32 = internal::None,
      typename T33 = internal::None, typename T34 = internal::None,
      typename T35 = internal::None, typename T36 = internal::None,
      typename T37 = internal::None, typename T38 = internal::None,
      typename T39 = internal::None, typename T40 = internal::None,
      typename T41 = internal::None, typename T42 = internal::None,
      typename T43 = internal::None, typename T44 = internal::None,
      typename T45 = internal::None, typename T46 = internal::None,
      typename T47 = internal::None, typename T48 = internal::None,
      typename T49 = internal::None, typename T50 = internal::None,
      typename T51 = internal::None, typename T52 = internal::None,
      typename T53 = internal::None, typename T54 = internal::None,
      typename T55 = internal::None, typename T56 = internal::None,
      typename T57 = internal::None, typename T58 = internal::None,
      typename T59 = internal::None, typename T60 = internal::None,
      typename T61 = internal::None, typename T62 = internal::None,
      typename T63 = internal::None>
  struct BigTypes {
    typedef internal::Types63<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
        T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
        T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
        T41, T42, T43, T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54,
        T55, T56, T57, T58, T59, T60, T61, T62, T63> type;
  };

  template <typename T1, typename T2, typename T3, typename T4, typename T5,
      typename T6, typename T7, typename T8, typename T9, typename T10,
      typename T11, typename T12, typename T13, typename T14, typename T15,
      typename T16, typename T17, typename T18, typename T19, typename T20,
      typename T21, typename T22, typename T23, typename T24, typename T25,
      typename T26, typename T27, typename T28, typename T29, typename T30,
      typename T31, typename T32, typename T33, typename T34, typename T35,
      typename T36, typename T37, typename T38, typename T39, typename T40,
      typename T41, typename T42, typename T43, typename T44, typename T45,
      typename T46, typename T47, typename T48, typename T49, typename T50>
  struct BigTypes<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30,
      T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45,
      T46, T47, T48, T49, T50, internal::None> {
    typedef internal::Types50<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
        T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
        T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
        T41, T42, T43, T44, T45, T46, T47, T48, T49, T50> type;
  };

  template <typename T1, typename T2, typename T3, typename T4, typename T5,
      typename T6, typename T7, typename T8, typename T9, typename T10,
      typename T11, typename T12, typename T13, typename T14, typename T15,
      typename T16, typename T17, typename T18, typename T19, typename T20,
      typename T21, typename T22, typename T23, typename T24, typename T25,
      typename T26, typename T27, typename T28, typename T29, typename T30,
      typename T31, typename T32, typename T33, typename T34, typename T35,
      typename T36, typename T37, typename T38, typename T39, typename T40,
      typename T41, typename T42, typename T43, typename T44, typename T45,
      typename T46, typename T47, typename T48, typename T49, typename T50,
      typename T51>
  struct BigTypes<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30,
      T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45,
      T46, T47, T48, T49, T50, T51, internal::None> {
    typedef internal::Types51<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
        T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
        T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
        T41, T42, T43, T44, T45, T46, T47, T48, T49, T50, T51> type;
  };

  template <typename T1, typename T2, typename T3, typename T4, typename T5,
      typename T6, typename T7, typename T8, typename T9, typename T10,
      typename T11, typename T12, typename T13, typename T14, typename T15,
      typename T16, typename T17, typename T18, typename T19, typename T20,
      typename T21, typename T22, typename T23, typename T24, typename T25,
      typename T26, typename T27, typename T28, typename T29, typename T30,
      typename T31, typename T32, typename T33, typename T34, typename T35,
      typename T36, typename T37, typename T38, typename T39, typename T40,
      typename T41, typename T42, typename T43, typename T44, typename T45,
      typename T46, typename T47, typename T48, typename T49, typename T50,
      typename T51, typename T52>
  struct BigTypes<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30,
      T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45,
      T46, T47, T48, T49, T50, T51, T52, internal::None> {
    typedef internal::Types52<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
        T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
        T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
        T41, T42, T43, T44, T45, T46, T47, T48, T49, T50, T51, T52> type;
  };

  template <typename T1, typename T2, typename T3, typename T4, typename T5,
      typename T6, typename T7, typename T8, typename T9, typename T10,
      typename T11, typename T12, typename T13, typename T14, typename T15,
      typename T16, typename T17, typename T18, typename T19, typename T20,
      typename T21, typename T22, typename T23, typename T24, typename T25,
      typename T26, typename T27, typename T28, typename T29, typename T30,
      typename T31, typename T32, typename T33, typename T34, typename T35,
      typename T36, typename T37, typename T38, typename T39, typename T40,
      typename T41, typename T42, typename T43, typename T44, typename T45,
      typename T46, typename T47, typename T48, typename T49, typename T50,
      typename T51, typename T52, typename T53>
  struct BigTypes<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30,
      T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45,
      T46, T47, T48, T49, T50, T51, T52, T53, internal::None> {
    typedef internal::Types53<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
        T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
        T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
        T41, T42, T43, T44, T45, T46, T47, T48, T49, T50, T51, T52, T53> type;
  };

  template <typename T1, typename T2, typename T3, typename T4, typename T5,
      typename T6, typename T7, typename T8, typename T9, typename T10,
      typename T11, typename T12, typename T13, typename T14, typename T15,
      typename T16, typename T17, typename T18, typename T19, typename T20,
      typename T21, typename T22, typename T23, typename T24, typename T25,
      typename T26, typename T27, typename T28, typename T29, typename T30,
      typename T31, typename T32, typename T33, typename T34, typename T35,
      typename T36, typename T37, typename T38, typename T39, typename T40,
      typename T41, typename T42, typename T43, typename T44, typename T45,
      typename T46, typename T47, typename T48, typename T49, typename T50,
      typename T51, typename T52, typename T53, typename T54>
  struct BigTypes<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30,
      T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45,
      T46, T47, T48, T49, T50, T51, T52, T53, T54, internal::None> {
    typedef internal::Types54<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
        T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
        T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
        T41, T42, T43, T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54> type;
  };

  template <typename T1, typename T2, typename T3, typename T4, typename T5,
      typename T6, typename T7, typename T8, typename T9, typename T10,
      typename T11, typename T12, typename T13, typename T14, typename T15,
      typename T16, typename T17, typename T18, typename T19, typename T20,
      typename T21, typename T22, typename T23, typename T24, typename T25,
      typename T26, typename T27, typename T28, typename T29, typename T30,
      typename T31, typename T32, typename T33, typename T34, typename T35,
      typename T36, typename T37, typename T38, typename T39, typename T40,
      typename T41, typename T42, typename T43, typename T44, typename T45,
      typename T46, typename T47, typename T48, typename T49, typename T50,
      typename T51, typename T52, typename T53, typename T54, typename T55>
  struct BigTypes<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30,
      T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45,
      T46, T47, T48, T49, T50, T51, T52, T53, T54, T55, internal::None> {
    typedef internal::Types55<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
        T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
        T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
        T41, T42, T43, T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54,
        T55> type;
  };

  template <typename T1, typename T2, typename T3, typename T4, typename T5,
      typename T6, typename T7, typename T8, typename T9, typename T10,
      typename T11, typename T12, typename T13, typename T14, typename T15,
      typename T16, typename T17, typename T18, typename T19, typename T20,
      typename T21, typename T22, typename T23, typename T24, typename T25,
      typename T26, typename T27, typename T28, typename T29, typename T30,
      typename T31, typename T32, typename T33, typename T34, typename T35,
      typename T36, typename T37, typename T38, typename T39, typename T40,
      typename T41, typename T42, typename T43, typename T44, typename T45,
      typename T46, typename T47, typename T48, typename T49, typename T50,
      typename T51, typename T52, typename T53, typename T54, typename T55,
      typename T56>
  struct BigTypes<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30,
      T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45,
      T46, T47, T48, T49, T50, T51, T52, T53, T54, T55, T56, internal::None> {
    typedef internal::Types56<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
        T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
        T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
        T41, T42, T43, T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54,
        T55, T56> type;
  };

  template <typename T1, typename T2, typename T3, typename T4, typename T5,
      typename T6, typename T7, typename T8, typename T9, typename T10,
      typename T11, typename T12, typename T13, typename T14, typename T15,
      typename T16, typename T17, typename T18, typename T19, typename T20,
      typename T21, typename T22, typename T23, typename T24, typename T25,
      typename T26, typename T27, typename T28, typename T29, typename T30,
      typename T31, typename T32, typename T33, typename T34, typename T35,
      typename T36, typename T37, typename T38, typename T39, typename T40,
      typename T41, typename T42, typename T43, typename T44, typename T45,
      typename T46, typename T47, typename T48, typename T49, typename T50,
      typename T51, typename T52, typename T53, typename T54, typename T55,
      typename T56, typename T57>
  struct BigTypes<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30,
      T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45,
      T46, T47, T48, T49, T50, T51, T52, T53, T54, T55, T56, T57, internal::None> {
    typedef internal::Types57<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
        T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
        T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
        T41, T42, T43, T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54,
        T55, T56, T57> type;
  };

  template <typename T1, typename T2, typename T3, typename T4, typename T5,
      typename T6, typename T7, typename T8, typename T9, typename T10,
      typename T11, typename T12, typename T13, typename T14, typename T15,
      typename T16, typename T17, typename T18, typename T19, typename T20,
      typename T21, typename T22, typename T23, typename T24, typename T25,
      typename T26, typename T27, typename T28, typename T29, typename T30,
      typename T31, typename T32, typename T33, typename T34, typename T35,
      typename T36, typename T37, typename T38, typename T39, typename T40,
      typename T41, typename T42, typename T43, typename T44, typename T45,
      typename T46, typename T47, typename T48, typename T49, typename T50,
      typename T51, typename T52, typename T53, typename T54, typename T55,
      typename T56, typename T57, typename T58>
  struct BigTypes<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30,
      T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45,
      T46, T47, T48, T49, T50, T51, T52, T53, T54, T55, T56, T57, T58, internal::None> {
    typedef internal::Types58<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
        T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
        T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
        T41, T42, T43, T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54,
        T55, T56, T57, T58> type;
  };

  template <typename T1, typename T2, typename T3, typename T4, typename T5,
      typename T6, typename T7, typename T8, typename T9, typename T10,
      typename T11, typename T12, typename T13, typename T14, typename T15,
      typename T16, typename T17, typename T18, typename T19, typename T20,
      typename T21, typename T22, typename T23, typename T24, typename T25,
      typename T26, typename T27, typename T28, typename T29, typename T30,
      typename T31, typename T32, typename T33, typename T34, typename T35,
      typename T36, typename T37, typename T38, typename T39, typename T40,
      typename T41, typename T42, typename T43, typename T44, typename T45,
      typename T46, typename T47, typename T48, typename T49, typename T50,
      typename T51, typename T52, typename T53, typename T54, typename T55,
      typename T56, typename T57, typename T58, typename T59>
  struct BigTypes<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30,
      T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45,
      T46, T47, T48, T49, T50, T51, T52, T53, T54, T55, T56, T57, T58, T59, internal::None> {
    typedef internal::Types59<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
        T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
        T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
        T41, T42, T43, T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54,
        T55, T56, T57, T58, T59> type;
  };

  template <typename T1, typename T2, typename T3, typename T4, typename T5,
      typename T6, typename T7, typename T8, typename T9, typename T10,
      typename T11, typename T12, typename T13, typename T14, typename T15,
      typename T16, typename T17, typename T18, typename T19, typename T20,
      typename T21, typename T22, typename T23, typename T24, typename T25,
      typename T26, typename T27, typename T28, typename T29, typename T30,
      typename T31, typename T32, typename T33, typename T34, typename T35,
      typename T36, typename T37, typename T38, typename T39, typename T40,
      typename T41, typename T42, typename T43, typename T44, typename T45,
      typename T46, typename T47, typename T48, typename T49, typename T50,
      typename T51, typename T52, typename T53, typename T54, typename T55,
      typename T56, typename T57, typename T58, typename T59, typename T60>
  struct BigTypes<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30,
      T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45,
      T46, T47, T48, T49, T50, T51, T52, T53, T54, T55, T56, T57, T58, T59, T60, internal::None> {
    typedef internal::Types60<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
        T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
        T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
        T41, T42, T43, T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54,
        T55, T56, T57, T58, T59, T60> type;
  };

  template <typename T1, typename T2, typename T3, typename T4, typename T5,
      typename T6, typename T7, typename T8, typename T9, typename T10,
      typename T11, typename T12, typename T13, typename T14, typename T15,
      typename T16, typename T17, typename T18, typename T19, typename T20,
      typename T21, typename T22, typename T23, typename T24, typename T25,
      typename T26, typename T27, typename T28, typename T29, typename T30,
      typename T31, typename T32, typename T33, typename T34, typename T35,
      typename T36, typename T37, typename T38, typename T39, typename T40,
      typename T41, typename T42, typename T43, typename T44, typename T45,
      typename T46, typename T47, typename T48, typename T49, typename T50,
      typename T51, typename T52, typename T53, typename T54, typename T55,
      typename T56, typename T57, typename T58, typename T59, typename T60,
      typename T61>
  struct BigTypes<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30,
      T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45,
      T46, T47, T48, T49, T50, T51, T52, T53, T54, T55, T56, T57, T58, T59, T60,
      T61, internal::None> {
    typedef internal::Types61<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
        T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
        T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
        T41, T42, T43, T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54,
        T55, T56, T57, T58, T59, T60, T61> type;
  };
  namespace internal
  {
    template <typename T1, typename T2, typename T3, typename T4, typename T5,
        typename T6, typename T7, typename T8, typename T9, typename T10,
        typename T11, typename T12, typename T13, typename T14, typename T15,
        typename T16, typename T17, typename T18, typename T19, typename T20,
        typename T21, typename T22, typename T23, typename T24, typename T25,
        typename T26, typename T27, typename T28, typename T29, typename T30,
        typename T31, typename T32, typename T33, typename T34, typename T35,
        typename T36, typename T37, typename T38, typename T39, typename T40,
        typename T41, typename T42, typename T43, typename T44, typename T45,
        typename T46, typename T47, typename T48, typename T49, typename T50,
        typename T51>
    struct TypeList<BigTypes<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
        T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28,
        T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43,
        T44, T45, T46, T47, T48, T49, T50, T51> > {
      typedef typename BigTypes<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
          T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
          T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
          T41, T42, T43, T44, T45, T46, T47, T48, T49, T50, T51>::type type;
    };

    template <typename T1, typename T2, typename T3, typename T4, typename T5,
        typename T6, typename T7, typename T8, typename T9, typename T10,
        typename T11, typename T12, typename T13, typename T14, typename T15,
        typename T16, typename T17, typename T18, typename T19, typename T20,
        typename T21, typename T22, typename T23, typename T24, typename T25,
        typename T26, typename T27, typename T28, typename T29, typename T30,
        typename T31, typename T32, typename T33, typename T34, typename T35,
        typename T36, typename T37, typename T38, typename T39, typename T40,
        typename T41, typename T42, typename T43, typename T44, typename T45,
        typename T46, typename T47, typename T48, typename T49, typename T50,
        typename T51, typename T52>
    struct TypeList<BigTypes<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
        T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28,
        T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43,
        T44, T45, T46, T47, T48, T49, T50, T51, T52> > {
      typedef typename BigTypes<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
          T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
          T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
          T41, T42, T43, T44, T45, T46, T47, T48, T49, T50, T51, T52>::type type;
    };

    template <typename T1, typename T2, typename T3, typename T4, typename T5,
        typename T6, typename T7, typename T8, typename T9, typename T10,
        typename T11, typename T12, typename T13, typename T14, typename T15,
        typename T16, typename T17, typename T18, typename T19, typename T20,
        typename T21, typename T22, typename T23, typename T24, typename T25,
        typename T26, typename T27, typename T28, typename T29, typename T30,
        typename T31, typename T32, typename T33, typename T34, typename T35,
        typename T36, typename T37, typename T38, typename T39, typename T40,
        typename T41, typename T42, typename T43, typename T44, typename T45,
        typename T46, typename T47, typename T48, typename T49, typename T50,
        typename T51, typename T52, typename T53>
    struct TypeList<BigTypes<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
        T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28,
        T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43,
        T44, T45, T46, T47, T48, T49, T50, T51, T52, T53> > {
      typedef typename BigTypes<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
          T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
          T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
          T41, T42, T43, T44, T45, T46, T47, T48, T49, T50, T51, T52, T53>::type type;
    };

    template <typename T1, typename T2, typename T3, typename T4, typename T5,
        typename T6, typename T7, typename T8, typename T9, typename T10,
        typename T11, typename T12, typename T13, typename T14, typename T15,
        typename T16, typename T17, typename T18, typename T19, typename T20,
        typename T21, typename T22, typename T23, typename T24, typename T25,
        typename T26, typename T27, typename T28, typename T29, typename T30,
        typename T31, typename T32, typename T33, typename T34, typename T35,
        typename T36, typename T37, typename T38, typename T39, typename T40,
        typename T41, typename T42, typename T43, typename T44, typename T45,
        typename T46, typename T47, typename T48, typename T49, typename T50,
        typename T51, typename T52, typename T53, typename T54>
    struct TypeList<BigTypes<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
        T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28,
        T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43,
        T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54> > {
      typedef typename BigTypes<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
          T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
          T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
          T41, T42, T43, T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54>::type type;
    };

    template <typename T1, typename T2, typename T3, typename T4, typename T5,
        typename T6, typename T7, typename T8, typename T9, typename T10,
        typename T11, typename T12, typename T13, typename T14, typename T15,
        typename T16, typename T17, typename T18, typename T19, typename T20,
        typename T21, typename T22, typename T23, typename T24, typename T25,
        typename T26, typename T27, typename T28, typename T29, typename T30,
        typename T31, typename T32, typename T33, typename T34, typename T35,
        typename T36, typename T37, typename T38, typename T39, typename T40,
        typename T41, typename T42, typename T43, typename T44, typename T45,
        typename T46, typename T47, typename T48, typename T49, typename T50,
        typename T51, typename T52, typename T53, typename T54, typename T55>
    struct TypeList<BigTypes<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
        T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28,
        T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43,
        T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54, T55> > {
      typedef typename BigTypes<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
          T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
          T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
          T41, T42, T43, T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54,
          T55>::type type;
    };

    template <typename T1, typename T2, typename T3, typename T4, typename T5,
        typename T6, typename T7, typename T8, typename T9, typename T10,
        typename T11, typename T12, typename T13, typename T14, typename T15,
        typename T16, typename T17, typename T18, typename T19, typename T20,
        typename T21, typename T22, typename T23, typename T24, typename T25,
        typename T26, typename T27, typename T28, typename T29, typename T30,
        typename T31, typename T32, typename T33, typename T34, typename T35,
        typename T36, typename T37, typename T38, typename T39, typename T40,
        typename T41, typename T42, typename T43, typename T44, typename T45,
        typename T46, typename T47, typename T48, typename T49, typename T50,
        typename T51, typename T52, typename T53, typename T54, typename T55,
        typename T56>
    struct TypeList<BigTypes<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
        T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28,
        T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43,
        T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54, T55, T56> > {
      typedef typename BigTypes<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
          T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
          T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
          T41, T42, T43, T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54,
          T55, T56>::type type;
    };

    template <typename T1, typename T2, typename T3, typename T4, typename T5,
        typename T6, typename T7, typename T8, typename T9, typename T10,
        typename T11, typename T12, typename T13, typename T14, typename T15,
        typename T16, typename T17, typename T18, typename T19, typename T20,
        typename T21, typename T22, typename T23, typename T24, typename T25,
        typename T26, typename T27, typename T28, typename T29, typename T30,
        typename T31, typename T32, typename T33, typename T34, typename T35,
        typename T36, typename T37, typename T38, typename T39, typename T40,
        typename T41, typename T42, typename T43, typename T44, typename T45,
        typename T46, typename T47, typename T48, typename T49, typename T50,
        typename T51, typename T52, typename T53, typename T54, typename T55,
        typename T56, typename T57>
    struct TypeList<BigTypes<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
        T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28,
        T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43,
        T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54, T55, T56, T57> > {
      typedef typename BigTypes<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
          T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
          T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
          T41, T42, T43, T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54,
          T55, T56, T57>::type type;
    };

    template <typename T1, typename T2, typename T3, typename T4, typename T5,
        typename T6, typename T7, typename T8, typename T9, typename T10,
        typename T11, typename T12, typename T13, typename T14, typename T15,
        typename T16, typename T17, typename T18, typename T19, typename T20,
        typename T21, typename T22, typename T23, typename T24, typename T25,
        typename T26, typename T27, typename T28, typename T29, typename T30,
        typename T31, typename T32, typename T33, typename T34, typename T35,
        typename T36, typename T37, typename T38, typename T39, typename T40,
        typename T41, typename T42, typename T43, typename T44, typename T45,
        typename T46, typename T47, typename T48, typename T49, typename T50,
        typename T51, typename T52, typename T53, typename T54, typename T55,
        typename T56, typename T57, typename T58>
    struct TypeList<BigTypes<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
        T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28,
        T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43,
        T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54, T55, T56, T57, T58> > {
      typedef typename BigTypes<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
          T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
          T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
          T41, T42, T43, T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54,
          T55, T56, T57, T58>::type type;
    };

    template <typename T1, typename T2, typename T3, typename T4, typename T5,
        typename T6, typename T7, typename T8, typename T9, typename T10,
        typename T11, typename T12, typename T13, typename T14, typename T15,
        typename T16, typename T17, typename T18, typename T19, typename T20,
        typename T21, typename T22, typename T23, typename T24, typename T25,
        typename T26, typename T27, typename T28, typename T29, typename T30,
        typename T31, typename T32, typename T33, typename T34, typename T35,
        typename T36, typename T37, typename T38, typename T39, typename T40,
        typename T41, typename T42, typename T43, typename T44, typename T45,
        typename T46, typename T47, typename T48, typename T49, typename T50,
        typename T51, typename T52, typename T53, typename T54, typename T55,
        typename T56, typename T57, typename T58, typename T59>
    struct TypeList<BigTypes<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
        T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28,
        T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43,
        T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54, T55, T56, T57, T58,
        T59> > {
      typedef typename BigTypes<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
          T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
          T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
          T41, T42, T43, T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54,
          T55, T56, T57, T58, T59>::type type;
    };

    template <typename T1, typename T2, typename T3, typename T4, typename T5,
        typename T6, typename T7, typename T8, typename T9, typename T10,
        typename T11, typename T12, typename T13, typename T14, typename T15,
        typename T16, typename T17, typename T18, typename T19, typename T20,
        typename T21, typename T22, typename T23, typename T24, typename T25,
        typename T26, typename T27, typename T28, typename T29, typename T30,
        typename T31, typename T32, typename T33, typename T34, typename T35,
        typename T36, typename T37, typename T38, typename T39, typename T40,
        typename T41, typename T42, typename T43, typename T44, typename T45,
        typename T46, typename T47, typename T48, typename T49, typename T50,
        typename T51, typename T52, typename T53, typename T54, typename T55,
        typename T56, typename T57, typename T58, typename T59, typename T60>
    struct TypeList<BigTypes<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
        T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28,
        T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43,
        T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54, T55, T56, T57, T58,
        T59, T60> > {
      typedef typename BigTypes<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
          T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
          T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
          T41, T42, T43, T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54,
          T55, T56, T57, T58, T59, T60>::type type;
    };

    template <typename T1, typename T2, typename T3, typename T4, typename T5,
        typename T6, typename T7, typename T8, typename T9, typename T10,
        typename T11, typename T12, typename T13, typename T14, typename T15,
        typename T16, typename T17, typename T18, typename T19, typename T20,
        typename T21, typename T22, typename T23, typename T24, typename T25,
        typename T26, typename T27, typename T28, typename T29, typename T30,
        typename T31, typename T32, typename T33, typename T34, typename T35,
        typename T36, typename T37, typename T38, typename T39, typename T40,
        typename T41, typename T42, typename T43, typename T44, typename T45,
        typename T46, typename T47, typename T48, typename T49, typename T50,
        typename T51, typename T52, typename T53, typename T54, typename T55,
        typename T56, typename T57, typename T58, typename T59, typename T60,
        typename T61>
    struct TypeList<BigTypes<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
        T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28,
        T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43,
        T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54, T55, T56, T57, T58,
        T59, T60, T61> > {
      typedef typename BigTypes<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
          T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
          T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
          T41, T42, T43, T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54,
          T55, T56, T57, T58, T59, T60, T61>::type type;
    };

    /*
     * In case of a new template parameter is needed:
     * Copy paste this struct with a version with 1 template parameter more.
     * Increase by one any integer you see in type names.
     */
    template <typename T1, typename T2, typename T3, typename T4, typename T5,
        typename T6, typename T7, typename T8, typename T9, typename T10,
        typename T11, typename T12, typename T13, typename T14, typename T15,
        typename T16, typename T17, typename T18, typename T19, typename T20,
        typename T21, typename T22, typename T23, typename T24, typename T25,
        typename T26, typename T27, typename T28, typename T29, typename T30,
        typename T31, typename T32, typename T33, typename T34, typename T35,
        typename T36, typename T37, typename T38, typename T39, typename T40,
        typename T41, typename T42, typename T43, typename T44, typename T45,
        typename T46, typename T47, typename T48, typename T49, typename T50,
        typename T51, typename T52, typename T53, typename T54, typename T55,
        typename T56, typename T57, typename T58, typename T59, typename T60,
        typename T61, typename T62>
    struct TypeList<BigTypes<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
        T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28,
        T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43,
        T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54, T55, T56, T57, T58,
        T59, T60, T61, T62> > {
      typedef typename BigTypes<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
          T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
          T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
          T41, T42, T43, T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54,
          T55, T56, T57, T58, T59, T60, T61, T62>::type type;
    };

    template <typename T1, typename T2, typename T3, typename T4, typename T5,
        typename T6, typename T7, typename T8, typename T9, typename T10,
        typename T11, typename T12, typename T13, typename T14, typename T15,
        typename T16, typename T17, typename T18, typename T19, typename T20,
        typename T21, typename T22, typename T23, typename T24, typename T25,
        typename T26, typename T27, typename T28, typename T29, typename T30,
        typename T31, typename T32, typename T33, typename T34, typename T35,
        typename T36, typename T37, typename T38, typename T39, typename T40,
        typename T41, typename T42, typename T43, typename T44, typename T45,
        typename T46, typename T47, typename T48, typename T49, typename T50,
        typename T51, typename T52, typename T53, typename T54, typename T55,
        typename T56, typename T57, typename T58, typename T59, typename T60,
        typename T61, typename T62, typename T63>
    struct TypeList<BigTypes<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
        T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28,
        T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43,
        T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54, T55, T56, T57, T58,
        T59, T60, T61, T62, T63> > {
      typedef typename BigTypes<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
          T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
          T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
          T41, T42, T43, T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54,
          T55, T56, T57, T58, T59, T60, T61, T62, T63>::type type;
    };
  } //namespace internal
} //namespace testing

#define PTR_FUN_PTR_FACTORIES \
        VoidPtrFunVoidPtrFactory, \
        CharPtrFunCharPtrFactory, \
        UnsCharPtrFunUnsCharPtrFactory, \
        ShortPtrFunShortPtrFactory, \
        UnsShortPtrFunUnsShortPtrFactory, \
        IntPtrFunIntPtrFactory, \
        UnsIntPtrFunUnsIntPtrFactory, \
        LongPtrFunLongPtrFactory, \
        UnsLongPtrFunUnsLongPtrFactory, \
        LongLongPtrFunLongLongPtrFactory, \
        UnsLongLongPtrFunUnsLongLongPtrFactory, \
        FloatPtrFunFloatPtrFactory, \
        DoublePtrFunDoublePtrFactory, \
        LongDoublePtrFunLongDoublePtrFactory, \
        ConstIntPtrFunConstIntPtr

#define NON_PTR_FUN_FACTORIES \
        VoidFunVoidFactory, \
        IntFunVoidFactory, \
        UnsIntFunVoidFactory, \
        IntFunIntIntFactory, \
        CharFunCharFactory, \
        UnsCharFunUnsCharFactory, \
        UnsIntFunUnsIntIntFactory, \
        ShortFunShortFactory, \
        UnsShortFunUnsShortFactory, \
        LongFunLongFactory, \
        UnsLongFunUnsLongFactory, \
        LongLongFunLongLongFactory, \
        UnsLongLongFunUnsLongLongFactory, \
        FloatFunFloatFactory, \
        DoubleFunDoubleFactory, \
        LongDoubleFunLongDoubleFactory, \
        StructFunStructFactory, \
        StructTypedDefFunStructTypedDefFactory, \
        StructAnonymousTypedDefFunStructAnonymousTypedDefFactory, \
        UnionFunUnionFactory, \
        UnionTypedDefFunUnionTypedDefFactory, \
        UnionAnonymousTypedDefFunUnionAnonymousTypedDefFactory, \
        StructWithUnionFunStructWithUnionFactory, \
        ConstIntFunConstIntFactory

#define VOID_FUN_COMPOSABLE_TYPE_WITH_COMPOSABLE_TYPE_TYPES \
        VoidFunStructWithEmbeddedStructFactory, \
        VoidFunStructWithEmbeddedAnonymousStructFactory, \
        VoidFunUnionWithEmbeddedUnionFactory, \
        VoidFunUnionWithEmbeddedAnonymousUnionFactory, \
        VoidFunStructWithAnonymousStructFieldFactory, \
        VoidFunUnionWithAnonymousUnionFieldFactory, \
        VoidFunStructWithFirstAnonymousStructFieldFactory, \
        VoidFunUnionWithFirstAnonymousUnionFieldFactory, \
        VoidFunStructWithTypedefStructFactory, \
        StructSubStructRecursiveTypeFactory

#define COMPILE_ONLY_TYPES \
        CompileTwoFunctionsFactory, \
        VariadicFunctionsFactory, \
        MultipleDefinitionsFactory, \
        FunctionVaArgsFactory, \
        VoidFunParamNoNameFactory, \
        VoidOutFactory, \
        InlineVoidFactory

typedef ::testing::Types
<
        NON_PTR_FUN_FACTORIES,
        PTR_FUN_PTR_FACTORIES
> GenerateTestTypes;

typedef ::testing::Types
<
        NON_PTR_FUN_FACTORIES
> NonPtrFunTypes;

typedef ::testing::Types
<
        PTR_FUN_PTR_FACTORIES
> PtrFunPtrTypes;

typedef ::testing::Types
<
        VOID_FUN_COMPOSABLE_TYPE_WITH_COMPOSABLE_TYPE_TYPES
> VoidFunComposableTypeWithComposableTypeTypes;

typedef ::testing::BigTypes
<
        PTR_FUN_PTR_FACTORIES,
        NON_PTR_FUN_FACTORIES,
        VOID_FUN_COMPOSABLE_TYPE_WITH_COMPOSABLE_TYPE_TYPES,
        COMPILE_ONLY_TYPES,
        StructRecursiveMemberPtrTypeFactory,
        VoidFunStructPtrFactory,
        IntFunStructPtrIntCharPtrFactory,
        VoidFunStructWithArrayFactory,
        VoidFunIntArrayFactory,
        VoidFunStructRecusNonTypedefFactory,
        StructFileFromStdioFactory
> ParserTestTypes;

typedef ::testing::Types
<
        COMPILE_ONLY_TYPES
> CompileOnlyTypes;

#endif /* TESTTYPES_H */

