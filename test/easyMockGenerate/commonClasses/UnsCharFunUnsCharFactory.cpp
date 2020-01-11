#include <UnsCharFunUnsCharFactory.h>

Function UnsCharFunUnsCharFactory::functionFactory()
{
  Function f(functionGetFunctionName(), TypedReturnValue(CTYPE_UCHAR),{NamedParameter(CTYPE_UCHAR, "uc")});
  return f;
}

Function* UnsCharFunUnsCharFactory::newFunctionFactory()
{
  return functionFactory().clone();
}


std::string UnsCharFunUnsCharFactory::functionGetFunctionName()
{
  return std::string("unsCharFunUnsChar");
}

std::string UnsCharFunUnsCharFactory::getFilename()
{
   return "unsCharFunUnsChar.h";
}

void UnsCharFunUnsCharFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  unsigned char aToExpect = 0xca;
  unsigned char rvToExpect = 0xfe;
  switch(tc)
  {
    case EasyMockTestCase::OneExpect:
      m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(&cmp_u_char));
      break;
    case EasyMockTestCase::ThreeExpects:
    {
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_rv.push_back(rvToExpect + expectIdx);
        m_expects.push_back(std::make_tuple(aToExpect + expectIdx));
        m_params.push_back(std::make_tuple(aToExpect + expectIdx));
        m_compare.push_back(std::make_tuple(&cmp_u_char));
      }
      break;
    }
    case EasyMockTestCase::OneExpectArgIsBad:
      m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect + 1));
      m_compare.push_back(std::make_tuple(&cmp_u_char));
      break;
    case EasyMockTestCase::SecondExpectArgIsBad:
      m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(&cmp_u_char));

      m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect + 1)); //second call fails
      m_compare.push_back(std::make_tuple(&cmp_u_char));
      break;
    case EasyMockTestCase::NoExpect:
    case EasyMockTestCase::NotEnoughCall:
      break;
  }
}
