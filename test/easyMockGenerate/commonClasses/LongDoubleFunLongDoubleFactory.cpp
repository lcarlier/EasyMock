#include <LongDoubleFunLongDoubleFactory.h>

Function LongDoubleFunLongDoubleFactory::functionFactory()
{
  Function f(functionGetFunctionName(), TypedReturnValue(CTYPE_LONG_DOUBLE),Parameter::Vector({NamedParameter(CTYPE_LONG_DOUBLE, "ld")}));
  return f;
}

Function* LongDoubleFunLongDoubleFactory::newFunctionFactory()
{
  return functionFactory().clone();
}


std::string LongDoubleFunLongDoubleFactory::functionGetFunctionName()
{
  return std::string("longDoubleFunLongDouble");
}

std::string LongDoubleFunLongDoubleFactory::getFilename()
{
   return "longDoubleFunLongDouble.h";
}

void LongDoubleFunLongDoubleFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  long double aToExpect = 13.123;
  long double rvToExpect = 17.456;
  aToExpect = -aToExpect;
  rvToExpect = -rvToExpect;
  switch(tc)
  {
    case EasyMockTestCase::OneExpect:
      m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(&cmp_long_double));
      break;
    case EasyMockTestCase::ThreeExpects:
    {
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_rv.push_back(rvToExpect + expectIdx);
        m_expects.push_back(std::make_tuple(aToExpect + expectIdx));
        m_params.push_back(std::make_tuple(aToExpect + expectIdx));
        m_compare.push_back(std::make_tuple(&cmp_long_double));
      }
      break;
    }
    case EasyMockTestCase::OneExpectArgIsBad:
      m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect + 1));
      m_compare.push_back(std::make_tuple(&cmp_long_double));
      break;
    case EasyMockTestCase::SecondExpectArgIsBad:
      m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(&cmp_long_double));

      m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect + 1)); //second call fails
      m_compare.push_back(std::make_tuple(&cmp_long_double));
      break;
    case EasyMockTestCase::NoExpect:
    case EasyMockTestCase::NotEnoughCall:
      break;
  }
}
