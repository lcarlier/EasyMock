#include <CppNamespaceIntFunIntFactory.h>
#include <FunctionFactory.h>
#include <Namespace.h>
#include <EasyMock_CType.h>

std::shared_ptr<FunctionDeclaration> CppNamespaceIntFunIntFactory::functionFactory()
{
  Parameter::Vector params;
  params.emplace_back(NamedParameter(CTYPE_INT, "a"));
  auto funNamespace = std::make_shared<const Namespace>("L2", std::make_shared<const Namespace>("L1"));
  return std::make_shared<FunctionDeclaration>("intFunInt", ReturnValue{std::make_shared<CType>(CTYPE_INT)}, std::move(params), std::move(funNamespace));
}

ElementToMockList CppNamespaceIntFunIntFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  returnedList.push_back(functionFactory());
  return returnedList;
}

std::string CppNamespaceIntFunIntFactory::functionGetFunctionName()
{
  return std::string("L1::L2::intFunInt");
}

std::string CppNamespaceIntFunIntFactory::getFilename()
{
  return "cppNamespaceIntFunInt.h";
}

void CppNamespaceIntFunIntFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  switch(tc)
  {
    case EasyMockTestCase::TestCase::OneExpect:
      m_rvContext.m_rv.push_back(5);
      m_expects.push_back(std::make_tuple(6));
      m_params.push_back(std::make_tuple(6));
      m_compare.push_back(std::make_tuple(EasyMock::cmp<int>));
      break;
    case EasyMockTestCase::TestCase::ThreeExpects:
    {
      int aOneToExpect = 5;
      int rvToExpect = 7;
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(rvToExpect + expectIdx);
        m_expects.push_back(std::make_tuple(aOneToExpect + expectIdx));
        m_params.push_back(std::make_tuple(aOneToExpect + expectIdx));
        m_compare.push_back(std::make_tuple(EasyMock::cmp<int>));
      }
      break;
    }
    case EasyMockTestCase::TestCase::OneExpectArgIsBad:
      m_rvContext.m_rv.push_back(5);
      m_expects.push_back(std::make_tuple(6));
      m_params.push_back(std::make_tuple(7));
      m_compare.push_back(std::make_tuple(EasyMock::cmp<int>));
      break;
    case EasyMockTestCase::TestCase::SecondExpectArgIsBad:
      m_rvContext.m_rv.push_back(5);
      m_expects.push_back(std::make_tuple(6));
      m_params.push_back(std::make_tuple(6));
      m_compare.push_back(std::make_tuple(EasyMock::cmp<int>));

      m_rvContext.m_rv.push_back(6);
      m_expects.push_back(std::make_tuple(7));
      m_params.push_back(std::make_tuple(8)); //Second call fails
      m_compare.push_back(std::make_tuple(EasyMock::cmp<int>));
      break;
    case EasyMockTestCase::TestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(5);
        m_expects.push_back(std::make_tuple(6));
        m_params.push_back(std::make_tuple(6));
        m_compare.push_back(std::make_tuple(EasyMock::cmp<int>));
      }
      break;
    case EasyMockTestCase::TestCase::NoExpect:
      break;
  }
}
