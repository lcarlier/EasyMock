#include "VoidFunStructWithAnonymousStructFieldFactory.h"

#include <StructType.h>
#include <ComposableField.h>

std::shared_ptr<FunctionDeclaration> VoidFunStructWithAnonymousStructFieldFactory::functionFactory()
{
  bool isEmbeddedStruct = true;
  auto top = std::make_shared<StructType>("topAnonymousStructField", !isEmbeddedStruct); //NOT EMBEDDED
  top->addField(ComposableField(CTYPE_INT, "a"));
  auto beingDefined = std::make_shared<StructType>("", isEmbeddedStruct);
  beingDefined->addField(ComposableField(CTYPE_INT, "s1"));
  beingDefined->addField(ComposableField(CTYPE_FLOAT, "s2"));
  top->addField(ComposableField(std::move(beingDefined), ""));

  Parameter::Vector pv{};
  pv.emplace_back(Parameter(std::move(top), "t"));
  auto f = std::make_shared<FunctionDeclaration>(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), std::move(pv));

  return f;
}

std::string VoidFunStructWithAnonymousStructFieldFactory::functionGetFunctionName()
{
  return std::string("voidFunStructWithAnonymousStructField");
}

std::string VoidFunStructWithAnonymousStructFieldFactory::getFilename()
{
   return "voidFunStructWithAnonymousStructField.h";
}

std::string VoidFunStructWithAnonymousStructFieldFactory::getMatcherFunctionName()
{
  return "cmp_struct_topAnonymousStructField";
}

std::string VoidFunStructWithAnonymousStructFieldFactory::getFieldWrongName()
{
  return "t";
}

std::string VoidFunStructWithAnonymousStructFieldFactory::getSubFieldWrongName()
{
  return "s2";
}

std::string VoidFunStructWithAnonymousStructFieldFactory::getSubFieldWrongTypeName()
{
  return "topAnonymousStructField::<anonymous>";
}

std::string VoidFunStructWithAnonymousStructFieldFactory::getSubComposableTypeType()
{
  return " struct";
}

void VoidFunStructWithAnonymousStructFieldFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  struct topAnonymousStructField aToExpect;

  aToExpect.a = 42;
  aToExpect.s1 = 42;
  aToExpect.s2 = 6.;
  switch(tc)
  {
    case EasyMockTestCase::TestCase::OneExpect:
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(m_user_matcher));
      break;
    case EasyMockTestCase::TestCase::OneExpectArgIsBad:
      m_expects.push_back(std::make_tuple(aToExpect));
      aToExpect.s2+=1;
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(m_user_matcher));
      break;
    case EasyMockTestCase::TestCase::ThreeExpects:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_expects.push_back(std::make_tuple(aToExpect));
        m_params.push_back(std::make_tuple(aToExpect));
        m_compare.push_back(std::make_tuple(m_user_matcher));
      }
      break;
    case EasyMockTestCase::TestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_expects.push_back(std::make_tuple(aToExpect));
        m_params.push_back(std::make_tuple(aToExpect));
        m_compare.push_back(std::make_tuple(m_user_matcher));
      }
      break;
    case EasyMockTestCase::TestCase::SecondExpectArgIsBad:
    case EasyMockTestCase::TestCase::NoExpect:
      break;
  }
}
