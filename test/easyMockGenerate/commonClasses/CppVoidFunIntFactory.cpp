#include <CppVoidFunIntFactory.h>

#include <FunctionFactory.h>

FunctionDeclaration CppVoidFunIntFactory::functionFactory()
{
  Parameter::Vector params;
  params.emplace_back(NamedParameter(CTYPE_INT, "a"));
  return FunctionDeclaration { functionGetFunctionName(), VoidReturnValue(), std::move(params) };
}

ElementToMockList CppVoidFunIntFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  returnedList.push_back(functionFactory());
  return returnedList;
}

std::string CppVoidFunIntFactory::functionGetFunctionName()
{
  return std::string("cppVoidFunInt");
}

std::string CppVoidFunIntFactory::getFilename()
{
  return "cppVoidFunInt.h";
}

void CppVoidFunIntFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  switch(tc)
  {
    case EasyMockTestCase::OneExpect:
      m_expects.push_back(std::make_tuple(6));
      m_params.push_back(std::make_tuple(6));
      m_compare.push_back(std::make_tuple(EasyMock::cmp<int>));
      break;
    case EasyMockTestCase::ThreeExpects:
    {
      int aOneToExpect = 5;
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_expects.push_back(std::make_tuple(aOneToExpect + expectIdx));
        m_params.push_back(std::make_tuple(aOneToExpect + expectIdx));
        m_compare.push_back(std::make_tuple(EasyMock::cmp<int>));
      }
      break;
    }
    case EasyMockTestCase::OneExpectArgIsBad:
      m_expects.push_back(std::make_tuple(6));
      m_params.push_back(std::make_tuple(7));
      m_compare.push_back(std::make_tuple(EasyMock::cmp<int>));
      break;
    case EasyMockTestCase::SecondExpectArgIsBad:
      m_expects.push_back(std::make_tuple(6));
      m_params.push_back(std::make_tuple(6));
      m_compare.push_back(std::make_tuple(EasyMock::cmp<int>));

      m_expects.push_back(std::make_tuple(7));
      m_params.push_back(std::make_tuple(8)); //Second call fails
      m_compare.push_back(std::make_tuple(EasyMock::cmp<int>));
      break;
    case EasyMockTestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_expects.push_back(std::make_tuple(6));
        m_params.push_back(std::make_tuple(6));
        m_compare.push_back(std::make_tuple(EasyMock::cmp<int>));
      }
      break;
    case EasyMockTestCase::NoExpect:
      break;
  }
}
