#include "StructWithUnionFunStructWithUnionFactory.h"

#include <StructType.h>
#include <UnionType.h>
#include <ComposableField.h>
#include <TypedefType.h>

std::shared_ptr<FunctionDeclaration> StructWithUnionFunStructWithUnionFactory::functionFactory()
{
  auto getsWithUnion = []()
  {
    return std::make_shared<TypedefType>("sWithUnion", std::make_shared<StructType>("", false));
  };
  std::shared_ptr<TypedefType> tst = getsWithUnion();
  ComposableType *st = tst->getTypee()->asComposableType();
  auto ut = std::make_shared<UnionType>("ut", true);
  ut->addField(ComposableField(CTYPE_INT, "a"));
  ut->addField(ComposableField(CTYPE_FLOAT, "b"));
  st->addField(ComposableField(std::move(ut), "u"));

  Parameter::Vector pv{};
  pv.emplace_back(Parameter(tst, "st"));
  auto f = std::make_shared<FunctionDeclaration>(functionGetFunctionName(), ReturnValue(std::move(tst)), std::move(pv));
  return f;
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
    case EasyMockTestCase::TestCase::OneExpect:
      m_rvContext.m_rv.push_back(s);
      m_expects.push_back(std::make_tuple(s));
      m_params.push_back(std::make_tuple(s));
      m_compare.push_back(std::make_tuple(nullptr)); //Separate dedicated UT are written to test the generation and function of the comparators for structs
      break;
    case EasyMockTestCase::TestCase::ThreeExpects:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(s);
        m_expects.push_back(std::make_tuple(s));
        m_params.push_back(std::make_tuple(s));
        m_compare.push_back(std::make_tuple(nullptr)); //Separate dedicated UT are written to test the generation and function of the comparators for structs
      }
      break;
    case EasyMockTestCase::TestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(s);
        m_expects.push_back(std::make_tuple(s));
        m_params.push_back(std::make_tuple(s));
        m_compare.push_back(std::make_tuple(nullptr)); //Separate dedicated UT are written to test the generation and function of the comparators for structs
      }
      break;
    case EasyMockTestCase::TestCase::OneExpectArgIsBad: //Not tested in a generic way
    case EasyMockTestCase::TestCase::SecondExpectArgIsBad: //Not tested in a generic way
    case EasyMockTestCase::TestCase::NoExpect:
      break;
  }
}
