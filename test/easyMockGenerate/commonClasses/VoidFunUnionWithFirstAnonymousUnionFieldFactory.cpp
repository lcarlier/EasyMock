#include <VoidFunUnionWithFirstAnonymousUnionFieldFactory.h>

#include <UnionType.h>
#include <ComposableField.h>

std::shared_ptr<FunctionDeclaration> VoidFunUnionWithFirstAnonymousUnionFieldFactory::functionFactory()
{
  bool isEmbeddedStruct = true;
  auto top = std::make_shared<UnionType>("topAnonymousFirstUnionField", !isEmbeddedStruct); //NOT EMBEDDED
  auto beingDefined = std::make_shared<UnionType>("", isEmbeddedStruct);
  beingDefined->addField(ComposableField(CTYPE_INT, "s1"));
  beingDefined->addField(ComposableField(CTYPE_FLOAT, "s2"));
  top->addField(ComposableField(std::move(beingDefined), ""));
  top->addField(ComposableField(CTYPE_INT, "a"));

  Parameter::Vector pv{};
  pv.emplace_back(Parameter(std::move(top), "u"));
  auto f = std::make_shared<FunctionDeclaration>(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), std::move(pv));

  return f;
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
