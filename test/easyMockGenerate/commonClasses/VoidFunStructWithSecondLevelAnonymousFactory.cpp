#include "VoidFunStructWithSecondLevelAnonymousFactory.h"

#include <FunctionDeclaration.h>
#include <Parameter.h>
#include <EasyMock_CType.h>
#include <StructType.h>
#include <ComposableField.h>
#include <Pointer.h>
#include <IncompleteType.h>
#include <TypedefType.h>

FunctionDeclaration VoidFunStructWithSecondLevelAnonymousFactory::functionFactory()
{
  auto ttop = std::make_shared<TypedefType>("top_t", std::make_shared<StructType>("top", false));
  ComposableType *top = ttop->getTypee()->asComposableType();
  {
    auto sLevel1 = std::make_shared<StructType>("level1", true);
    {
      auto anonymousStruct = std::make_shared<StructType>("", true);
      {
        {
          auto tsLevel2 = std::make_shared<TypedefType>("level2_t", std::make_shared<StructType>("level2", false));
          ComposableType *sLevel2 = tsLevel2->getTypee()->asComposableType();
          sLevel2->addField(ComposableField(CTYPE_INT, "a"));
          anonymousStruct->addField(ComposableField(std::move(tsLevel2), "l2"));
        }

        {
          auto anonymousStruct1 = std::make_shared<StructType>("", true);
          anonymousStruct1->addField(ComposableField(CTYPE_INT, "a"));
          auto c = std::make_shared<TypedefType>("u8", std::make_shared<CType>(CTYPE_UCHAR));
          anonymousStruct1->addField(ComposableField(std::move(c), "b"));
          anonymousStruct->addField(ComposableField(std::move(anonymousStruct1), ""));
        }

        {
          auto anonymousStruct2 = std::make_shared<StructType>("", true);
          anonymousStruct2->addField(ComposableField(CTYPE_INT, "c"));
          anonymousStruct2->addField(ComposableField(CTYPE_INT, "d"));
          anonymousStruct->addField(ComposableField(std::move(anonymousStruct2), ""));
        }
      }

      sLevel1->addField(ComposableField(std::move(anonymousStruct), ""));
    }
    top->addField(ComposableField(std::move(sLevel1), "l1"));
  }

  Parameter::Vector pv{};
  pv.emplace_back(Parameter(std::move(ttop), "s"));
  FunctionDeclaration f(functionGetFunctionName(), VoidReturnValue(), std::move(pv));

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
