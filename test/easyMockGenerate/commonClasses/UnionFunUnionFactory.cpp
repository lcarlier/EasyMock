#include <UnionFunUnionFactory.h>

#include <UnionType.h>
#include <ComposableField.h>

FunctionDeclaration UnionFunUnionFactory::functionFactory()
{
  bool isEmbeddedInOtherType = false;
  UnionType *st1 = new UnionType("u1", isEmbeddedInOtherType);
  st1->addField(new ComposableField(CTYPE_INT, "a"));
  UnionType *st2 = new UnionType("u2", isEmbeddedInOtherType);
  st2->addField(new ComposableField(CTYPE_INT, "b"));

  FunctionDeclaration f(functionGetFunctionName(), ReturnValue(st1), Parameter::Vector({new Parameter(st2, "u")}));
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
    case EasyMockTestCase::OneExpect:
      m_rvContext.m_rv.push_back(t);
      m_expects.push_back(std::make_tuple(r));
      m_params.push_back(std::make_tuple(r));
      m_compare.push_back(std::make_tuple(nullptr)); //Separate dedicated UT are written to test the generation and function of the comparators for structs
      break;
    case EasyMockTestCase::ThreeExpects:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(t);
        m_expects.push_back(std::make_tuple(r));
        m_params.push_back(std::make_tuple(r));
        m_compare.push_back(std::make_tuple(nullptr)); //Separate dedicated UT are written to test the generation and function of the comparators for structs
      }
      break;
    case EasyMockTestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(t);
        m_expects.push_back(std::make_tuple(r));
        m_params.push_back(std::make_tuple(r));
        m_compare.push_back(std::make_tuple(nullptr)); //Separate dedicated UT are written to test the generation and function of the comparators for structs
      }
      break;
    case EasyMockTestCase::OneExpectArgIsBad: //Not tested in a generic way
    case EasyMockTestCase::SecondExpectArgIsBad: //Not tested in a generic way
    case EasyMockTestCase::NoExpect:
      break;
  }
}
