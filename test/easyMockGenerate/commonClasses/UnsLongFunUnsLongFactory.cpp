#include <UnsLongFunUnsLongFactory.h>

FunctionDeclaration UnsLongFunUnsLongFactory::functionFactory()
{
  FunctionDeclaration f(functionGetFunctionName(), TypedReturnValue(CTYPE_ULONG), Parameter::Vector({NamedParameter(CTYPE_ULONG, "ul")}));
  return f;
}

FunctionDeclaration* UnsLongFunUnsLongFactory::newFunctionFactory()
{
  return functionFactory().clone();
}


std::string UnsLongFunUnsLongFactory::functionGetFunctionName()
{
  return std::string("unsLongFunUnsLong");
}

std::string UnsLongFunUnsLongFactory::getFilename()
{
   return "unsLongFunUnsLong.h";
}

void UnsLongFunUnsLongFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  unsigned long aToExpect = std::numeric_limits<unsigned long>::max() - 42;
  unsigned long rvToExpect = std::numeric_limits<unsigned long>::max() - 84;
  switch(tc)
  {
    case EasyMockTestCase::OneExpect:
      m_rvContext.m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(&cmp_u_long));
      break;
    case EasyMockTestCase::ThreeExpects:
    {
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(rvToExpect + expectIdx);
        m_expects.push_back(std::make_tuple(aToExpect + expectIdx));
        m_params.push_back(std::make_tuple(aToExpect + expectIdx));
        m_compare.push_back(std::make_tuple(&cmp_u_long));
      }
      break;
    }
    case EasyMockTestCase::OneExpectArgIsBad:
      m_rvContext.m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect + 1));
      m_compare.push_back(std::make_tuple(&cmp_u_long));
      break;
    case EasyMockTestCase::SecondExpectArgIsBad:
      m_rvContext.m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(&cmp_u_long));

      m_rvContext.m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect + 1)); //second call fails
      m_compare.push_back(std::make_tuple(&cmp_u_long));
      break;
    case EasyMockTestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(rvToExpect + expectIdx);
        m_expects.push_back(std::make_tuple(aToExpect + expectIdx));
        m_params.push_back(std::make_tuple(aToExpect + expectIdx));
        m_compare.push_back(std::make_tuple(&cmp_u_long));
      }
      break;
    case EasyMockTestCase::NoExpect:
      break;
  }
}
