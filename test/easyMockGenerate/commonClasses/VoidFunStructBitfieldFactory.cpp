#include <VoidFunStructBitfieldFactory.h>

#include <FunctionDeclaration.h>
#include <Parameter.h>
#include <EasyMock_CType.h>
#include <StructType.h>
#include <ComposableField.h>
#include <ComposableBitfield.h>
#include <TypedefType.h>

std::shared_ptr<FunctionDeclaration> VoidFunStructBitfieldFactory::functionFactory()
{
  auto s = std::make_shared<StructType>("BoxProps", false);
  s->addField(ComposableBitfield(CTYPE_UINT, "opaque", 1));
  s->addField(ComposableBitfield(CTYPE_UINT, "fill_color", 3));
  s->addField(ComposableBitfield(CTYPE_UINT, "", 4));
  s->addField(ComposableBitfield(CTYPE_UINT, "show_border", 1));
  auto uintType = std::make_shared<TypedefType>( "t_uint", std::make_shared<CType>(CTYPE_UINT) );
  s->addField(ComposableBitfield(std::move(uintType), "border_color", 3));
  s->addField(ComposableBitfield(CTYPE_UINT, "border_style", 2));
  s->addField(ComposableBitfield(CTYPE_UCHAR, "", 0));
  s->addField(ComposableBitfield(CTYPE_UCHAR, "width", 4));
  s->addField(ComposableBitfield(CTYPE_UCHAR, "height", 4));
#if defined(__APPLE__)
  auto uint64t = std::make_shared<TypedefType>("uint64_t", std::make_shared<CType>(CTYPE_ULONG_LONG));
#elif defined(__linux__)
  auto uint64t = std::make_shared<TypedefType>("uint64_t", std::make_shared<CType>(CTYPE_ULONG));
#endif
  s->addField(ComposableBitfield(uint64t, "bit64_0", 1));
  s->addField(ComposableBitfield(uint64t, "bit64_1", 1));
  s->addField(ComposableBitfield(std::move(uint64t), "rest64", 62));
  auto uint32t = std::make_shared<TypedefType>("uint32_t", std::make_shared<CType>(CTYPE_UINT));
  s->addField(ComposableBitfield(uint32t, "bit32_0", 1));
  s->addField(ComposableBitfield(uint32t, "bit32_1", 1));
  s->addField(ComposableBitfield(std::move(uint32t), "rest32", 30));
  auto uint16t = std::make_shared<TypedefType>("uint16_t", std::make_shared<CType>(CTYPE_USHORT));
  s->addField(ComposableBitfield(uint16t, "bit16_0", 1));
  s->addField(ComposableBitfield(uint16t, "bit16_1", 1));
  s->addField(ComposableBitfield(std::move(uint16t), "rest16", 14));
  auto uint8t = std::make_shared<TypedefType>("uint8_t", std::make_shared<CType>(CTYPE_UCHAR));
  s->addField(ComposableBitfield(uint8t, "bit8_0", 1));
  s->addField(ComposableBitfield(uint8t, "bit8_1", 1));
  s->addField(ComposableBitfield(std::move(uint8t), "rest8", 6));

  auto sContainer = std::make_shared<StructType>("BoxPropsContainer", false);
  sContainer->addField(ComposableField(std::move(s), "b"));

  Parameter::Vector pv{};
  pv.emplace_back(Parameter(std::move(sContainer), "s"));
  auto f = std::make_shared<FunctionDeclaration>(functionGetFunctionName(), VoidReturnValue(), std::move(pv));
  return f;
}

std::string VoidFunStructBitfieldFactory::functionGetFunctionName()
{
  return "voidFunStructBitfield";
}

std::string VoidFunStructBitfieldFactory::getFilename()
{
  return "voidFunStructBitfield.h";
}

std::string VoidFunStructBitfieldFactory::getMatcherFunctionName()
{
  return "cmp_struct_BoxPropsContainer";
}

std::string VoidFunStructBitfieldFactory::getFieldWrongName()
{
  return "s.b";
}

std::string VoidFunStructBitfieldFactory::getSubFieldWrongName()
{
  return "border_color";
}

std::string VoidFunStructBitfieldFactory::getSubFieldWrongTypeName()
{
  return "BoxProps";
}

std::string VoidFunStructBitfieldFactory::getSubComposableTypeType()
{
  return " struct";
}

void VoidFunStructBitfieldFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  struct BoxPropsContainer aToExpect;
  aToExpect.b.border_color = 1;
  aToExpect.b.border_style = 2;
  aToExpect.b.fill_color = 3;
  aToExpect.b.height = 4;
  aToExpect.b.opaque = 1;
  aToExpect.b.show_border = 1;
  aToExpect.b.width = 5;
  aToExpect.b.bit64_0 = 0;
  aToExpect.b.bit64_1 = 1;
  aToExpect.b.rest64 = 0;
  aToExpect.b.bit32_0 = 1;
  aToExpect.b.bit32_1 = 0;
  aToExpect.b.rest32 = 0;
  aToExpect.b.bit16_0 = 0;
  aToExpect.b.bit16_1 = 1;
  aToExpect.b.rest16 = 0;
  aToExpect.b.bit8_0 = 1;
  aToExpect.b.bit8_0 = 0;
  aToExpect.b.rest8 = 0;

  switch(tc)
  {
    case EasyMockTestCase::TestCase::OneExpect:
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(m_user_matcher));
      break;
    case EasyMockTestCase::TestCase::ThreeExpects:
    {
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        aToExpect.b.border_color++;
        m_expects.push_back(std::make_tuple(aToExpect));
        m_params.push_back(std::make_tuple(aToExpect));
        m_compare.push_back(std::make_tuple(m_user_matcher));
      }
      break;
    }
    case EasyMockTestCase::TestCase::OneExpectArgIsBad:
      m_expects.push_back(std::make_tuple(aToExpect));
      aToExpect.b.border_color++;
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(m_user_matcher));
      break;
    case EasyMockTestCase::TestCase::SecondExpectArgIsBad:
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(m_user_matcher));

      m_expects.push_back(std::make_tuple(aToExpect));
      aToExpect.b.border_color++;
      m_params.push_back(std::make_tuple(aToExpect)); //second call fails
      m_compare.push_back(std::make_tuple(m_user_matcher));
      break;
    case EasyMockTestCase::TestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        aToExpect.b.border_color++;
        m_expects.push_back(std::make_tuple(aToExpect));
        m_params.push_back(std::make_tuple(aToExpect));
        m_compare.push_back(std::make_tuple(m_user_matcher));
      }
      break;
    case EasyMockTestCase::TestCase::NoExpect:
      break;
  }
}
