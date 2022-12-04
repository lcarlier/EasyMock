#include <CppRefIntFunRefIntFactory.h>

#include <FunctionFactory.h>
#include <Reference.h>
#include <EasyMock_CType.h>

std::shared_ptr<FunctionDeclaration> CppRefIntFunRefIntFactory::functionFactory()
{
  Parameter::Vector params;
  {
    Parameter p{std::make_shared<Reference>(std::make_shared<CType>(CTYPE_INT)), "a"};
    params.push_back(std::move(p));
  }
  ReturnValue rv{std::make_shared<Reference>(std::make_shared<CType>(CTYPE_INT))};
  return std::make_shared<FunctionDeclaration>( functionGetFunctionName(), std::move(rv), std::move(params) );
}

ElementToMockList CppRefIntFunRefIntFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  returnedList.push_back(functionFactory());
  return returnedList;
}

std::string CppRefIntFunRefIntFactory::functionGetFunctionName()
{
  return std::string("cppRefIntFunRefInt");
}

std::string CppRefIntFunRefIntFactory::getFilename()
{
  return "cppRefIntFunRefInt.h";
}

void CppRefIntFunRefIntFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  static int firstCallValue = 6;
  static int secondCallValue = 7;
  static int expectedRet = 6;
  switch(tc)
  {
    case EasyMockTestCase::TestCase::OneExpect:
      m_rvContext.m_rv.push_back(expectedRet);
      m_expects.push_back(firstCallValue);
      m_params.push_back(firstCallValue);
      m_compare.push_back(std::make_tuple(EasyMock::cmp<int&>));
      break;
    case EasyMockTestCase::TestCase::ThreeExpects:
    {
      static int aOneToExpect = 5;
      static int aOneToExpectPlus1 = aOneToExpect + 1;
      static int aOneToExpectPlus2 = aOneToExpect + 2;

      m_rvContext.m_rv.push_back(aOneToExpect);
      m_expects.push_back(aOneToExpect);
      m_params.push_back(aOneToExpect);
      m_compare.push_back(std::make_tuple(EasyMock::cmp<int&>));

      m_rvContext.m_rv.push_back(aOneToExpectPlus1);
      m_expects.push_back(aOneToExpectPlus1);
      m_params.push_back(aOneToExpectPlus1);
      m_compare.push_back(std::make_tuple(EasyMock::cmp<int&>));

      m_rvContext.m_rv.push_back(aOneToExpectPlus2);
      m_expects.push_back(aOneToExpectPlus2);
      m_params.push_back(aOneToExpectPlus2);
      m_compare.push_back(std::make_tuple(EasyMock::cmp<int&>));

      break;
    }
    case EasyMockTestCase::TestCase::OneExpectArgIsBad:
      m_rvContext.m_rv.push_back(firstCallValue);
      m_expects.push_back(firstCallValue);
      m_params.push_back(secondCallValue);
      m_compare.push_back(std::make_tuple(EasyMock::cmp<int&>));
      break;
    case EasyMockTestCase::TestCase::SecondExpectArgIsBad:
    {
      static int badCall = 8;
      m_rvContext.m_rv.push_back(firstCallValue);
      m_expects.push_back(firstCallValue);
      m_params.push_back(firstCallValue);
      m_compare.push_back(std::make_tuple(EasyMock::cmp<int &>));

      m_rvContext.m_rv.push_back(secondCallValue);
      m_expects.push_back(secondCallValue);
      m_params.push_back(badCall); //Second call fails
      m_compare.push_back(std::make_tuple(EasyMock::cmp<int&>));
      break;
    }
    case EasyMockTestCase::TestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(firstCallValue);
        m_expects.push_back(firstCallValue);
        m_params.push_back(firstCallValue);
        m_compare.push_back(std::make_tuple(EasyMock::cmp<int&>));
      }
      break;
    case EasyMockTestCase::TestCase::NoExpect:
      break;
  }
}
