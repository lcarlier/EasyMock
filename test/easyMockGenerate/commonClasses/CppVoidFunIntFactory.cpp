#include <CppVoidFunIntFactory.h>

#include <FunctionFactory.h>

std::shared_ptr<FunctionDeclaration> CppVoidFunIntFactory::functionFactory()
{
  Parameter::Vector params;
  params.emplace_back(NamedParameter(CTYPE_INT, "a"));
  return std::make_shared<FunctionDeclaration>( functionGetFunctionName(), VoidReturnValue(), std::move(params) );
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
    case EasyMockTestCase::TestCase::OneExpect:
      m_expects.push_back(std::make_tuple(6));
      m_params.push_back(std::make_tuple(6));
      m_compare.push_back(std::make_tuple(EasyMock::cmp<int>));
      break;
    case EasyMockTestCase::TestCase::ThreeExpects:
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
    case EasyMockTestCase::TestCase::OneExpectArgIsBad:
      m_expects.push_back(std::make_tuple(6));
      m_params.push_back(std::make_tuple(7));
      m_compare.push_back(std::make_tuple(EasyMock::cmp<int>));
      break;
    case EasyMockTestCase::TestCase::SecondExpectArgIsBad:
      m_expects.push_back(std::make_tuple(6));
      m_params.push_back(std::make_tuple(6));
      m_compare.push_back(std::make_tuple(EasyMock::cmp<int>));

      m_expects.push_back(std::make_tuple(7));
      m_params.push_back(std::make_tuple(8)); //Second call fails
      m_compare.push_back(std::make_tuple(EasyMock::cmp<int>));
      break;
    case EasyMockTestCase::TestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_expects.push_back(std::make_tuple(6));
        m_params.push_back(std::make_tuple(6));
        m_compare.push_back(std::make_tuple(EasyMock::cmp<int>));
      }
      break;
    case EasyMockTestCase::TestCase::NoExpect:
      break;
  }
}
