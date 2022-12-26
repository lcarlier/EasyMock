#include <ShortFunShortFactory.h>

#include "EasyMockGenerateTypes.h"

std::shared_ptr<FunctionDeclaration> ShortFunShortFactory::functionFactory()
{
  Parameter::Vector pv{};
  pv.emplace_back(NamedParameter(CTYPE_SHORT, "s"));
  auto f = std::make_shared<FunctionDeclaration>(functionGetFunctionName(), TypedReturnValue(CTYPE_SHORT), std::move(pv));
  return f;
}

std::string ShortFunShortFactory::functionGetFunctionName()
{
  return std::string("shortFunShort");
}

std::string ShortFunShortFactory::getFilename()
{
   return "shortFunShort.h";
}

void ShortFunShortFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  short aToExpect = -5;
  short rvToExpect = -7;
  switch(tc)
  {
    case EasyMockTestCase::TestCase::OneExpect:
      m_rvContext.m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(&cmp_short));
      break;
    case EasyMockTestCase::TestCase::ThreeExpects:
    {
      short nbThreeExpects = EasyMockTestCase::ThreeExpects_NbExpects;
      for(short expectIdx = 0; expectIdx < nbThreeExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(rvToExpect + expectIdx);
        m_expects.push_back(std::make_tuple(aToExpect + expectIdx));
        m_params.push_back(std::make_tuple(aToExpect + expectIdx));
        m_compare.push_back(std::make_tuple(&cmp_short));
      }
      break;
    }
    case EasyMockTestCase::TestCase::OneExpectArgIsBad:
      m_rvContext.m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect + 1));
      m_compare.push_back(std::make_tuple(&cmp_short));
      break;
    case EasyMockTestCase::TestCase::SecondExpectArgIsBad:
      m_rvContext.m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(&cmp_short));

      m_rvContext.m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect + 1)); //second call fails
      m_compare.push_back(std::make_tuple(&cmp_short));
      break;
    case EasyMockTestCase::TestCase::NotEnoughCall:
    {
      short nbNotEnoughCallExpects = EasyMockTestCase::ThreeExpects_NbExpects;
      for (short expectIdx = 0; expectIdx < nbNotEnoughCallExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(rvToExpect + expectIdx);
        m_expects.push_back(std::make_tuple(aToExpect + expectIdx));
        m_params.push_back(std::make_tuple(aToExpect + expectIdx));
        m_compare.push_back(std::make_tuple(&cmp_short));
      }
      break;
    }
    case EasyMockTestCase::TestCase::NoExpect:
      break;
  }
}
