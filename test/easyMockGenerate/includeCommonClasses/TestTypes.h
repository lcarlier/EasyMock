#ifndef TESTTYPES_H
#define TESTTYPES_H

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
#include <VoidFunStructWithEmbeddedStructFactory.h>
#include <VoidFunStructWithEmbeddedAnonymousStructFactory.h>
#include <VoidFunUnionWithEmbeddedUnionFactory.h>
#include <VoidFunUnionWithEmbeddedAnonymousUnionFactory.h>
#include <VoidFunStructWithAnonymousStructFieldFactory.h>
#include <VoidFunUnionWithAnonymousUnionFieldFactory.h>

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
        LongDoublePtrFunLongDoublePtrFactory

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
        StructRecursiveMemberPtrTypeFactory, \
        StructTypedDefFunStructTypedDefFactory, \
        StructAnonymousTypedDefFunStructAnonymousTypedDefFactory, \
        UnionFunUnionFactory, \
        UnionTypedDefFunUnionTypedDefFactory, \
        UnionAnonymousTypedDefFunUnionAnonymousTypedDefFactory

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
        PTR_FUN_PTR_FACTORIES,
        NON_PTR_FUN_FACTORIES,
        VoidFunStructPtrFactory,
        IntFunStructPtrIntCharPtrFactory,
        VoidFunStructWithArrayFactory,
        VoidFunIntArrayFactory,
        StructSubStructRecursiveTypeFactory,
        VoidFunStructWithEmbeddedStructFactory,
        VoidFunStructWithEmbeddedAnonymousStructFactory,
        VoidFunUnionWithEmbeddedUnionFactory,
        VoidFunUnionWithEmbeddedAnonymousUnionFactory,
        VoidFunStructWithAnonymousStructFieldFactory,
        VoidFunUnionWithAnonymousUnionFieldFactory
> ParserTestTypes;

#endif /* TESTTYPES_H */

