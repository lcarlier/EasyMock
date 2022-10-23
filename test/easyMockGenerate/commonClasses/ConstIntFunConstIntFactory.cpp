#include <ConstIntFunConstIntFactory.h>

#include <ReturnValue.h>
#include <EasyMock_CType.h>
#include <ConstQualifiedType.h>

std::shared_ptr<FunctionDeclaration> ConstIntFunConstIntFactory::functionFactory()
{
  ReturnValue rv { std::make_shared<ConstQualifiedType>(std::make_shared<CType>(CTYPE_INT)) };
  /*
   * We use setDeclareString because rv.getFullDeclareString() generates
   * "int const" by default
   */
  rv.setDeclareString("const int");

  auto curType = std::make_shared<CType>(CTYPE_INT);
  auto constCurType = std::make_shared<ConstQualifiedType>(std::move(curType));
  Parameter param{std::move(constCurType), "i"};

  Parameter::Vector pv{};
  pv.emplace_back(std::move(param));
  auto f = std::make_shared<FunctionDeclaration>(functionGetFunctionName(), std::move(rv), std::move(pv));
  return f;
}

std::string ConstIntFunConstIntFactory::functionGetFunctionName()
{
  return std::string("constIntFunConstInt");
}

std::string ConstIntFunConstIntFactory::getFilename()
{
   return "constIntFunConstInt.h";
}

void ConstIntFunConstIntFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  const int aToExpect = 42;
  const int rvToExpect = 84;
  switch(tc)
  {
    case EasyMockTestCase::TestCase::OneExpect:
      m_rvContext.m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(&cmp_int));
      break;
    case EasyMockTestCase::TestCase::ThreeExpects:
    {
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(rvToExpect + expectIdx);
        m_expects.push_back(std::make_tuple(aToExpect + expectIdx));
        m_params.push_back(std::make_tuple(aToExpect + expectIdx));
        m_compare.push_back(std::make_tuple(&cmp_int));
      }
      break;
    }
    case EasyMockTestCase::TestCase::OneExpectArgIsBad:
      m_rvContext.m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect + 1));
      m_compare.push_back(std::make_tuple(&cmp_int));
      break;
    case EasyMockTestCase::TestCase::SecondExpectArgIsBad:
      m_rvContext.m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(&cmp_int));

      m_rvContext.m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect + 1)); //second call fails
      m_compare.push_back(std::make_tuple(&cmp_int));
      break;
    case EasyMockTestCase::TestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(rvToExpect + expectIdx);
        m_expects.push_back(std::make_tuple(aToExpect + expectIdx));
        m_params.push_back(std::make_tuple(aToExpect + expectIdx));
        m_compare.push_back(std::make_tuple(&cmp_int));
      }
      break;
    case EasyMockTestCase::TestCase::NoExpect:
      break;
  }
}
