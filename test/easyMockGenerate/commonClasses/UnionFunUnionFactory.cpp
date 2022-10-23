#include <UnionFunUnionFactory.h>

#include <UnionType.h>
#include <ComposableField.h>

std::shared_ptr<FunctionDeclaration> UnionFunUnionFactory::functionFactory()
{
  bool isEmbeddedInOtherType = false;
  auto st1 = std::make_shared<UnionType>("u1", isEmbeddedInOtherType);
  st1->addField(ComposableField(CTYPE_INT, "a"));
  auto st2 = std::make_shared<UnionType>("u2", isEmbeddedInOtherType);
  st2->addField(ComposableField(CTYPE_INT, "b"));

  Parameter::Vector pv{};
  pv.emplace_back(Parameter(std::move(st2), "u"));
  auto f = std::make_shared<FunctionDeclaration>(functionGetFunctionName(), ReturnValue(std::move(st1)), std::move(pv));
  return f;
}

std::string UnionFunUnionFactory::functionGetFunctionName()
{
  return "unionFunUnion";
}

std::string UnionFunUnionFactory::getFilename()
{
  return "unionFunUnion.h";
}

void UnionFunUnionFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  union u1 t;
  t.a = 42;
  union u2 r;
  r.b = 84;
  switch(tc)
  {
    case EasyMockTestCase::TestCase::OneExpect:
      m_rvContext.m_rv.push_back(t);
      m_expects.push_back(std::make_tuple(r));
      m_params.push_back(std::make_tuple(r));
      m_compare.push_back(std::make_tuple(nullptr)); //Separate dedicated UT are written to test the generation and function of the comparators for structs
      break;
    case EasyMockTestCase::TestCase::ThreeExpects:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(t);
        m_expects.push_back(std::make_tuple(r));
        m_params.push_back(std::make_tuple(r));
        m_compare.push_back(std::make_tuple(nullptr)); //Separate dedicated UT are written to test the generation and function of the comparators for structs
      }
      break;
    case EasyMockTestCase::TestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(t);
        m_expects.push_back(std::make_tuple(r));
        m_params.push_back(std::make_tuple(r));
        m_compare.push_back(std::make_tuple(nullptr)); //Separate dedicated UT are written to test the generation and function of the comparators for structs
      }
      break;
    case EasyMockTestCase::TestCase::OneExpectArgIsBad: //Not tested in a generic way
    case EasyMockTestCase::TestCase::SecondExpectArgIsBad: //Not tested in a generic way
    case EasyMockTestCase::TestCase::NoExpect:
      break;
  }
}
