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

#define COMMON_TYPES_PARSER_GENERATE \
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
        StructFunStructFactory

typedef ::testing::Types
<
        VoidFunVoidFactory,
        IntFunVoidFactory,
        UnsIntFunVoidFactory,
        IntFunIntIntFactory,
        CharFunCharFactory,
        UnsCharFunUnsCharFactory,
        UnsIntFunUnsIntIntFactory,
        ShortFunShortFactory,
        UnsShortFunUnsShortFactory,
        LongFunLongFactory,
        UnsLongFunUnsLongFactory,
        LongLongFunLongLongFactory,
        UnsLongLongFunUnsLongLongFactory,
        FloatFunFloatFactory,
        DoubleFunDoubleFactory,
        LongDoubleFunLongDoubleFactory,
        StructFunStructFactory,
        PTR_FUN_PTR_FACTORIES
> GenerateTestTypes;

typedef ::testing::Types
<
        PTR_FUN_PTR_FACTORIES
> PtrFunPtrTypes;

typedef ::testing::Types
<
        COMMON_TYPES_PARSER_GENERATE,
        VoidFunStructPtrFactory,
        IntFunStructPtrIntCharPtrFactory
> ParserTestTypes;

#endif /* TESTTYPES_H */

