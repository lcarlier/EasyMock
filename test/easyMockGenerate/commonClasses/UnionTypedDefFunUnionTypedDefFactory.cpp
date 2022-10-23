#include <UnionTypedDefFunUnionTypedDefFactory.hpp>

#include <UnionType.h>
#include <ComposableField.h>
#include <TypedefType.h>

std::shared_ptr<FunctionDeclaration> UnionTypedDefFunUnionTypedDefFactory::functionFactory()
{
  auto getT_U = []()
  {
    bool isEmbeddedInOtherType = false;
    return std::make_shared<TypedefType>("t_u", std::make_shared<UnionType>("u", isEmbeddedInOtherType));
  };
  std::shared_ptr<TypedefType> tst1 = getT_U();
  ComposableType *st1 = tst1->getTypee()->asComposableType();
  st1->addField(ComposableField(CTYPE_INT, "a"));
  st1->addField(ComposableField(CTYPE_INT, "b"));

  Parameter::Vector pv{};
  pv.emplace_back(Parameter(tst1, "param"));
  auto f = std::make_shared<FunctionDeclaration>(functionGetFunctionName(), ReturnValue(std::move(tst1)), std::move(pv));
  return f;
}

std::string UnionTypedDefFunUnionTypedDefFactory::functionGetFunctionName()
{
  return "unionTypedDefFunUnionTypedDef";
}

std::string UnionTypedDefFunUnionTypedDefFactory::getFilename()
{
  return "unionTypedDefFunUnionTypedDef.h";
}

void UnionTypedDefFunUnionTypedDefFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  t_u t;
  t.a = 42;
  t.b = 84;
  switch(tc)
  {
    case EasyMockTestCase::TestCase::OneExpect:
      m_rvContext.m_rv.push_back(t);
      m_expects.push_back(std::make_tuple(t));
      m_params.push_back(std::make_tuple(t));
      m_compare.push_back(std::make_tuple(nullptr)); //Separate dedicated UT are written to test the generation and function of the comparators for structs
      break;
    case EasyMockTestCase::TestCase::ThreeExpects:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(t);
        m_expects.push_back(std::make_tuple(t));
        m_params.push_back(std::make_tuple(t));
        m_compare.push_back(std::make_tuple(nullptr)); //Separate dedicated UT are written to test the generation and function of the comparators for structs
      }
      break;
    case EasyMockTestCase::TestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(t);
        m_expects.push_back(std::make_tuple(t));
        m_params.push_back(std::make_tuple(t));
        m_compare.push_back(std::make_tuple(nullptr)); //Separate dedicated UT are written to test the generation and function of the comparators for structs
      }
      break;
    case EasyMockTestCase::TestCase::OneExpectArgIsBad: //Not tested in a generic way
    case EasyMockTestCase::TestCase::SecondExpectArgIsBad: //Not tested in a generic way
    case EasyMockTestCase::TestCase::NoExpect:
      break;
  }
}
