#include <CharFunCharFactory.h>

Function CharFunCharFactory::functionFactory()
{
  Function f(functionGetFunctionName(), TypedReturnValue(CTYPE_CHAR), Parameter::Vector({NamedParameter(CTYPE_CHAR, "c")}));
  return f;
}

Function* CharFunCharFactory::newFunctionFactory()
{
  return functionFactory().clone();
}


std::string CharFunCharFactory::functionGetFunctionName()
{
  return std::string("charFunChar");
}

std::string CharFunCharFactory::getFilename()
{
   return "charFunChar.h";
}

void CharFunCharFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  char aToExpect = 'a';
  char rvToExpect = 'b';
  switch(tc)
  {
    case EasyMockTestCase::OneExpect:
      m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(&cmp_char));
      break;
    case EasyMockTestCase::ThreeExpects:
    {
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_rv.push_back(rvToExpect + expectIdx);
        m_expects.push_back(std::make_tuple(aToExpect + expectIdx));
        m_params.push_back(std::make_tuple(aToExpect + expectIdx));
        m_compare.push_back(std::make_tuple(&cmp_char));
      }
      break;
    }
    case EasyMockTestCase::OneExpectArgIsBad:
      m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect + 1));
      m_compare.push_back(std::make_tuple(&cmp_char));
      break;
    case EasyMockTestCase::SecondExpectArgIsBad:
      m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(&cmp_char));

      m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect + 1)); //second call fails
      m_compare.push_back(std::make_tuple(&cmp_char));
      break;
    case EasyMockTestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_rv.push_back(rvToExpect + expectIdx);
        m_expects.push_back(std::make_tuple(aToExpect + expectIdx));
        m_params.push_back(std::make_tuple(aToExpect + expectIdx));
        m_compare.push_back(std::make_tuple(&cmp_char));
      }
      break;
    case EasyMockTestCase::NoExpect:
      break;
  }
}
