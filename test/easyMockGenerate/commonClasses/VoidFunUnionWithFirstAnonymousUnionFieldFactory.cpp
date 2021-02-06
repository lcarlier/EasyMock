#include <VoidFunUnionWithFirstAnonymousUnionFieldFactory.h>

#include <UnionType.h>
#include <ComposableField.h>

FunctionDeclaration VoidFunUnionWithFirstAnonymousUnionFieldFactory::functionFactory()
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
  UnionType* top = new UnionType("topAnonymousFirstUnionField", !isEmbeddedStruct); //NOT EMBEDDED
  UnionType* beingDefined = new UnionType("", isEmbeddedStruct);
  beingDefined->addField(new ComposableField(CTYPE_INT, "s1"));
  beingDefined->addField(new ComposableField(CTYPE_FLOAT, "s2"));
  top->addField(new ComposableField(beingDefined, ""));
  top->addField(new ComposableField(CTYPE_INT, "a"));
  FunctionDeclaration f(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), Parameter::Vector({new Parameter(top, "u")}));

  return f;
}

FunctionDeclaration* VoidFunUnionWithFirstAnonymousUnionFieldFactory::newFunctionFactory()
{
  return functionFactory().clone();
}


std::string VoidFunUnionWithFirstAnonymousUnionFieldFactory::functionGetFunctionName()
{
  return std::string("voidFunUnionWithFirstAnonymousUnionField");
}

std::string VoidFunUnionWithFirstAnonymousUnionFieldFactory::getFilename()
{
   return "voidFunUnionWithFirstAnonymousUnionField.h";
}

std::string VoidFunUnionWithFirstAnonymousUnionFieldFactory::getMatcherFunctionName()
{
  return "cmp_union_topAnonymousFirstUnionField";
}

std::string VoidFunUnionWithFirstAnonymousUnionFieldFactory::getFieldWrongName()
{
  return "u";
}

std::string VoidFunUnionWithFirstAnonymousUnionFieldFactory::getSubFieldWrongName()
{
  /*
   * Even though the setupTestCase function modify s2, the field of the union
   * which will return an error is the first. I.E: s1
   */
  return "s1";
}

std::string VoidFunUnionWithFirstAnonymousUnionFieldFactory::getSubFieldWrongTypeName()
{
  /*
   * As the opposite of voidFunUnionWithAnonymousFieldUnion, we execute the
   * comparator of the anonymous union, so the anonymous string should be
   * returned
   */
  return "topAnonymousFirstUnionField::<anonymous>";
}

std::string VoidFunUnionWithFirstAnonymousUnionFieldFactory::getSubComposableTypeType()
{
  return "n union";
}

void VoidFunUnionWithFirstAnonymousUnionFieldFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  union topAnonymousFirstUnionField aToExpect;

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
