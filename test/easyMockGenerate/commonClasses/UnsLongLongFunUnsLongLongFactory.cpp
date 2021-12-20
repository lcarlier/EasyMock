#include <UnsLongLongFunUnsLongLongFactory.h>

FunctionDeclaration UnsLongLongFunUnsLongLongFactory::functionFactory()
{
  Parameter::Vector pv{};
  pv.emplace_back(NamedParameter(CTYPE_ULONG_LONG, "ull"));
  FunctionDeclaration f(functionGetFunctionName(), TypedReturnValue(CTYPE_ULONG_LONG), std::move(pv));
  return f;
}

std::string UnsLongLongFunUnsLongLongFactory::functionGetFunctionName()
{
  return std::string("unsLongLongFunUnsLongLong");
}

std::string UnsLongLongFunUnsLongLongFactory::getFilename()
{
   return "unsLongLongFunUnsLongLong.h";
}

void UnsLongLongFunUnsLongLongFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  unsigned long long aToExpect = std::numeric_limits<unsigned long long>::max() - 42;
  unsigned long long rvToExpect = std::numeric_limits<unsigned long long>::max() - 84;
  switch(tc)
  {
    case EasyMockTestCase::OneExpect:
      m_rvContext.m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(&cmp_u_long_long));
      break;
    case EasyMockTestCase::ThreeExpects:
    {
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(rvToExpect + expectIdx);
        m_expects.push_back(std::make_tuple(aToExpect + expectIdx));
        m_params.push_back(std::make_tuple(aToExpect + expectIdx));
        m_compare.push_back(std::make_tuple(&cmp_u_long_long));
      }
      break;
    }
    case EasyMockTestCase::OneExpectArgIsBad:
      m_rvContext.m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect + 1));
      m_compare.push_back(std::make_tuple(&cmp_u_long_long));
      break;
    case EasyMockTestCase::SecondExpectArgIsBad:
      m_rvContext.m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(&cmp_u_long_long));

      m_rvContext.m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect + 1)); //second call fails
      m_compare.push_back(std::make_tuple(&cmp_u_long_long));
      break;
    case EasyMockTestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(rvToExpect + expectIdx);
        m_expects.push_back(std::make_tuple(aToExpect + expectIdx));
        m_params.push_back(std::make_tuple(aToExpect + expectIdx));
        m_compare.push_back(std::make_tuple(&cmp_u_long_long));
      }
      break;
    case EasyMockTestCase::NoExpect:
      break;
  }
}
