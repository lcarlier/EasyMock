#include <UnionAnonymousTypedDefFunUnionAnonymousTypedDefFactory.h>

#include <UnionType.h>
#include <ComposableField.h>
#include <TypedefType.h>

std::shared_ptr<FunctionDeclaration> UnionAnonymousTypedDefFunUnionAnonymousTypedDefFactory::functionFactory()
{
  auto getTypedDefAnonymousUnion = []()
  {
    bool isEmbeddedInOtherType = false;
    return std::make_shared<TypedefType>("TypedDefAnonymousUnion", std::make_shared<UnionType>("", isEmbeddedInOtherType));
  };
  std::shared_ptr<TypedefType> tst1 = getTypedDefAnonymousUnion();
  ComposableType *st1 = tst1->getTypee()->asComposableType();
  st1->addField(ComposableField(CTYPE_INT, "a"));
  st1->addField(ComposableField(CTYPE_INT, "b"));

  Parameter::Vector pv{};
  pv.emplace_back(Parameter(tst1, "u"));
  auto f = std::make_shared<FunctionDeclaration>(functionGetFunctionName(), ReturnValue(std::move(tst1)), std::move(pv));
  return f;
}

std::string UnionAnonymousTypedDefFunUnionAnonymousTypedDefFactory::functionGetFunctionName()
{
  return "unionAnonymousTypedDefFunUnionAnonymousTypedDef";
}

std::string UnionAnonymousTypedDefFunUnionAnonymousTypedDefFactory::getFilename()
{
  return "unionAnonymousTypedDefFunUnionAnonymousTypedDef.h";
}

void UnionAnonymousTypedDefFunUnionAnonymousTypedDefFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  TypedDefAnonymousUnion t;
  t.a = 42;
  t.b = 84;
  switch(tc)
  {
    case EasyMockTestCase::TestCase::OneExpect:
      m_rvContext.m_rv.push_back(t);
      m_expects.push_back(std::make_tuple(t));
      m_params.push_back(std::make_tuple(t));
      m_compare.push_back(std::make_tuple(nullptr)); //Seperate dedicated UT are writen to test the generation and function of the comparators for structs
      break;
    case EasyMockTestCase::TestCase::ThreeExpects:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(t);
        m_expects.push_back(std::make_tuple(t));
        m_params.push_back(std::make_tuple(t));
        m_compare.push_back(std::make_tuple(nullptr)); //Seperate dedicated UT are writen to test the generation and function of the comparators for structs
      }
      break;
    case EasyMockTestCase::TestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(t);
        m_expects.push_back(std::make_tuple(t));
        m_params.push_back(std::make_tuple(t));
        m_compare.push_back(std::make_tuple(nullptr)); //Seperate dedicated UT are writen to test the generation and function of the comparators for structs
      }
      break;
    case EasyMockTestCase::TestCase::OneExpectArgIsBad: //Not tested in a generic way
    case EasyMockTestCase::TestCase::SecondExpectArgIsBad: //Not tested in a generic way
    case EasyMockTestCase::TestCase::NoExpect:
      break;
  }
}
