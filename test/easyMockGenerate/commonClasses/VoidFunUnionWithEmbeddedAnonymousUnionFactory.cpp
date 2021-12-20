#include <VoidFunUnionWithEmbeddedAnonymousUnionFactory.h>

#include <UnionType.h>
#include <ComposableField.h>

FunctionDeclaration VoidFunUnionWithEmbeddedAnonymousUnionFactory::functionFactory()
{
  bool isEmbeddedStruct = true;
  auto top = std::make_shared<UnionType>("topEmbeddedAnonymousUnion", !isEmbeddedStruct); //NOT EMBEDDED
  auto beingDefined = std::make_shared<UnionType>("", isEmbeddedStruct);
  beingDefined->addField(ComposableField(CTYPE_INT, "a"));
  beingDefined->addField(ComposableField(CTYPE_FLOAT, "b"));
  top->addField(ComposableField(std::move(beingDefined), "eau"));

  Parameter::Vector pv{};
  pv.emplace_back(Parameter(std::move(top), "u"));
  FunctionDeclaration f(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), std::move(pv));

  return f;
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
