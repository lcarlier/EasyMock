#include <CppClassVoidFunVoidConstFactory.h>

#include <FunctionDeclaration.h>
#include <ClassType.h>
#include <ReturnValue.h>
#include <Namespace.h>

static std::shared_ptr<ClassType> classType{nullptr};

std::shared_ptr<FunctionDeclaration> CppClassVoidFunVoidConstFactory::functionFactory()
{
  classType.reset(new ClassType("ClassVoidFunVoidConst", false));
  auto f = std::make_shared<FunctionDeclaration>("voidFunVoidConst", VoidReturnValue(), Parameter::Vector{}, getGlobalNamespace(), classType);
  f->setAccessSpecifier(FunctionAccessSpecifier::PUBLIC);
  f->setClassConst(true);
  classType->addFunction(f);
  return f;
}

ElementToMockList CppClassVoidFunVoidConstFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  returnedList.push_back(functionFactory());
  return returnedList;
}

std::string CppClassVoidFunVoidConstFactory::functionGetFunctionName()
{
  return std::string{"ClassVoidFunVoidConst::voidFunVoidConst"};
}

std::string CppClassVoidFunVoidConstFactory::getFilename()
{
  return std::string{"cppClassVoidFunVoidConst.h"};
}

void CppClassVoidFunVoidConstFactory::setupOneExpect(ClassVoidFunVoidConst *expectInstance, ClassVoidFunVoidConst* paramInstance)
{
  m_expects.push_back(std::make_tuple(expectInstance));
  m_params.push_back(std::make_tuple(paramInstance));
}

void CppClassVoidFunVoidConstFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  ClassVoidFunVoidConst& instance = getInstance();
  switch(tc)
  {
    case EasyMockTestCase::TestCase::OneExpect:
      setupOneExpect(nullptr, &instance);
      break;
    case EasyMockTestCase::TestCase::ThreeExpects:
    {
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_expects.push_back(std::make_tuple(nullptr));
        m_params.push_back(std::make_tuple(&instance));
      }
      break;
    }
    case EasyMockTestCase::TestCase::OneExpectArgIsBad:
      m_expects.push_back(std::make_tuple(nullptr));
      m_params.push_back(std::make_tuple(&instance));
      break;
    case EasyMockTestCase::TestCase::SecondExpectArgIsBad:
      m_expects.push_back(std::make_tuple(nullptr));
      m_params.push_back(std::make_tuple(&instance));

      m_expects.push_back(std::make_tuple(nullptr));
      m_params.push_back(std::make_tuple(&instance)); //Second call fails
      break;
    case EasyMockTestCase::TestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_expects.push_back(std::make_tuple(nullptr));
        m_params.push_back(std::make_tuple(&instance));
      }
      break;
    case EasyMockTestCase::TestCase::NoExpect:
      break;
  }
}

void CppClassVoidFunVoidConstFactory::setupTestCase(EasyMockTestCase::TestCaseClass tc)
{
  ClassVoidFunVoidConst& instance = getInstance();
  switch(tc)
  {
    case EasyMockTestCase::TestCaseClass::OneExpectRightClassInstance:
      setupOneExpect(&instance, &instance);
      break;
    case EasyMockTestCase::TestCaseClass::OneExpectWrongClassInstance:
    {
      static ClassVoidFunVoidConst wrongInstance;
      setupOneExpect(&instance, &wrongInstance);
    }
      break;
  }
}

ClassVoidFunVoidConst &CppClassVoidFunVoidConstFactory::getInstance()
{
  static ClassVoidFunVoidConst inst{};
  return inst;
}