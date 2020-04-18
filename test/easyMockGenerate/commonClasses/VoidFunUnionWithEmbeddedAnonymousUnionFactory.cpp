#include <VoidFunUnionWithEmbeddedAnonymousUnionFactory.h>

#include <UnionType.h>

Function VoidFunUnionWithEmbeddedAnonymousUnionFactory::functionFactory()
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
  UnionType* top = new UnionType("topEmbeddedAnonymousUnion", !isEmbeddedStruct); //NOT EMBEDDED
  UnionType* beingDefined = new UnionType("", isEmbeddedStruct);
  beingDefined->addStructField(new ComposableField(CTYPE_INT, "a"));
  beingDefined->addStructField(new ComposableField(CTYPE_FLOAT, "b"));
  top->addStructField(new ComposableField(beingDefined, "eau"));
  Function f(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), Parameter::Vector({new Parameter(top, "u")}));
  return f;
}

Function* VoidFunUnionWithEmbeddedAnonymousUnionFactory::newFunctionFactory()
{
  return functionFactory().clone();
}


std::string VoidFunUnionWithEmbeddedAnonymousUnionFactory::functionGetFunctionName()
{
  return std::string("voidFunUnionWithEmbeddedAnonymousUnion");
}

std::string VoidFunUnionWithEmbeddedAnonymousUnionFactory::getFilename()
{
   return "voidFunUnionWithEmbeddedAnonymousUnion.h";
}

std::string VoidFunUnionWithEmbeddedAnonymousUnionFactory::getMatcherFunctionName()
{
  return "cmp_union_topEmbeddedAnonymousUnion";
}

std::string VoidFunUnionWithEmbeddedAnonymousUnionFactory::getFieldWrongName()
{
  return "u.eau";
}

std::string VoidFunUnionWithEmbeddedAnonymousUnionFactory::getSubFieldWrongName()
{
  return "a";
}

std::string VoidFunUnionWithEmbeddedAnonymousUnionFactory::getSubFieldWrongTypeName()
{
  return "topEmbeddedAnonymousUnion::<anonymous>";
}

std::string VoidFunUnionWithEmbeddedAnonymousUnionFactory::getSubComposableTypeType()
{
  return "n union";
}

void VoidFunUnionWithEmbeddedAnonymousUnionFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  union topEmbeddedAnonymousUnion aToExpect;

  aToExpect.eau.a = 42;
  switch(tc)
  {
    case EasyMockTestCase::OneExpect:
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(m_user_matcher));
      break;
    case EasyMockTestCase::OneExpectArgIsBad:
      m_expects.push_back(std::make_tuple(aToExpect));
      aToExpect.eau.a++;
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