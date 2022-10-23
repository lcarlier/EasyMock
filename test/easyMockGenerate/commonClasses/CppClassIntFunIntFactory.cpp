#include <CppClassIntFunIntFactory.h>

#include <FunctionDeclaration.h>
#include <ClassType.h>
#include <ReturnValue.h>
#include <Namespace.h>

static std::shared_ptr<ClassType> classType{nullptr};

std::shared_ptr<FunctionDeclaration> CppClassIntFunIntFactory::functionFactory()
{
  classType.reset(new ClassType("ClassIntFunInt", false));
  Parameter::Vector params;
  params.emplace_back(NamedParameter(CTYPE_INT, "a"));
  auto f = std::make_shared<FunctionDeclaration>("intFunInt", TypedReturnValue(CTYPE_INT, false), std::move(params), getGlobalNamespace(), classType);
  f->setAccessSpecifier(FunctionAccessSpecifier::PUBLIC);
  classType->addFunction(f);
  return f;
}

ElementToMockList CppClassIntFunIntFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  returnedList.push_back(functionFactory());
  auto f = std::make_shared<FunctionDeclaration>("secondFun", VoidReturnValue(), Parameter::Vector{}, getGlobalNamespace(), classType);
  f->setAccessSpecifier(FunctionAccessSpecifier::PUBLIC);
  classType->addFunction(f);
  returnedList.push_back(f);
  return returnedList;
}

std::string CppClassIntFunIntFactory::functionGetFunctionName()
{
  return std::string{"ClassIntFunInt::intFunInt"};
}

std::string CppClassIntFunIntFactory::getFilename()
{
  return std::string{"cppClassIntFunInt.h"};
}

void CppClassIntFunIntFactory::setupOneExpect(ClassIntFunInt *expectInstance, ClassIntFunInt* paramInstance)
{
  m_rvContext.m_rv.push_back(5);
  m_expects.push_back(std::make_tuple(expectInstance, 6));
  m_params.push_back(std::make_tuple(paramInstance, 6));
  m_compare.push_back(std::make_tuple(EasyMock::cmp<int>));
}

void CppClassIntFunIntFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  ClassIntFunInt& instance = getInstance();
  switch(tc)
  {
    case EasyMockTestCase::TestCase::OneExpect:
      setupOneExpect(nullptr, &instance);
      break;
    case EasyMockTestCase::TestCase::ThreeExpects:
    {
      int aOneToExpect = 5;
      int rvToExpect = 7;
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(rvToExpect + expectIdx);
        m_expects.push_back(std::make_tuple(nullptr, aOneToExpect + expectIdx));
        m_params.push_back(std::make_tuple(&instance, aOneToExpect + expectIdx));
        m_compare.push_back(std::make_tuple(EasyMock::cmp<int>));
      }
      break;
    }
    case EasyMockTestCase::TestCase::OneExpectArgIsBad:
      m_rvContext.m_rv.push_back(5);
      m_expects.push_back(std::make_tuple(nullptr, 6));
      m_params.push_back(std::make_tuple(&instance, 7));
      m_compare.push_back(std::make_tuple(EasyMock::cmp<int>));
      break;
    case EasyMockTestCase::TestCase::SecondExpectArgIsBad:
      m_rvContext.m_rv.push_back(5);
      m_expects.push_back(std::make_tuple(nullptr, 6));
      m_params.push_back(std::make_tuple(&instance, 6));
      m_compare.push_back(std::make_tuple(EasyMock::cmp<int>));

      m_rvContext.m_rv.push_back(6);
      m_expects.push_back(std::make_tuple(nullptr, 7));
      m_params.push_back(std::make_tuple(&instance, 8)); //Second call fails
      m_compare.push_back(std::make_tuple(EasyMock::cmp<int>));
      break;
    case EasyMockTestCase::TestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(5);
        m_expects.push_back(std::make_tuple(nullptr, 6));
        m_params.push_back(std::make_tuple(&instance, 6));
        m_compare.push_back(std::make_tuple(EasyMock::cmp<int>));
      }
      break;
    case EasyMockTestCase::TestCase::NoExpect:
      break;
  }
}

void CppClassIntFunIntFactory::setupTestCase(EasyMockTestCase::TestCaseClass tc)
{
  ClassIntFunInt& instance = getInstance();
  switch(tc)
  {
    case EasyMockTestCase::TestCaseClass::OneExpectRightClassInstance:
      setupOneExpect(&instance, &instance);
      break;
    case EasyMockTestCase::TestCaseClass::OneExpectWrongClassInstance:
    {
      static ClassIntFunInt wrongInstance;
      setupOneExpect(&instance, &wrongInstance);
    }
    break;
  }
}

ClassIntFunInt &CppClassIntFunIntFactory::getInstance()
{
  static ClassIntFunInt inst{};
  return inst;
}