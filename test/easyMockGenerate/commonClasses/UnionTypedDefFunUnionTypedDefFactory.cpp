#include <UnionTypedDefFunUnionTypedDefFactory.hpp>

#include <UnionType.h>
#include <ComposableField.h>
#include <TypedefType.h>

FunctionDeclaration UnionTypedDefFunUnionTypedDefFactory::functionFactory()
{
  bool isEmbeddedInOtherType = false;
  TypedefType *tst1 = new TypedefType("t_u", new UnionType("u", isEmbeddedInOtherType));
  UnionType *st1 = dynamic_cast<UnionType*>(tst1->getTypee());
  st1->addField(new ComposableField(CTYPE_INT, "a"));
  st1->addField(new ComposableField(CTYPE_INT, "b"));
  TypeItf *rv = tst1->clone();

  FunctionDeclaration f(functionGetFunctionName(), ReturnValue(rv), Parameter::Vector({new Parameter(tst1, "param")}));
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
      m_rvContext.m_rv.push_back(t);
      m_expects.push_back(std::make_tuple(t));
      m_params.push_back(std::make_tuple(t));
      m_compare.push_back(std::make_tuple(nullptr)); //Separate dedicated UT are written to test the generation and function of the comparators for structs
      break;
    case EasyMockTestCase::ThreeExpects:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(t);
        m_expects.push_back(std::make_tuple(t));
        m_params.push_back(std::make_tuple(t));
        m_compare.push_back(std::make_tuple(nullptr)); //Separate dedicated UT are written to test the generation and function of the comparators for structs
      }
      break;
    case EasyMockTestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(t);
        m_expects.push_back(std::make_tuple(t));
        m_params.push_back(std::make_tuple(t));
        m_compare.push_back(std::make_tuple(nullptr)); //Separate dedicated UT are written to test the generation and function of the comparators for structs
      }
      break;
    case EasyMockTestCase::OneExpectArgIsBad: //Not tested in a generic way
    case EasyMockTestCase::SecondExpectArgIsBad: //Not tested in a generic way
    case EasyMockTestCase::NoExpect:
      break;
  }
}
