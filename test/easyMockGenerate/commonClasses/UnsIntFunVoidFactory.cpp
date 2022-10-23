#include <UnsIntFunVoidFactory.h>

std::shared_ptr<FunctionDeclaration> UnsIntFunVoidFactory::functionFactory()
{
  auto f = std::make_shared<FunctionDeclaration>(functionGetFunctionName(), TypedReturnValue(CTYPE_UINT), Parameter::Vector {});
  return f;
}

std::string UnsIntFunVoidFactory::functionGetFunctionName()
{
  return std::string("unsIntFunVoid");
}

std::string UnsIntFunVoidFactory::getFilename()
{
   return "unsIntFunVoid.h";
}

void UnsIntFunVoidFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  switch(tc)
  {
    case EasyMockTestCase::TestCase::OneExpect:
      m_rvContext.m_rv.push_back(5);
      break;
    case EasyMockTestCase::TestCase::ThreeExpects:
    {
      int rvToExpect = 7;
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(rvToExpect + expectIdx);
      }
      break;
    }
    case EasyMockTestCase::TestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(5);
      }
      break;
    case EasyMockTestCase::TestCase::OneExpectArgIsBad: //Not tested
    case EasyMockTestCase::TestCase::SecondExpectArgIsBad: //Not tested
    case EasyMockTestCase::TestCase::NoExpect:
      break;
  }
}
