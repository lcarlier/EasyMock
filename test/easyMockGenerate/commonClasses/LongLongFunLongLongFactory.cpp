#include <LongLongFunLongLongFactory.h>

Function LongLongFunLongLongFactory::functionFactory()
{
  Function f(functionGetFunctionName(), TypedReturnValue(CTYPE_LONG_LONG),{NamedParameter(CTYPE_LONG_LONG, "ll")});
  return f;
}

Function* LongLongFunLongLongFactory::newFunctionFactory()
{
  return functionFactory().clone();
}


std::string LongLongFunLongLongFactory::functionGetFunctionName()
{
  return std::string("longLongFunLongLong");
}

std::string LongLongFunLongLongFactory::getFilename()
{
   return "longLongFunLongLong.h";
}

void LongLongFunLongLongFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  long long aToExpect = std::numeric_limits<long long>::max() - 42;
  long long rvToExpect = std::numeric_limits<long long>::max() - 84;
  aToExpect = -aToExpect;
  rvToExpect = -rvToExpect;
  switch(tc)
  {
    case EasyMockTestCase::OneExpect:
      m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(&cmp_long_long));
      break;
    case EasyMockTestCase::ThreeExpects:
    {
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_rv.push_back(rvToExpect + expectIdx);
        m_expects.push_back(std::make_tuple(aToExpect + expectIdx));
        m_params.push_back(std::make_tuple(aToExpect + expectIdx));
        m_compare.push_back(std::make_tuple(&cmp_long_long));
      }
      break;
    }
    case EasyMockTestCase::OneExpectArgIsBad:
      m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect + 1));
      m_compare.push_back(std::make_tuple(&cmp_long_long));
      break;
    case EasyMockTestCase::SecondExpectArgIsBad:
      m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(&cmp_long_long));

      m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect + 1)); //second call fails
      m_compare.push_back(std::make_tuple(&cmp_long_long));
      break;
    case EasyMockTestCase::NoExpect:
    case EasyMockTestCase::NotEnoughCall:
      break;
  }
}
