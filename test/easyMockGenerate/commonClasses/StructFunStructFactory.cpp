#include <gtest/gtest.h>

#include <StructFunStructFactory.h>

#include "EasyMockGenerateTypes.h"
#include <StructType.h>
#include <EasyMockStructHelper.h>
#include <ComposableField.h>
#include <EasyMock_CType.h>
#include <Pointer.h>

float fToExpect[] = {4.5, 5.5, 6.5};

static struct s2 toExpect[] =
{
  { 9, &fToExpect[0], {6, 3.5}},
  {10, &fToExpect[1], {7, 4.5}},
  {11, &fToExpect[2], {8, 5.5}}
};

static struct s1 returnValues[] =
{
  {5, 2.5},
  {6, 3.5},
  {7, 4.5}
};

static ReturnValue structFunStructReturnValue();

static ReturnValue structFunStructReturnValue()
{
  ReturnValue rv{newStructS1Type()};

  return rv;
}

std::shared_ptr<FunctionDeclaration> StructFunStructFactory::functionFactory()
{
  Parameter::Vector funParam = structS2Parameter();

  auto structOnelineStruct = std::make_shared<StructType>( "onelineStruct", false );
  structOnelineStruct->addField(ComposableField{CTYPE_UINT, "a"});
  structOnelineStruct->addField(ComposableField{CTYPE_UINT, "b"});
  structOnelineStruct->addField(ComposableField{CTYPE_UINT, "c"});
  structOnelineStruct->addField(ComposableField{ std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_UINT)), "pa"});
  structOnelineStruct->addField(ComposableField{ std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_UINT)), "pb"});
  structOnelineStruct->addField(ComposableField{ std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_UINT)), "pc"});
  /*
   * This UT want's to make sure we are processing the space correctly so set the declare string
   */
  std::get<ComposableField>(structOnelineStruct->getContainedFields()[3]).setDeclareString("unsigned int *");
  std::get<ComposableField>(structOnelineStruct->getContainedFields()[4]).setDeclareString("unsigned int *");
  std::get<ComposableField>(structOnelineStruct->getContainedFields()[5]).setDeclareString("unsigned int *");
  funParam.push_back(Parameter{std::move(structOnelineStruct), "s2"});

  auto f = std::make_shared<FunctionDeclaration>(functionGetFunctionName(), structFunStructReturnValue(), std::move(funParam));
  return f;
}

std::string StructFunStructFactory::functionGetFunctionName()
{
  return std::string("structFunStruct");
}

std::string StructFunStructFactory::getFilename()
{
  return "structFunStruct.h";
}

void StructFunStructFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  struct onelineStruct onelineStruct{6, 7, 8};
  switch(tc)
  {
    case EasyMockTestCase::TestCase::OneExpect:
      m_rvContext.m_rv.push_back(returnValues[0]);
      m_expects.push_back(std::make_tuple(toExpect[0], onelineStruct));
      m_params.push_back(std::make_tuple(toExpect[0], onelineStruct));
      m_compare.push_back(std::make_tuple(nullptr, nullptr)); //Seperate dedicated UT are writen to test the generation and function of the comparators for structs
      break;
    case EasyMockTestCase::TestCase::ThreeExpects:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(returnValues[expectIdx]);
        m_expects.push_back(std::make_tuple(toExpect[expectIdx], onelineStruct));
        m_params.push_back(std::make_tuple(toExpect[expectIdx], onelineStruct));
        m_compare.push_back(std::make_tuple(nullptr, nullptr)); //Seperate dedicated UT are writen to test the generation and function of the comparators for structs
      }
      break;
    case EasyMockTestCase::TestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(returnValues[expectIdx]);
        m_expects.push_back(std::make_tuple(toExpect[expectIdx], onelineStruct));
        m_params.push_back(std::make_tuple(toExpect[expectIdx], onelineStruct));
        m_compare.push_back(std::make_tuple(nullptr, nullptr)); //Seperate dedicated UT are writen to test the generation and function of the comparators for structs
      }
      break;
    case EasyMockTestCase::TestCase::OneExpectArgIsBad: //Not tested in a generic way
    case EasyMockTestCase::TestCase::SecondExpectArgIsBad: //Not tested in a generic way
    case EasyMockTestCase::TestCase::NoExpect:
      break;
  }
}
