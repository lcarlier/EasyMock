#include "StructWithUnionFunStructWithUnionFactory.h"

#include <StructType.h>
#include <UnionType.h>
#include <ComposableField.h>
#include <TypedefType.h>

FunctionDeclaration StructWithUnionFunStructWithUnionFactory::functionFactory()
{
  TypedefType *tst = new TypedefType("sWithUnion", new StructType("", false));
  StructType *st = dynamic_cast<StructType*>(tst->getTypee());
  UnionType *ut = new UnionType("ut", true);
  ut->addField(new ComposableField(CTYPE_INT, "a"));
  ut->addField(new ComposableField(CTYPE_FLOAT, "b"));
  st->addField(new ComposableField(ut, "u"));
  TypeItf *rv = tst->clone();
  FunctionDeclaration f(functionGetFunctionName(), ReturnValue(rv), Parameter::Vector({new Parameter(tst, "st")}));
  return f;
}

FunctionDeclaration* StructWithUnionFunStructWithUnionFactory::newFunctionFactory()
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
      m_rvContext.m_rv.push_back(s);
      m_expects.push_back(std::make_tuple(s));
      m_params.push_back(std::make_tuple(s));
      m_compare.push_back(std::make_tuple(nullptr)); //Separate dedicated UT are written to test the generation and function of the comparators for structs
      break;
    case EasyMockTestCase::ThreeExpects:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(s);
        m_expects.push_back(std::make_tuple(s));
        m_params.push_back(std::make_tuple(s));
        m_compare.push_back(std::make_tuple(nullptr)); //Separate dedicated UT are written to test the generation and function of the comparators for structs
      }
      break;
    case EasyMockTestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(s);
        m_expects.push_back(std::make_tuple(s));
        m_params.push_back(std::make_tuple(s));
        m_compare.push_back(std::make_tuple(nullptr)); //Separate dedicated UT are written to test the generation and function of the comparators for structs
      }
      break;
    case EasyMockTestCase::OneExpectArgIsBad: //Not tested in a generic way
    case EasyMockTestCase::SecondExpectArgIsBad: //Not tested in a generic way
    case EasyMockTestCase::NoExpect:
      break;
  }
}
