#include <LongLongFunLongLongFactory.h>

FunctionDeclaration LongLongFunLongLongFactory::functionFactory()
{
  FunctionDeclaration f(functionGetFunctionName(), TypedReturnValue(CTYPE_LONG_LONG), Parameter::Vector({NamedParameter(CTYPE_LONG_LONG, "ll")}));
  return f;
}

FunctionDeclaration* LongLongFunLongLongFactory::newFunctionFactory()
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
      m_rvContext.m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(&cmp_long_long));
      break;
    case EasyMockTestCase::ThreeExpects:
    {
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(rvToExpect + expectIdx);
        m_expects.push_back(std::make_tuple(aToExpect + expectIdx));
        m_params.push_back(std::make_tuple(aToExpect + expectIdx));
        m_compare.push_back(std::make_tuple(&cmp_long_long));
      }
      break;
    }
    case EasyMockTestCase::OneExpectArgIsBad:
      m_rvContext.m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect + 1));
      m_compare.push_back(std::make_tuple(&cmp_long_long));
      break;
    case EasyMockTestCase::SecondExpectArgIsBad:
      m_rvContext.m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(&cmp_long_long));

      m_rvContext.m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect + 1)); //second call fails
      m_compare.push_back(std::make_tuple(&cmp_long_long));
      break;
    case EasyMockTestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(rvToExpect + expectIdx);
        m_expects.push_back(std::make_tuple(aToExpect + expectIdx));
        m_params.push_back(std::make_tuple(aToExpect + expectIdx));
        m_compare.push_back(std::make_tuple(&cmp_long_long));
      }
      break;
    case EasyMockTestCase::NoExpect:
      break;
  }
}
