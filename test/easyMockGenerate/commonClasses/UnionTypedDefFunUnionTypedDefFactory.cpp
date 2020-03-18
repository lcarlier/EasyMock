#include <UnionTypedDefFunUnionTypedDefFactory.hpp>

#include <UnionType.h>

Function UnionTypedDefFunUnionTypedDefFactory::functionFactory()
{
  UnionType *st1 = new UnionType("u", "t_u");
  st1->addStructField(new ComposableField(CTYPE_INT, "a"));
  st1->addStructField(new ComposableField(CTYPE_INT, "b"));
  UnionType *rv = st1->clone();

  Function f(functionGetFunctionName(), ReturnValue(rv), {new Parameter(st1, "s2")});
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
    case EasyMockTestCase::OneExpect:
      m_rv.push_back(t);
      m_expects.push_back(std::make_tuple(t));
      m_params.push_back(std::make_tuple(t));
      m_compare.push_back(std::make_tuple(nullptr)); //Seperate dedicated UT are writen to test the generation and function of the comparators for structs
      break;
    case EasyMockTestCase::ThreeExpects:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_rv.push_back(t);
        m_expects.push_back(std::make_tuple(t));
        m_params.push_back(std::make_tuple(t));
        m_compare.push_back(std::make_tuple(nullptr)); //Seperate dedicated UT are writen to test the generation and function of the comparators for structs
      }
      break;
    case EasyMockTestCase::OneExpectArgIsBad: //Not tested in a generic way
    case EasyMockTestCase::SecondExpectArgIsBad: //Not tested in a generic way
    case EasyMockTestCase::NoExpect:
    case EasyMockTestCase::NotEnoughCall:
      break;
  }
}
