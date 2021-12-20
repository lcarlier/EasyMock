#include <VoidFunUnionWithEmbeddedUnionFactory.h>

#include <UnionType.h>
#include<ComposableField.h>

FunctionDeclaration VoidFunUnionWithEmbeddedUnionFactory::functionFactory()
{
  bool isEmbeddedStruct = true;
  auto top = std::make_shared<UnionType>("topEmbeddedUnion", !isEmbeddedStruct); //NOT EMBEDDED
  auto beingDefined = std::make_shared<UnionType>("embeddedUnion", isEmbeddedStruct);
  beingDefined->addField(ComposableField(CTYPE_INT, "a"));
  beingDefined->addField(ComposableField(CTYPE_FLOAT, "b"));
  top->addField(ComposableField(std::move(beingDefined), "eu"));

  Parameter::Vector pv{};
  pv.emplace_back(Parameter(std::move(top), "u"));
  FunctionDeclaration f(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), std::move(pv));
  return f;
}

std::string VoidFunUnionWithEmbeddedUnionFactory::functionGetFunctionName()
{
  return std::string("voidFunUnionWithEmbeddedUnion");
}

std::string VoidFunUnionWithEmbeddedUnionFactory::getFilename()
{
   return "voidFunUnionWithEmbeddedUnion.h";
}

std::string VoidFunUnionWithEmbeddedUnionFactory::getMatcherFunctionName()
{
  return "cmp_union_topEmbeddedUnion";
}

std::string VoidFunUnionWithEmbeddedUnionFactory::getFieldWrongName()
{
  return "u.eu";
}

std::string VoidFunUnionWithEmbeddedUnionFactory::getSubFieldWrongName()
{
  return "a";
}

std::string VoidFunUnionWithEmbeddedUnionFactory::getSubFieldWrongTypeName()
{
  return "topEmbeddedUnion::embeddedUnion";
}

std::string VoidFunUnionWithEmbeddedUnionFactory::getSubComposableTypeType()
{
  return "n union";
}

void VoidFunUnionWithEmbeddedUnionFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  union topEmbeddedUnion aToExpect;

  aToExpect.eu.a = 42;
  switch(tc)
  {
    case EasyMockTestCase::OneExpect:
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(m_user_matcher));
      break;
    case EasyMockTestCase::OneExpectArgIsBad:
      m_expects.push_back(std::make_tuple(aToExpect));
      aToExpect.eu.a++;
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(m_user_matcher));
      break;
    case EasyMockTestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_expects.push_back(std::make_tuple(aToExpect));
        m_params.push_back(std::make_tuple(aToExpect));
        m_compare.push_back(std::make_tuple(m_user_matcher));
      }
      break;
    case EasyMockTestCase::ThreeExpects:
    case EasyMockTestCase::SecondExpectArgIsBad:
    case EasyMockTestCase::NoExpect:
      break;
  }
}
