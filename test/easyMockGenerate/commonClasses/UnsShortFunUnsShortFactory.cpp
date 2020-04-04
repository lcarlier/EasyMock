#include <UnsShortFunUnsShortFactory.h>

Function UnsShortFunUnsShortFactory::functionFactory()
{
  Function f(functionGetFunctionName(), TypedReturnValue(CTYPE_USHORT), Parameter::Vector({NamedParameter(CTYPE_USHORT, "s")}));
  return f;
}

Function* UnsShortFunUnsShortFactory::newFunctionFactory()
{
  return functionFactory().clone();
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
      m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(&cmp_u_short));
      break;
    case EasyMockTestCase::ThreeExpects:
    {
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_rv.push_back(rvToExpect + expectIdx);
        m_expects.push_back(std::make_tuple(aToExpect + expectIdx));
        m_params.push_back(std::make_tuple(aToExpect + expectIdx));
        m_compare.push_back(std::make_tuple(&cmp_u_short));
      }
      break;
    }
    case EasyMockTestCase::OneExpectArgIsBad:
      m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect + 1));
      m_compare.push_back(std::make_tuple(&cmp_u_short));
      break;
    case EasyMockTestCase::SecondExpectArgIsBad:
      m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(&cmp_u_short));

      m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect + 1)); //second call fails
      m_compare.push_back(std::make_tuple(&cmp_u_short));
      break;
    case EasyMockTestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_rv.push_back(rvToExpect + expectIdx);
        m_expects.push_back(std::make_tuple(aToExpect + expectIdx));
        m_params.push_back(std::make_tuple(aToExpect + expectIdx));
        m_compare.push_back(std::make_tuple(&cmp_u_short));
      }
      break;
    case EasyMockTestCase::NoExpect:
      break;
  }
}
