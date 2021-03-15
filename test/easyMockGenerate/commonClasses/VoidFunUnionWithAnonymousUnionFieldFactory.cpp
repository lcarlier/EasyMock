#include <VoidFunUnionWithAnonymousUnionFieldFactory.h>

#include <UnionType.h>
#include <ComposableField.h>

FunctionDeclaration VoidFunUnionWithAnonymousUnionFieldFactory::functionFactory()
{
  bool isEmbeddedStruct = true;
  UnionType* top = new UnionType("topAnonymousUnionField", !isEmbeddedStruct); //NOT EMBEDDED
  top->addField(new ComposableField(CTYPE_INT, "a"));
  UnionType* beingDefined = new UnionType("", isEmbeddedStruct);
  beingDefined->addField(new ComposableField(CTYPE_INT, "s1"));
  beingDefined->addField(new ComposableField(CTYPE_FLOAT, "s2"));
  top->addField(new ComposableField(beingDefined, ""));
  FunctionDeclaration f(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), Parameter::Vector({new Parameter(top, "u")}));

  return f;
}

FunctionDeclaration* VoidFunUnionWithAnonymousUnionFieldFactory::newFunctionFactory()
{
  return functionFactory().clone();
}


std::string VoidFunUnionWithAnonymousUnionFieldFactory::functionGetFunctionName()
{
  return std::string("voidFunUnionWithAnonymousUnionField");
}

std::string VoidFunUnionWithAnonymousUnionFieldFactory::getFilename()
{
   return "voidFunUnionWithAnonymousUnionField.h";
}

std::string VoidFunUnionWithAnonymousUnionFieldFactory::getMatcherFunctionName()
{
  return "cmp_union_topAnonymousUnionField";
}

std::string VoidFunUnionWithAnonymousUnionFieldFactory::getFieldWrongName()
{
  return "u";
}

std::string VoidFunUnionWithAnonymousUnionFieldFactory::getSubFieldWrongName()
{
  /*
   * Even though the setupTestCase function modify s2, the field of the union
   * which will return an error is the first of the parent union. I.E: a
   */
  return "a";
}

std::string VoidFunUnionWithAnonymousUnionFieldFactory::getSubFieldWrongTypeName()
{
  /*
   * Even though the setupTestCase function modify s2, the field of the union
   * which will return an error is the first of the parent union.
   * I.E: we don't reach the subfield type
   */
  return "topAnonymousUnionField";
}

std::string VoidFunUnionWithAnonymousUnionFieldFactory::getSubComposableTypeType()
{
  return "n union";
}

void VoidFunUnionWithAnonymousUnionFieldFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  union topAnonymousUnionField aToExpect;

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
