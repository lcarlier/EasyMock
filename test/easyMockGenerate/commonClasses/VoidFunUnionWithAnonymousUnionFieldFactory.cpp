#include <VoidFunUnionWithAnonymousUnionFieldFactory.h>

#include <UnionType.h>
#include <ComposableField.h>

std::shared_ptr<FunctionDeclaration> VoidFunUnionWithAnonymousUnionFieldFactory::functionFactory()
{
  bool isEmbeddedStruct = true;
  auto top = std::make_shared<UnionType>("topAnonymousUnionField", !isEmbeddedStruct); //NOT EMBEDDED
  top->addField(ComposableField(CTYPE_INT, "a"));
  auto beingDefined = std::make_shared<UnionType>("", isEmbeddedStruct);
  beingDefined->addField(ComposableField(CTYPE_INT, "s1"));
  beingDefined->addField(ComposableField(CTYPE_FLOAT, "s2"));
  top->addField(ComposableField(std::move(beingDefined), ""));

  Parameter::Vector pv{};
  pv.emplace_back(Parameter(std::move(top), "u"));
  auto f = std::make_shared<FunctionDeclaration>(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), std::move(pv));

  return f;
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
