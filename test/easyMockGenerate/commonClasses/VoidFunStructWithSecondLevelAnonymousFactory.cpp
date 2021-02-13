#include "VoidFunStructWithSecondLevelAnonymousFactory.h"

#include <FunctionDeclaration.h>
#include <Parameter.h>
#include <EasyMock_CType.h>
#include <StructType.h>
#include <ComposableField.h>
#include <Pointer.h>
#include <IncompleteType.h>

FunctionDeclaration VoidFunStructWithSecondLevelAnonymousFactory::functionFactory()
{
  StructType *top = new StructType("top", "top_t", false);
  {
    StructType *sLevel1 = new StructType("level1", true);
    {
      StructType *anonymousStruct = new StructType("", true);
      {
        {
          StructType *sLevel2 = new StructType("level2", "level2_t", false);
          sLevel2->addField(new ComposableField(CTYPE_INT, "a"));
          anonymousStruct->addField(new ComposableField(sLevel2, "l2"));
        }

        {
          StructType *anonymousStruct1 = new StructType("", true);
          anonymousStruct1->addField(new ComposableField(CTYPE_INT, "a"));
          CType *c = new CType(CTYPE_CHAR, "u8");
          anonymousStruct1->addField(new ComposableField(c, "b"));
          anonymousStruct->addField(new ComposableField(anonymousStruct1, ""));
        }

        {
          StructType *anonymousStruct2 = new StructType("", true);
          anonymousStruct2->addField(new ComposableField(CTYPE_INT, "c"));
          anonymousStruct2->addField(new ComposableField(CTYPE_INT, "d"));
          anonymousStruct->addField(new ComposableField(anonymousStruct2, ""));
        }
      }

      sLevel1->addField(new ComposableField(anonymousStruct, ""));
    }
    ComposableField* level1Field = new ComposableField(sLevel1, "l1");
    level1Field->setDeclareString("struct level1");
    top->addField(level1Field);
  }

  Parameter* p = new Parameter(top, "s");

  FunctionDeclaration f(functionGetFunctionName(), VoidReturnValue(), Parameter::Vector({p}));

  constexpr unsigned int NB_ANONYMOUS_TYPE_IN_THIS_UT = 3;
  /*
   * with -fno-access-control we are able to set this static class variable to
   * decrement the number of anonymous composable type by the number of anonymous
   * type the UT contains.
   * Thanks to that, the parser will generate the same anonymous ID as the code above.
   */
  ComposableType::m_number_of_anonymous_composable_type -= NB_ANONYMOUS_TYPE_IN_THIS_UT;
  return f;
}

std::string VoidFunStructWithSecondLevelAnonymousFactory::functionGetFunctionName()
{
  return "voidFunStructWithSecondLevelAnonymous";
}

std::string VoidFunStructWithSecondLevelAnonymousFactory::getFilename()
{
  return "voidFunStructWithSecondLevelAnonymous.h";
}

std::string VoidFunStructWithSecondLevelAnonymousFactory::getMatcherFunctionName()
{
  return "cmp_top_t";
}

std::string VoidFunStructWithSecondLevelAnonymousFactory::getFieldWrongName()
{
  return "s.l1";
}

std::string VoidFunStructWithSecondLevelAnonymousFactory::getSubFieldWrongName()
{
  return "a";
}

std::string VoidFunStructWithSecondLevelAnonymousFactory::getSubFieldWrongTypeName()
{
  return "top_t::level1::<anonymous>::<anonymous>";
}

std::string VoidFunStructWithSecondLevelAnonymousFactory::getSubComposableTypeType()
{
  return " struct";
}

void VoidFunStructWithSecondLevelAnonymousFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  top_t aToExpect;
  aToExpect.l1.l2.a = 1;
  aToExpect.l1.a = 2;
  aToExpect.l1.b = 3;
  aToExpect.l1.c = 4;
  aToExpect.l1.d = 5;

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
        aToExpect.l1.a++;
        m_expects.push_back(std::make_tuple(aToExpect));
        m_params.push_back(std::make_tuple(aToExpect));
        m_compare.push_back(std::make_tuple(m_user_matcher));
      }
      break;
    }
    case EasyMockTestCase::OneExpectArgIsBad:
      m_expects.push_back(std::make_tuple(aToExpect));
      aToExpect.l1.a++;
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(m_user_matcher));
      break;
    case EasyMockTestCase::SecondExpectArgIsBad:
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(m_user_matcher));

      m_expects.push_back(std::make_tuple(aToExpect));
      aToExpect.l1.a++;
      m_params.push_back(std::make_tuple(aToExpect)); //second call fails
      m_compare.push_back(std::make_tuple(m_user_matcher));
      break;
    case EasyMockTestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        aToExpect.l1.a++;
        m_expects.push_back(std::make_tuple(aToExpect));
        m_params.push_back(std::make_tuple(aToExpect));
        m_compare.push_back(std::make_tuple(m_user_matcher));
      }
      break;
    case EasyMockTestCase::NoExpect:
      break;
  }
}
