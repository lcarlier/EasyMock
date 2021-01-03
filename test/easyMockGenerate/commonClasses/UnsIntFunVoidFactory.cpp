#include <UnsIntFunVoidFactory.h>

FunctionDeclaration UnsIntFunVoidFactory::functionFactory()
{
  FunctionDeclaration f(functionGetFunctionName(), TypedReturnValue(CTYPE_UINT),{});
  return f;
}

FunctionDeclaration* UnsIntFunVoidFactory::newFunctionFactory()
{
  return functionFactory().clone();
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
    case EasyMockTestCase::OneExpect:
      m_rvContext.m_rv.push_back(5);
      break;
    case EasyMockTestCase::ThreeExpects:
    {
      int rvToExpect = 7;
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(rvToExpect + expectIdx);
      }
      break;
    }
    case EasyMockTestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(5);
      }
      break;
    case EasyMockTestCase::OneExpectArgIsBad: //Not tested
    case EasyMockTestCase::SecondExpectArgIsBad: //Not tested
    case EasyMockTestCase::NoExpect:
      break;
  }
}
