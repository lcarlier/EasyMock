#include <gtest/gtest.h>

#include <StructFunStructFactory.h>

#include "EasyMockGenerateTypes.h"
#include <StructType.h>
#include <StructField.h>

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

static StructType* newStructFunStructS1Type();
static ReturnValue structFunStructReturnValue();
static Parameter::Vector structFunStructParameters();

static StructType* newStructFunStructS1Type()
{
  return new StructType("s1",{new StructField(CTYPE_INT, "a"), new StructField(CTYPE_FLOAT, "b")});
}

static ReturnValue structFunStructReturnValue()
{
  ReturnValue rv(newStructFunStructS1Type());

  return rv;
}

static Parameter::Vector structFunStructParameters()
{
  StructType* s1StructType = newStructFunStructS1Type();
  StructField *s1 = new StructField(s1StructType, "s");
  s1StructType = nullptr; //Invalidate
  Parameter* p = StructParameter("s2", "a",{new StructField(CTYPE_INT, "c"), new StructField(CTYPE_FLOAT, "d"), s1});
  s1 = nullptr; //Invalidate
  Parameter::Vector funParameter = {p};

  return funParameter;
}

Function StructFunStructFactory::functionFactory()
{
  Function f(functionGetFunctionName(), structFunStructReturnValue(), structFunStructParameters());
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

bool operator==(const struct s1 &lhs, const struct s1 &rhs)
{
  return lhs.a == rhs.a && lhs.b == rhs.b;
}

std::ostream& operator<<(std::ostream& os, const struct s1& c)
{
  return os << "a: " << c.a << " b: " << c.b;
}

std::ostream& operator<<(std::ostream& os, const struct s2& c)
{
  return os << "c: " << c.c << " d: " << c.d << " s1.a: " << c.s.a << " s1.b: " << c.s.b;
}
