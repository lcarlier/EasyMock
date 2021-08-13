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
#include <CrossDefinedFunCrossDefinedFactory.h>
#include <Int128FunUint128Factory.h>
#include <VoidFunStructBitfieldFactory.h>
#include <VoidFunStructWithConstMemberFactory.h>
#include <VoidFunStructWithSecondLevelAnonymousFactory.h>
#include <ConstVoidPtrFunConstVoidPtrFactory.h>
#include <VoidFunMultilineFactory.h>
#include <VoidFunStructCompleteFieldFactory.h>
#include <VoidFunAttrFunFactory.h>
#include <VoidFunUnnamedPtrParamFactory.h>
#include <VoidFunEmbeddedCommentsFactory.h>
#include <VoidFunStructWithAnonymousUnionFieldWithStructFactory.h>

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
        StructFunStructGenerateTypeFactory, \
        StructTypedDefFunStructTypedDefFactory, \
        StructTypedDefFunStructTypedDefGenerateTypeFactory, \
        StructAnonymousTypedDefFunStructAnonymousTypedDefFactory, \
        StructAnonymousTypedDefFunStructAnonymousTypedDefGenerateTypeFactory, \
        UnionFunUnionFactory, \
        UnionFunUnionGenerateTypeFactory, \
        UnionTypedDefFunUnionTypedDefFactory, \
        UnionTypedDefFunUnionTypedDefGenerateTypeFactory, \
        UnionAnonymousTypedDefFunUnionAnonymousTypedDefFactory, \
        UnionAnonymousTypedDefFunUnionAnonymousTypedDefGenerateTypeFactory, \
        StructWithUnionFunStructWithUnionFactory, \
        StructWithUnionFunStructWithUnionGenerateTypeFactory, \
        ConstIntFunConstIntFactory, \
        Int128FunUint128Factory, \
        Int128FunUint128FactoryGenTypeFactory

#define VOID_FUN_COMPOSABLE_TYPE_WITH_COMPOSABLE_TYPE_TYPES \
        VoidFunStructWithEmbeddedStructFactory, \
        VoidFunStructWithEmbeddedStructGenerateTypeFactory, \
        VoidFunStructWithEmbeddedAnonymousStructFactory, \
        VoidFunStructWithEmbeddedAnonymousStructGenerateTypeFactory, \
        VoidFunUnionWithEmbeddedUnionFactory, \
        VoidFunUnionWithEmbeddedUnionGenerateTypeFactory, \
        VoidFunUnionWithEmbeddedAnonymousUnionFactory, \
        VoidFunUnionWithEmbeddedAnonymousUnionGenerateTypeFactory, \
        VoidFunStructWithAnonymousStructFieldFactory, \
        VoidFunStructWithAnonymousStructFieldGenerateTypeFactory, \
        VoidFunUnionWithAnonymousUnionFieldFactory, \
        VoidFunUnionWithAnonymousUnionFieldGenerateTypeFactory, \
        VoidFunStructWithFirstAnonymousStructFieldFactory, \
        VoidFunStructWithFirstAnonymousStructFieldGenerateTypeFactory, \
        VoidFunUnionWithFirstAnonymousUnionFieldFactory, \
        VoidFunUnionWithFirstAnonymousUnionFieldGenerateTypeFactory, \
        VoidFunStructWithTypedefStructFactory, \
        VoidFunStructWithTypedefStructGenerateTypeFactory, \
        StructSubStructRecursiveTypeFactory, \
        StructSubStructRecursiveTypeGenerateTypeFactory, \
        VoidFunStructBitfieldFactory, \
        VoidFunStructBitfieldGenerateTypeFactory, \
        VoidFunStructWithSecondLevelAnonymousFactory, \
        VoidFunStructWithSecondLevelAnonymousGenerateTypeFactory, \
        VoidFunStructWithAnonymousUnionFieldWithStructFactory, \
        VoidFunStructWithAnonymousUnionFieldWithStructGenerateTypeFactory

#define COMPILE_ONLY_TYPES \
        CompileTwoFunctionsFactory, \
        VariadicFunctionsFactory, \
        MultipleDefinitionsFactory, \
        FunctionVaArgsFactory, \
        VoidFunParamNoNameFactory, \
        VoidOutFactory, \
        InlineVoidFactory, \
        VoidFunFunPtrFactory, \
        VoidFunFunPtrGenerateTypeFactory, \
        VoidFunTypedefFunPtrFactory, \
        VoidFunEnumFactory, \
        VoidFunEnumGenerateTypeFactory, \
        VoidFunPtrToPtrRecurStructFactory, \
        VoidFunStructForwardDeclaredFactory, \
        VoidFunStructForwardDeclaredGenerateTypeFactory, \
        VoidFunTypeDefFactory, \
        VoidFunTypeDefGenerateTypeFactory, \
        CrossDefinedFunCrossDefinedFactory, \
        CrossDefinedFunCrossDefinedGenTypeFactory, \
        VoidFunTypedefFunPtrGenerateTypeFactory, \
        VoidFunStructWithConstMemberFactory, \
        VoidFunStructWithConstMemberGenerateTypeFactory, \
        StructRecursiveMemberPtrTypeFactory, \
        StructRecursiveMemberPtrTypeGenerateTypeFactory, \
        StructFileFromStdioFactory, \
        StructFileFromStdioGenerateTypeFactory, \
        VoidFunStructPtrFactory, \
        VoidFunStructPtrGenerateTypeFactory, \
        VoidFunStructRecusNonTypedefFactory, \
        VoidFunStructRecusNonTypedefGenerateTypeFactory, \
        VoidFunStructWithArrayFactory, \
        VoidFunStructWithArrayGenerateTypeFactory, \
        ConstVoidPtrFunConstVoidPtrFactory, \
        ConstVoidPtrFunConstVoidPtrGenerateTypeFactory, \
        VoidFunMultilineFactory,  \
        VoidFunMultilineGenerateTypeFactory, \
        VoidFunStructCompleteFieldFactory, \
        VoidFunStructCompleteFieldGenerateTypeFactory, \
        VoidFunAttrFunFactory, \
        VoidFunAttrFunGenerateTypeFactory, \
        VoidFunUnnamedPtrParamFactory, \
        VoidFunUnnamedPtrParamGenerateTypeFactory, \
        VoidFunEmbeddedCommentsFactory, \
        VoidFunEmbeddedCommentsGenerateTypeFactory

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
        IntFunStructPtrIntCharPtrFactory,
        VoidFunIntArrayFactory,
        VoidFunIntArrayGenerateTypeFactory
> ParserTestTypes;

typedef ::testing::Types
<
        COMPILE_ONLY_TYPES
> CompileOnlyTypes;

#endif /* TESTTYPES_H */
