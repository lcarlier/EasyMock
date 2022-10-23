#include <VoidFunUnionWithEmbeddedUnionFactory.h>

#include <UnionType.h>
#include<ComposableField.h>

std::shared_ptr<FunctionDeclaration> VoidFunUnionWithEmbeddedUnionFactory::functionFactory()
{
  bool isEmbeddedStruct = true;
  auto top = std::make_shared<UnionType>("topEmbeddedUnion", !isEmbeddedStruct); //NOT EMBEDDED
  auto beingDefined = std::make_shared<UnionType>("embeddedUnion", isEmbeddedStruct);
  beingDefined->addField(ComposableField(CTYPE_INT, "a"));
  beingDefined->addField(ComposableField(CTYPE_FLOAT, "b"));
  top->addField(ComposableField(std::move(beingDefined), "eu"));

  Parameter::Vector pv{};
  pv.emplace_back(Parameter(std::move(top), "u"));
  auto f = std::make_shared<FunctionDeclaration>(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), std::move(pv));
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
    case EasyMockTestCase::TestCase::OneExpect:
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(m_user_matcher));
      break;
    case EasyMockTestCase::TestCase::OneExpectArgIsBad:
      m_expects.push_back(std::make_tuple(aToExpect));
      aToExpect.eu.a++;
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(m_user_matcher));
      break;
    case EasyMockTestCase::TestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_expects.push_back(std::make_tuple(aToExpect));
        m_params.push_back(std::make_tuple(aToExpect));
        m_compare.push_back(std::make_tuple(m_user_matcher));
      }
      break;
    case EasyMockTestCase::TestCase::ThreeExpects:
    case EasyMockTestCase::TestCase::SecondExpectArgIsBad:
    case EasyMockTestCase::TestCase::NoExpect:
      break;
  }
}
