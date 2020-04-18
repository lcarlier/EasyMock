#include "StructWithUnionFunStructWithUnionFactory.h"

#include <StructType.h>
#include <UnionType.h>

Function StructWithUnionFunStructWithUnionFactory::functionFactory()
{
  StructType *st = new StructType("", "sWithUnion", false);
  UnionType *ut = new UnionType("ut", "", true);
  ut->addStructField(new ComposableField(CTYPE_INT, "a"));
  ut->addStructField(new ComposableField(CTYPE_FLOAT, "b"));
  st->addStructField(new ComposableField(ut, "u"));
  StructType *rv = st->clone();
  Function f(functionGetFunctionName(), ReturnValue(rv), Parameter::Vector({new Parameter(st, "st")}));
  return f;
}

Function* StructWithUnionFunStructWithUnionFactory::newFunctionFactory()
{
  return functionFactory().clone();
}

std::string StructWithUnionFunStructWithUnionFactory::functionGetFunctionName()
{
  return std::string("structWithUnionFunStructWithUnion");
}

std::string StructWithUnionFunStructWithUnionFactory::getFilename()
{
  return "structWithUnionFunStructWithUnion.h";
}

void StructWithUnionFunStructWithUnionFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  sWithUnion s;
  s.u.a = 42;
  switch(tc)
  {
    case EasyMockTestCase::OneExpect:
      m_rv.push_back(s);
      m_expects.push_back(std::make_tuple(s));
      m_params.push_back(std::make_tuple(s));
      m_compare.push_back(std::make_tuple(nullptr)); //Seperate dedicated UT are writen to test the generation and function of the comparators for structs
      break;
    case EasyMockTestCase::ThreeExpects:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_rv.push_back(s);
        m_expects.push_back(std::make_tuple(s));
        m_params.push_back(std::make_tuple(s));
        m_compare.push_back(std::make_tuple(nullptr)); //Seperate dedicated UT are writen to test the generation and function of the comparators for structs
      }
      break;
    case EasyMockTestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_rv.push_back(s);
        m_expects.push_back(std::make_tuple(s));
        m_params.push_back(std::make_tuple(s));
        m_compare.push_back(std::make_tuple(nullptr)); //Seperate dedicated UT are writen to test the generation and function of the comparators for structs
      }
      break;
    case EasyMockTestCase::OneExpectArgIsBad: //Not tested in a generic way
    case EasyMockTestCase::SecondExpectArgIsBad: //Not tested in a generic way
    case EasyMockTestCase::NoExpect:
      break;
  }
}