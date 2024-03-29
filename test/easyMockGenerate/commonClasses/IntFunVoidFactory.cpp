#include <IntFunVoidFactory.h>

std::shared_ptr<FunctionDeclaration> IntFunVoidFactory::functionFactory()
{
  auto f = std::make_shared<FunctionDeclaration>(functionGetFunctionName(), TypedReturnValue(CTYPE_INT), Parameter::Vector {});
  return f;
}

std::string IntFunVoidFactory::functionGetFunctionName()
{
  return std::string("intFunVoid");
}

std::string IntFunVoidFactory::getFilename()
{
   return "intFunVoid.h";
}

void IntFunVoidFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  switch(tc)
  {
    case EasyMockTestCase::TestCase::OneExpect:
      m_rvContext.m_rv.push_back(-5);
      break;
    case EasyMockTestCase::TestCase::ThreeExpects:
    {
      int rvToExpect = -7;
      int nbThreeExpect = EasyMockTestCase::ThreeExpects_NbExpects;
      for(int expectIdx = 0; expectIdx < nbThreeExpect; expectIdx++)
      {
        m_rvContext.m_rv.push_back(rvToExpect + expectIdx);
      }
      break;
    }
    case EasyMockTestCase::TestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(-5);
      }
      break;
    case EasyMockTestCase::TestCase::OneExpectArgIsBad: //Not tested
    case EasyMockTestCase::TestCase::SecondExpectArgIsBad: //Not tested
    case EasyMockTestCase::TestCase::NoExpect:
      break;
  }
}
