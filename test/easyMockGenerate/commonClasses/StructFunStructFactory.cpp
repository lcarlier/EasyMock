#include <gtest/gtest.h>

#include <StructFunStructFactory.h>

#include "EasyMockGenerateTypes.h"
#include <StructType.h>
#include <StructField.h>
#include <EasyMockStructHelper.h>

static struct s2 toExpect[] =
{
  { 9, 4.5, {6, 3.5}},
  {10, 5.5, {7, 4.5}},
  {11, 6.5, {8, 5.5}}
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
  ReturnValue rv(newStructS1Type());

  return rv;
}

Function StructFunStructFactory::functionFactory()
{
  Function f(functionGetFunctionName(), structFunStructReturnValue(), structS2Parameter());
  return f;
}

Function* StructFunStructFactory::newFunctionFactory()
{
  return functionFactory().clone();
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
  switch(tc)
  {
    case EasyMockTestCase::OneExpect:
      m_rv.push_back(returnValues[0]);
      m_expects.push_back(std::make_tuple(toExpect[0]));
      m_params.push_back(std::make_tuple(toExpect[0]));
      m_compare.push_back(std::make_tuple(nullptr)); //Seperate dedicated UT are writen to test the generation and function of the comparators for structs
      break;
    case EasyMockTestCase::ThreeExpects:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_rv.push_back(returnValues[expectIdx]);
        m_expects.push_back(std::make_tuple(toExpect[expectIdx]));
        m_params.push_back(std::make_tuple(toExpect[expectIdx]));
        m_compare.push_back(std::make_tuple(nullptr)); //Seperate dedicated UT are writen to test the generation and function of the comparators for structs
      }
      break;
    case EasyMockTestCase::OneExpectArgIsBad: //Not tested in a generic way
    case EasyMockTestCase::SecondExpectArgIsBad: //Not tested in a generic way
    case EasyMockTestCase::NoExpect:
    case EasyMockTestCase::NotEnoughCall:
      break;
  }
}
