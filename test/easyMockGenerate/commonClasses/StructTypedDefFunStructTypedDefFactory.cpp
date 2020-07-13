#include "StructTypedDefFunStructTypedDefFactory.h"

#include <StructType.h>

Function StructTypedDefFunStructTypedDefFactory::functionFactory()
{
  bool isEmbeddedInOtherType = false;
  StructType *st1 = new StructType("foo", "TypedDefStruct", isEmbeddedInOtherType);
  st1->addField(new ComposableField(CTYPE_INT, "a"));
  StructType *rv = st1->clone();

  Function f(functionGetFunctionName(), ReturnValue(rv), Parameter::Vector({new Parameter(st1, "s2")}));
  return f;
}

std::string StructTypedDefFunStructTypedDefFactory::functionGetFunctionName()
{
  return "structTypedDefFunStructTypedDef";
}

std::string StructTypedDefFunStructTypedDefFactory::getFilename()
{
  return "structTypedDefFunStructTypedDef.h";
}

void StructTypedDefFunStructTypedDefFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  TypedDefStruct t;
  t.a = 42;
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
    case EasyMockTestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
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
      break;
  }
}
