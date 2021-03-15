#include "StructAnonymousTypedDefFunStructAnonymousTypedDefFactory.hpp"

#include <StructType.h>
#include <ComposableField.h>
#include <TypedefType.h>

FunctionDeclaration StructAnonymousTypedDefFunStructAnonymousTypedDefFactory::functionFactory()
{
  bool isEmbeddedInOtherType = false;
  TypedefType *tst1 = new TypedefType("TypedDefAnonymousStruct", new StructType("", isEmbeddedInOtherType));
  StructType *st1 = dynamic_cast<StructType*>(tst1->getTypee());
  st1->addField(new ComposableField(CTYPE_INT, "a"));

  TypedefType *tst2 = new TypedefType("TypedDefAnonymousStruct2", new StructType("", isEmbeddedInOtherType));
  StructType *st2 = dynamic_cast<StructType*>(tst2->getTypee());
  st2->addField(new ComposableField(CTYPE_INT, "a"));

  TypeItf *rv = tst1->clone();

  FunctionDeclaration f(functionGetFunctionName(), ReturnValue(rv), Parameter::Vector({new Parameter(tst1, "s1"), new Parameter(tst2, "s2")}));

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
  TypedDefAnonymousStruct2 t2;
  t2.a = 43;
  switch(tc)
  {
    case EasyMockTestCase::OneExpect:
      m_rvContext.m_rv.push_back(t);
      m_expects.push_back(std::make_tuple(t, t2));
      m_params.push_back(std::make_tuple(t, t2));
      m_compare.push_back(std::make_tuple(nullptr, nullptr)); //Separate dedicated UT are written to test the generation and function of the comparators for structs
      break;
    case EasyMockTestCase::ThreeExpects:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(t);
        m_expects.push_back(std::make_tuple(t, t2));
        m_params.push_back(std::make_tuple(t, t2));
        m_compare.push_back(std::make_tuple(nullptr, nullptr)); //Separate dedicated UT are written to test the generation and function of the comparators for structs
      }
      break;
    case EasyMockTestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(t);
        m_expects.push_back(std::make_tuple(t, t2));
        m_params.push_back(std::make_tuple(t, t2));
        m_compare.push_back(std::make_tuple(nullptr, nullptr)); //Separate dedicated UT are written to test the generation and function of the comparators for structs
      }
      break;
    case EasyMockTestCase::OneExpectArgIsBad: //Not tested in a generic way
    case EasyMockTestCase::SecondExpectArgIsBad: //Not tested in a generic way
    case EasyMockTestCase::NoExpect:
      break;
  }
}
