#include <ConstIntFunConstIntFactory.h>

#include <ReturnValue.h>
#include <EasyMock_CType.h>
#include <ConstQualifiedType.h>

FunctionDeclaration ConstIntFunConstIntFactory::functionFactory()
{
  ReturnValue rv { new ConstQualifiedType(new CType(CTYPE_INT)) };
  rv.setDeclareString("const int");

  TypeItf* curType = new CType(CTYPE_INT);
  ConstQualifiedType* constCurType = new ConstQualifiedType(curType);
  curType = nullptr; //We lost the ownership
  Parameter *param = new Parameter(constCurType, "i");
  param->setDeclareString("const int");
  constCurType = nullptr; //We lost the ownership

  FunctionDeclaration f(functionGetFunctionName(), rv, Parameter::Vector({param}));
  param = nullptr;
  return f;
}

FunctionDeclaration* ConstIntFunConstIntFactory::newFunctionFactory()
{
  return functionFactory().clone();
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
    case EasyMockTestCase::OneExpect:
      m_rvContext.m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(&cmp_int));
      break;
    case EasyMockTestCase::ThreeExpects:
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
    case EasyMockTestCase::OneExpectArgIsBad:
      m_rvContext.m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect + 1));
      m_compare.push_back(std::make_tuple(&cmp_int));
      break;
    case EasyMockTestCase::SecondExpectArgIsBad:
      m_rvContext.m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(&cmp_int));

      m_rvContext.m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect + 1)); //second call fails
      m_compare.push_back(std::make_tuple(&cmp_int));
      break;
    case EasyMockTestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(rvToExpect + expectIdx);
        m_expects.push_back(std::make_tuple(aToExpect + expectIdx));
        m_params.push_back(std::make_tuple(aToExpect + expectIdx));
        m_compare.push_back(std::make_tuple(&cmp_int));
      }
      break;
    case EasyMockTestCase::NoExpect:
      break;
  }
}
