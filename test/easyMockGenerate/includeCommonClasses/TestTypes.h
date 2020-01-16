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
        VoidPtrFunVoidPtrFactory,
        CharPtrFunCharPtrFactory,
        UnsCharPtrFunUnsCharPtrFactory,
        ShortPtrFunShortPtrFactory,
        UnsShortPtrFunUnsShortPtrFactory,
        IntPtrFunIntPtrFactory,
        UnsIntPtrFunUnsIntPtrFactory,
        LongPtrFunLongPtrFactory,
        UnsLongLongFunUnsLongLongFactory,
        LongLongPtrFunLongLongPtrFactory,
        UnsLongLongPtrFunUnsLongLongPtrFactory,
        FloatPtrFunFloatPtrFactory,
        DoublePtrFunDoublePtrFactory,
        LongDoublePtrFunLongDoublePtrFactory
> TestTypes;

#endif /* TESTTYPES_H */

