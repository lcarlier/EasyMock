#include <UnsShortFunUnsShortFactory.h>

FunctionDeclaration UnsShortFunUnsShortFactory::functionFactory()
{
  Parameter::Vector pv{};
  pv.emplace_back(NamedParameter(CTYPE_USHORT, "s"));
  FunctionDeclaration f(functionGetFunctionName(), TypedReturnValue(CTYPE_USHORT), std::move(pv));
  return f;
}

std::string UnsShortFunUnsShortFactory::functionGetFunctionName()
{
  return std::string("unsShortFunUnsShort");
}

std::string UnsShortFunUnsShortFactory::getFilename()
{
   return "unsShortFunUnsShort.h";
}

void UnsShortFunUnsShortFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  unsigned short aToExpect = 0xcafe;
  unsigned short rvToExpect = 0xbabe;
  switch(tc)
  {
    case EasyMockTestCase::OneExpect:
      m_rvContext.m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(&cmp_u_short));
      break;
    case EasyMockTestCase::ThreeExpects:
    {
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(rvToExpect + expectIdx);
        m_expects.push_back(std::make_tuple(aToExpect + expectIdx));
        m_params.push_back(std::make_tuple(aToExpect + expectIdx));
        m_compare.push_back(std::make_tuple(&cmp_u_short));
      }
      break;
    }
    case EasyMockTestCase::OneExpectArgIsBad:
      m_rvContext.m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect + 1));
      m_compare.push_back(std::make_tuple(&cmp_u_short));
      break;
    case EasyMockTestCase::SecondExpectArgIsBad:
      m_rvContext.m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(&cmp_u_short));

      m_rvContext.m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect + 1)); //second call fails
      m_compare.push_back(std::make_tuple(&cmp_u_short));
      break;
    case EasyMockTestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(rvToExpect + expectIdx);
        m_expects.push_back(std::make_tuple(aToExpect + expectIdx));
        m_params.push_back(std::make_tuple(aToExpect + expectIdx));
        m_compare.push_back(std::make_tuple(&cmp_u_short));
      }
      break;
    case EasyMockTestCase::NoExpect:
      break;
  }
}
