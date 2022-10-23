#include "StructTypedDefFunStructTypedDefFactory.h"

#include <StructType.h>
#include <ComposableField.h>
#include <TypedefType.h>

std::shared_ptr<FunctionDeclaration> StructTypedDefFunStructTypedDefFactory::functionFactory()
{
  auto getCommonAField= []()
  {
    return ComposableField(CTYPE_INT, "a");
  };
  bool isEmbeddedInOtherType = false;
  auto st1 = std::make_shared<StructType>("foo", isEmbeddedInOtherType);
  st1->addField(getCommonAField());

  auto trv = std::make_shared<TypedefType>("TypedDefStruct", std::make_shared<StructType>("foo", isEmbeddedInOtherType));
  StructType *rv = dynamic_cast<StructType*>(trv->getTypee());
  rv->addField(getCommonAField());

  Parameter::Vector pv{};
  pv.emplace_back(Parameter(std::move(st1), "s2"));
  auto f = std::make_shared<FunctionDeclaration>(functionGetFunctionName(), ReturnValue(std::move(trv)), std::move(pv));
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
    case EasyMockTestCase::TestCase::OneExpect:
      m_rvContext.m_rv.push_back(t);
      m_expects.push_back(std::make_tuple(t));
      m_params.push_back(std::make_tuple(t));
      m_compare.push_back(std::make_tuple(nullptr)); //Seperate dedicated UT are writen to test the generation and function of the comparators for structs
      break;
    case EasyMockTestCase::TestCase::ThreeExpects:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(t);
        m_expects.push_back(std::make_tuple(t));
        m_params.push_back(std::make_tuple(t));
        m_compare.push_back(std::make_tuple(nullptr)); //Seperate dedicated UT are writen to test the generation and function of the comparators for structs
      }
      break;
    case EasyMockTestCase::TestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(t);
        m_expects.push_back(std::make_tuple(t));
        m_params.push_back(std::make_tuple(t));
        m_compare.push_back(std::make_tuple(nullptr)); //Seperate dedicated UT are writen to test the generation and function of the comparators for structs
      }
      break;
    case EasyMockTestCase::TestCase::OneExpectArgIsBad: //Not tested in a generic way
    case EasyMockTestCase::TestCase::SecondExpectArgIsBad: //Not tested in a generic way
    case EasyMockTestCase::TestCase::NoExpect:
      break;
  }
}
