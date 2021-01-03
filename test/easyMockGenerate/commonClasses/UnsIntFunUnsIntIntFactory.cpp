#include <UnsIntFunUnsIntIntFactory.h>

static Parameter::Vector getIntFunIntIntPamrameters();

static Parameter::Vector getIntFunIntIntPamrameters()
{
  Parameter::Vector funParam(
  {
      NamedParameter(CTYPE_UINT, "a"),
      NamedParameter(CTYPE_INT, "b")
  });

  return funParam;
}

FunctionDeclaration UnsIntFunUnsIntIntFactory::functionFactory()
{
  FunctionDeclaration f(functionGetFunctionName(), TypedReturnValue(CTYPE_UINT), getIntFunIntIntPamrameters());
  return f;
}

FunctionDeclaration* UnsIntFunUnsIntIntFactory::newFunctionFactory()
{
  return functionFactory().clone();
}


std::string UnsIntFunUnsIntIntFactory::functionGetFunctionName()
{
  return std::string("unsIntFunUnsIntInt");
}

std::string UnsIntFunUnsIntIntFactory::getFilename()
{
   return "unsIntFunUnsIntInt.h";
}

void UnsIntFunUnsIntIntFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  unsigned int aToExpect = 0xcafebabe;
  unsigned int bToExpect = 0xf000baa3;
  unsigned int rvToExpect = 0xdeadbeaf;
  switch(tc)
  {
    case EasyMockTestCase::OneExpect:
      m_rvContext.m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect, bToExpect));
      m_params.push_back(std::make_tuple(aToExpect, bToExpect));
      m_compare.push_back(std::make_tuple(&cmp_u_int, &cmp_int));
      break;
    case EasyMockTestCase::ThreeExpects:
    {
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(rvToExpect + expectIdx);
        m_expects.push_back(std::make_tuple(aToExpect + expectIdx, bToExpect + expectIdx));
        m_params.push_back(std::make_tuple(aToExpect + expectIdx, bToExpect + expectIdx));
        m_compare.push_back(std::make_tuple(&cmp_u_int, &cmp_int));
      }
      break;
    }
    case EasyMockTestCase::OneExpectArgIsBad:
      m_rvContext.m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect, bToExpect));
      m_params.push_back(std::make_tuple(aToExpect + 1, bToExpect));
      m_compare.push_back(std::make_tuple(&cmp_u_int, &cmp_int));
      break;
    case EasyMockTestCase::SecondExpectArgIsBad:
      m_rvContext.m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect, bToExpect));
      m_params.push_back(std::make_tuple(aToExpect, bToExpect));
      m_compare.push_back(std::make_tuple(&cmp_u_int, &cmp_int));

      m_rvContext.m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect, bToExpect));
      m_params.push_back(std::make_tuple(aToExpect + 1, bToExpect)); //second call fails
      m_compare.push_back(std::make_tuple(&cmp_u_int, &cmp_int));
      break;
    case EasyMockTestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(rvToExpect + expectIdx);
        m_expects.push_back(std::make_tuple(aToExpect + expectIdx, bToExpect));
        m_params.push_back(std::make_tuple(aToExpect + expectIdx, bToExpect));
        m_compare.push_back(std::make_tuple(&cmp_u_int, &cmp_int));
      }
      break;
    case EasyMockTestCase::NoExpect:
      break;
  }
}
