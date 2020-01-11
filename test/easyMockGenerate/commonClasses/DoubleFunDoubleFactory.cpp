#include <DoubleFunDoubleFactory.h>

Function DoubleFunDoubleFactory::functionFactory()
{
  Function f(functionGetFunctionName(), TypedReturnValue(CTYPE_DOUBLE),{NamedParameter(CTYPE_DOUBLE, "d")});
  return f;
}

Function* DoubleFunDoubleFactory::newFunctionFactory()
{
  return functionFactory().clone();
}


std::string DoubleFunDoubleFactory::functionGetFunctionName()
{
  return std::string("doubleFunDouble");
}

std::string DoubleFunDoubleFactory::getFilename()
{
   return "doubleFunDouble.h";
}

void DoubleFunDoubleFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  double aToExpect = 13.123;
  double rvToExpect = 17.456;
  aToExpect = -aToExpect;
  rvToExpect = -rvToExpect;
  switch(tc)
  {
    case EasyMockTestCase::OneExpect:
      m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(&cmp_double));
      break;
    case EasyMockTestCase::ThreeExpects:
    {
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_rv.push_back(rvToExpect + expectIdx);
        m_expects.push_back(std::make_tuple(aToExpect + expectIdx));
        m_params.push_back(std::make_tuple(aToExpect + expectIdx));
        m_compare.push_back(std::make_tuple(&cmp_double));
      }
      break;
    }
    case EasyMockTestCase::OneExpectArgIsBad:
      m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect + 1));
      m_compare.push_back(std::make_tuple(&cmp_double));
      break;
    case EasyMockTestCase::SecondExpectArgIsBad:
      m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(&cmp_double));

      m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect + 1)); //second call fails
      m_compare.push_back(std::make_tuple(&cmp_double));
      break;
    case EasyMockTestCase::NoExpect:
    case EasyMockTestCase::NotEnoughCall:
      break;
  }
}
