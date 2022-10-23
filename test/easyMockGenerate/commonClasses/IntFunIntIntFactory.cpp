#include <IntFunIntIntFactory.h>

std::shared_ptr<FunctionDeclaration> IntFunIntIntFactory::functionFactory()
{
  Parameter::Vector funParam{};
  funParam.emplace_back(NamedParameter(CTYPE_INT, "a"));
  funParam.emplace_back(NamedParameter(CTYPE_INT, "b"));
  auto f = std::make_shared<FunctionDeclaration>(functionGetFunctionName(), TypedReturnValue(CTYPE_INT), std::move(funParam));
  return f;
}

std::string IntFunIntIntFactory::functionGetFunctionName()
{
  return std::string("intFunIntInt");
}

std::string IntFunIntIntFactory::getFilename()
{
   return "intFunIntInt.h";
}

void IntFunIntIntFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  switch(tc)
  {
    case EasyMockTestCase::TestCase::OneExpect:
      m_rvContext.m_rv.push_back(5);
      m_expects.push_back(std::make_tuple(6, 7));
      m_params.push_back(std::make_tuple(6, 7));
      m_compare.push_back(std::make_tuple(&cmp_int, &cmp_int));
      break;
    case EasyMockTestCase::TestCase::ThreeExpects:
    {
      int aOneToExpect = 5;
      int aTwoToExpect = 6;
      int rvToExpect = 7;
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(rvToExpect + expectIdx);
        m_expects.push_back(std::make_tuple(aOneToExpect + expectIdx, aTwoToExpect + expectIdx));
        m_params.push_back(std::make_tuple(aOneToExpect + expectIdx, aTwoToExpect + expectIdx));
        m_compare.push_back(std::make_tuple(&cmp_int, &cmp_int));
      }
      break;
    }
    case EasyMockTestCase::TestCase::OneExpectArgIsBad:
      m_rvContext.m_rv.push_back(5);
      m_expects.push_back(std::make_tuple(6, 7));
      m_params.push_back(std::make_tuple(7, 7));
      m_compare.push_back(std::make_tuple(&cmp_int, &cmp_int));
      break;
    case EasyMockTestCase::TestCase::SecondExpectArgIsBad:
      m_rvContext.m_rv.push_back(5);
      m_expects.push_back(std::make_tuple(6, 7));
      m_params.push_back(std::make_tuple(6, 7));
      m_compare.push_back(std::make_tuple(&cmp_int, &cmp_int));

      m_rvContext.m_rv.push_back(6);
      m_expects.push_back(std::make_tuple(7, 8));
      m_params.push_back(std::make_tuple(8, 8)); //Second call fails
      m_compare.push_back(std::make_tuple(&cmp_int, &cmp_int));
      break;
    case EasyMockTestCase::TestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(5);
        m_expects.push_back(std::make_tuple(6, 7));
        m_params.push_back(std::make_tuple(6, 7));
        m_compare.push_back(std::make_tuple(&cmp_int, &cmp_int));
      }
      break;
    case EasyMockTestCase::TestCase::NoExpect:
      break;
  }
}
