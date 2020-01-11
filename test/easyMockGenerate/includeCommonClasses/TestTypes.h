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
        StructFunStructFactory
> TestTypes;

#endif /* TESTTYPES_H */

