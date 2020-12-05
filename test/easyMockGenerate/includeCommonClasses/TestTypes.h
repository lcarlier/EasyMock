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
#include <VoidFunFunPtrFactory.h>
#include <VoidFunTypedefFunPtrFactory.h>
#include <VoidFunEnumFactory.h>
#include <VoidFunPtrToPtrRecurStructFactory.h>
#include <VoidFunStructForwardDeclaredFactory.h>
#include <VoidFunTypeDefFactory.h>
#include <VoidFunTypeDefGenTypeFactory.h>
#include <CrossDefinedFunCrossDefinedFactory.h>

// TestTypesInclude.h is generated
#include "TestTypesInclude.h"

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
        ConstIntPtrFunConstIntPtrFactory

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
        InlineVoidFactory, \
        VoidFunFunPtrFactory, \
        VoidFunTypedefFunPtrFactory, \
        VoidFunEnumFactory, \
        VoidFunPtrToPtrRecurStructFactory, \
        VoidFunStructForwardDeclaredFactory, \
        VoidFunTypeDefFactory, \
        VoidFunTypeDefGenTypeFactory, \
        CrossDefinedFunCrossDefinedFactory, \
        CrossDefinedFunCrossDefinedGenTypeFactory

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

