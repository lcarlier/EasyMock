#include <gtest/gtest.h> // googletest header file

#include <LLVMParser.h>
#include <Function.h>

#include <test_voidFunVoid.h>
#include <test_intFunVoid.h>
#include <test_unsIntFunVoid.h>
#include <test_charFunChar.h>
#include <test_intFunIntInt.h>
#include <test_unsIntFunUnsIntInt.h>
#include <test_shortFunShort.h>
#include <test_unsShortFunUnsShort.h>
#include <test_floatFunFloat.h>
#include <test_doubleFunDouble.h>
#include <test_unsCharFunUnsChar.h>
#include <test_longFunLong.h>
#include <test_unsLongFunUnsLong.h>
#include <test_longLongFunLongLong.h>
#include <test_unsLongLongFunUnsLongLong.h>
#include <test_longDoubleFunLongDouble.h>
#include <test_structFunStruct.h>

template <typename T>
class GenericParser_testCase : public ::testing::Test
{
};

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
> MyTypes;

TYPED_TEST_CASE(GenericParser_testCase, MyTypes);

TYPED_TEST(GenericParser_testCase, parser)
{
  ElementToMock::Vector elem;
  LLVMParser parser;
  std::string fileName(PROJECT_ROOT_DIR"/test/easyMockGenerate/include/");
  fileName.append(TypeParam::getFilename());
  parser.setFilename(fileName);
  parser.getElementToStub(elem);
  EXPECT_EQ(elem.size(), 1);
  Function& fp = Function::toFunction(elem[0]);
  Function f = functionFactory<TypeParam>();
  EXPECT_EQ(f, fp);
}
