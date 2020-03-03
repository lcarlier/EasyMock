#include "StructAnonymousTypedDefFunStructAnonymousTypedDefFactory.hpp"

#include <StructType.h>

Function StructAnonymousTypedDefFunStructAnonymousTypedDefFactory::functionFactory()
{
  StructType *st1 = new StructType("", "TypedDefAnonymousStruct");
  st1->addStructField(new StructField(CTYPE_INT, "a"));
  StructType *rv = st1->clone();

  Function f(functionGetFunctionName(), ReturnValue(rv), {new Parameter(st1, "s1")});
  return f;
}

std::string StructAnonymousTypedDefFunStructAnonymousTypedDefFactory::functionGetFunctionName()
{
  return "structAnonymousTypedDefFunStructAnonymousTypedDef";
}

std::string StructAnonymousTypedDefFunStructAnonymousTypedDefFactory::getFilename()
{
  return "structAnonymousTypedDefFunStructAnonymousTypedDef.h";
}

void StructAnonymousTypedDefFunStructAnonymousTypedDefFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  TypedDefAnonymousStruct t;
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
    case EasyMockTestCase::OneExpectArgIsBad: //Not tested in a generic way
    case EasyMockTestCase::SecondExpectArgIsBad: //Not tested in a generic way
    case EasyMockTestCase::NoExpect:
    case EasyMockTestCase::NotEnoughCall:
      break;
  }
}
