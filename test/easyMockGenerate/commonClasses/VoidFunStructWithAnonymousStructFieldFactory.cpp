#include "VoidFunStructWithAnonymousStructFieldFactory.h"

#include <StructType.h>

Function VoidFunStructWithAnonymousStructFieldFactory::functionFactory()
{
  const unsigned int NB_ANONYMOUS_TYPE_IN_THIS_UT = 1;
  /*
   * with -fno-access-control we are able to set this static class variable to
   * decrement the number of anonymous composable type by the number of anonymous
   * type the UT contains.
   * Thanks to that, the following code will generate the same anonymous ID
   */
  ComposableType::m_number_of_anonymous_composable_type -= NB_ANONYMOUS_TYPE_IN_THIS_UT;
  bool isEmbeddedStruct = true;
  StructType* top = new StructType("topAnonymousStructField", !isEmbeddedStruct); //NOT EMBEDDED
  top->addStructField(new ComposableField(CTYPE_INT, "a"));
  StructType* beingDefined = new StructType("", isEmbeddedStruct);
  beingDefined->addStructField(new ComposableField(CTYPE_INT, "s1"));
  beingDefined->addStructField(new ComposableField(CTYPE_FLOAT, "s2"));
  top->addStructField(new ComposableField(beingDefined, ""));
  Function f(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), Parameter::Vector({new Parameter(top, "t")}));

  return f;
}

Function* VoidFunStructWithAnonymousStructFieldFactory::newFunctionFactory()
{
  return functionFactory().clone();
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
    case EasyMockTestCase::OneExpect:
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(m_user_matcher));
      break;
    case EasyMockTestCase::OneExpectArgIsBad:
      m_expects.push_back(std::make_tuple(aToExpect));
      aToExpect.s2+=1;
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(m_user_matcher));
      break;
    case EasyMockTestCase::ThreeExpects:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_expects.push_back(std::make_tuple(aToExpect));
        m_params.push_back(std::make_tuple(aToExpect));
        m_compare.push_back(std::make_tuple(m_user_matcher));
      }
      break;
    case EasyMockTestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_expects.push_back(std::make_tuple(aToExpect));
        m_params.push_back(std::make_tuple(aToExpect));
        m_compare.push_back(std::make_tuple(m_user_matcher));
      }
      break;
    case EasyMockTestCase::SecondExpectArgIsBad:
    case EasyMockTestCase::NoExpect:
      break;
  }
}
