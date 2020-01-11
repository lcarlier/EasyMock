#include <IntFunVoidFactory.h>

Function IntFunVoidFactory::functionFactory()
{
  Function f(functionGetFunctionName(), TypedReturnValue(CTYPE_INT),{});
  return f;
}

Function* IntFunVoidFactory::newFunctionFactory()
{
  return functionFactory().clone();
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
    case EasyMockTestCase::OneExpect:
      m_rv.push_back(-5);
      break;
    case EasyMockTestCase::ThreeExpects:
    {
      int rvToExpect = -7;
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_rv.push_back(rvToExpect + expectIdx);
      }
      break;
    }
    case EasyMockTestCase::OneExpectArgIsBad: //Not tested
    case EasyMockTestCase::SecondExpectArgIsBad: //Not tested
    case EasyMockTestCase::NoExpect:
    case EasyMockTestCase::NotEnoughCall:
      break;
  }
}
