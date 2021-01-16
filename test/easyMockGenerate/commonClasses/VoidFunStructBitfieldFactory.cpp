#include <VoidFunStructBitfieldFactory.h>

#include <FunctionDeclaration.h>
#include <Parameter.h>
#include <EasyMock_CType.h>
#include <StructType.h>
#include <ComposableField.h>
#include <ComposableBitfield.h>

FunctionDeclaration VoidFunStructBitfieldFactory::functionFactory()
{
  StructType *s = new StructType("BoxProps", false);
  s->addField(new ComposableBitfield(CTYPE_UINT, "opaque", 1));
  s->addField(new ComposableBitfield(CTYPE_UINT, "fill_color", 3));
  s->addField(new ComposableBitfield(CTYPE_UINT, "", 4));
  s->addField(new ComposableBitfield(CTYPE_UINT, "show_border", 1));
  s->addField(new ComposableBitfield(CTYPE_UINT, "border_color", 3));
  s->addField(new ComposableBitfield(CTYPE_UINT, "border_style", 2));
  s->addField(new ComposableBitfield(CTYPE_UCHAR, "", 0));
  s->addField(new ComposableBitfield(CTYPE_UCHAR, "width", 4));
  s->addField(new ComposableBitfield(CTYPE_UCHAR, "height", 4));

  StructType *sContainer = new StructType("BoxPropsContainer", false);
  sContainer->addField(new ComposableField(s, "b"));

  Parameter* p = new Parameter(sContainer, "s");

  FunctionDeclaration f(functionGetFunctionName(), VoidReturnValue(), Parameter::Vector({p}));
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

  switch(tc)
  {
    case EasyMockTestCase::OneExpect:
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(m_user_matcher));
      break;
    case EasyMockTestCase::ThreeExpects:
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
    case EasyMockTestCase::OneExpectArgIsBad:
      m_expects.push_back(std::make_tuple(aToExpect));
      aToExpect.b.border_color++;
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(m_user_matcher));
      break;
    case EasyMockTestCase::SecondExpectArgIsBad:
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(m_user_matcher));

      m_expects.push_back(std::make_tuple(aToExpect));
      aToExpect.b.border_color++;
      m_params.push_back(std::make_tuple(aToExpect)); //second call fails
      m_compare.push_back(std::make_tuple(m_user_matcher));
      break;
    case EasyMockTestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        aToExpect.b.border_color++;
        m_expects.push_back(std::make_tuple(aToExpect));
        m_params.push_back(std::make_tuple(aToExpect));
        m_compare.push_back(std::make_tuple(m_user_matcher));
      }
      break;
    case EasyMockTestCase::NoExpect:
      break;
  }
}
