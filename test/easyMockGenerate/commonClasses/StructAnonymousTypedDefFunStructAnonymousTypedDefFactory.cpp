#include "StructAnonymousTypedDefFunStructAnonymousTypedDefFactory.hpp"

#include <StructType.h>
#include <ComposableField.h>
#include <TypedefType.h>

std::shared_ptr<FunctionDeclaration> StructAnonymousTypedDefFunStructAnonymousTypedDefFactory::functionFactory()
{
  auto getTypedDefAnonymousStruct= []()
  {
    bool isEmbeddedInOtherType = false;
    return std::make_shared<TypedefType>("TypedDefAnonymousStruct", std::make_shared<StructType>("", isEmbeddedInOtherType));
  };
  bool isEmbeddedInOtherType = false;
  std::shared_ptr<TypedefType> tst1 =getTypedDefAnonymousStruct();
  ComposableType* st1 = tst1->getTypee()->asComposableType();
  st1->addField(ComposableField(CTYPE_INT, "a"));

  auto tst2 = std::make_shared<TypedefType>("TypedDefAnonymousStruct2", std::make_shared<StructType>("", isEmbeddedInOtherType));
  ComposableType *st2 = tst2->getTypee()->asComposableType();
  st2->addField(ComposableField(CTYPE_INT, "a"));

  Parameter::Vector pv{};
  pv.emplace_back(Parameter(tst1, "s1"));
  pv.emplace_back(Parameter(std::move(tst2), "s2"));
  auto f = std::make_shared<FunctionDeclaration>(functionGetFunctionName(), ReturnValue(std::move(tst1)), std::move(pv));

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
    case EasyMockTestCase::TestCase::OneExpect:
      m_rvContext.m_rv.push_back(t);
      m_expects.push_back(std::make_tuple(t, t2));
      m_params.push_back(std::make_tuple(t, t2));
      m_compare.push_back(std::make_tuple(nullptr, nullptr)); //Separate dedicated UT are written to test the generation and function of the comparators for structs
      break;
    case EasyMockTestCase::TestCase::ThreeExpects:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(t);
        m_expects.push_back(std::make_tuple(t, t2));
        m_params.push_back(std::make_tuple(t, t2));
        m_compare.push_back(std::make_tuple(nullptr, nullptr)); //Separate dedicated UT are written to test the generation and function of the comparators for structs
      }
      break;
    case EasyMockTestCase::TestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(t);
        m_expects.push_back(std::make_tuple(t, t2));
        m_params.push_back(std::make_tuple(t, t2));
        m_compare.push_back(std::make_tuple(nullptr, nullptr)); //Separate dedicated UT are written to test the generation and function of the comparators for structs
      }
      break;
    case EasyMockTestCase::TestCase::OneExpectArgIsBad: //Not tested in a generic way
    case EasyMockTestCase::TestCase::SecondExpectArgIsBad: //Not tested in a generic way
    case EasyMockTestCase::TestCase::NoExpect:
      break;
  }
}
