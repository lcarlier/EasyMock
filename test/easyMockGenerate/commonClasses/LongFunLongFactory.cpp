#include <LongFunLongFactory.h>

FunctionDeclaration LongFunLongFactory::functionFactory()
{
  Parameter::Vector pv{};
  pv.emplace_back(NamedParameter(CTYPE_LONG, "l"));
  FunctionDeclaration f(functionGetFunctionName(), TypedReturnValue(CTYPE_LONG), std::move(pv));
  return f;
}

std::string LongFunLongFactory::functionGetFunctionName()
{
  return std::string("longFunLong");
}

std::string LongFunLongFactory::getFilename()
{
   return "longFunLong.h";
}

void LongFunLongFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  long aToExpect = std::numeric_limits<long>::max() - 42;
  long rvToExpect = std::numeric_limits<long>::max() - 84;
  aToExpect = -aToExpect;
  rvToExpect = -rvToExpect;
  switch(tc)
  {
    case EasyMockTestCase::OneExpect:
      m_rvContext.m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(&cmp_long));
      break;
    case EasyMockTestCase::ThreeExpects:
    {
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(rvToExpect + expectIdx);
        m_expects.push_back(std::make_tuple(aToExpect + expectIdx));
        m_params.push_back(std::make_tuple(aToExpect + expectIdx));
        m_compare.push_back(std::make_tuple(&cmp_long));
      }
      break;
    }
    case EasyMockTestCase::OneExpectArgIsBad:
      m_rvContext.m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect + 1));
      m_compare.push_back(std::make_tuple(&cmp_long));
      break;
    case EasyMockTestCase::SecondExpectArgIsBad:
      m_rvContext.m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(&cmp_long));

      m_rvContext.m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect + 1)); //second call fails
      m_compare.push_back(std::make_tuple(&cmp_long));
      break;
    case EasyMockTestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(rvToExpect + expectIdx);
        m_expects.push_back(std::make_tuple(aToExpect + expectIdx));
        m_params.push_back(std::make_tuple(aToExpect + expectIdx));
        m_compare.push_back(std::make_tuple(&cmp_long));
      }
      break;
    case EasyMockTestCase::NoExpect:
      break;
  }
}
