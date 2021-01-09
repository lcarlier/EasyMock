#include "Int128FunUint128Factory.h"

#include <EasyMock_CType.h>
#include <ReturnValue.h>
#include <FunctionDeclaration.h>
#include <limits>

FunctionDeclaration Int128FunUint128Factory::functionFactory()
{
  return functionFactoryArray()[0];
}

ElementToMockList Int128FunUint128Factory::functionFactoryArray()
{
  ElementToMockList returnedList;
  CType* int128Type = new CType(CTYPE_INT128, "", false);
  ReturnValue rv(int128Type);
  CType* uint128Type = new CType(CTYPE_UINT128, "", false);
  CType* uint128Type_t = new CType(CTYPE_UINT128, "__uint128_t", false);
  CType* int128Type_t = new CType(CTYPE_INT128, "__int128_t", false);
  Parameter* uint128Parameter = new Parameter(uint128Type, "u");
  Parameter* uint128Parameter_t = new Parameter(uint128Type_t, "ut");
  Parameter* int128Parameter_t = new Parameter(int128Type_t, "it");

  {
    FunctionDeclaration *fd = new FunctionDeclaration(functionGetFunctionName(), rv, Parameter::Vector({uint128Parameter, uint128Parameter_t, int128Parameter_t}));
    returnedList.push_back(fd);
  }

  return returnedList;
}

std::string Int128FunUint128Factory::functionGetFunctionName()
{
  return std::string("int128FunUint128");
}

std::string Int128FunUint128Factory::getFilename()
{
  return "int128FunUint128.h";
}

void Int128FunUint128Factory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  unsigned __int128 aToExpect = std::numeric_limits<unsigned __int128>::max() - 64;
  __int128 rvToExpect = std::numeric_limits<__int128>::min() + 42;
  __uint128_t bToExpect = std::numeric_limits<__uint128_t>::min() + 42;
  __int128_t cToExpect = std::numeric_limits<__int128_t>::max() - 64;
  switch(tc)
  {
    case EasyMockTestCase::OneExpect:
      m_rvContext.m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect, bToExpect, cToExpect));
      m_params.push_back(std::make_tuple(aToExpect, bToExpect, cToExpect));
      m_compare.push_back(std::make_tuple(&cmp_uint128, &cmp_uint128, &cmp_int128));
      break;
    case EasyMockTestCase::ThreeExpects:
    {
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(rvToExpect + expectIdx);
        m_expects.push_back(std::make_tuple(aToExpect + expectIdx, bToExpect, cToExpect));
        m_params.push_back(std::make_tuple(aToExpect + expectIdx, bToExpect, cToExpect));
        m_compare.push_back(std::make_tuple(&cmp_uint128, &cmp_uint128, &cmp_int128));
      }
      break;
    }
    case EasyMockTestCase::OneExpectArgIsBad:
      m_rvContext.m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect, bToExpect, cToExpect));
      m_params.push_back(std::make_tuple(aToExpect + 1, bToExpect, cToExpect));
      m_compare.push_back(std::make_tuple(&cmp_uint128, &cmp_uint128, &cmp_int128));
      break;
    case EasyMockTestCase::SecondExpectArgIsBad:
      m_rvContext.m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect, bToExpect, cToExpect));
      m_params.push_back(std::make_tuple(aToExpect, bToExpect, cToExpect));
      m_compare.push_back(std::make_tuple(&cmp_uint128, &cmp_uint128, &cmp_int128));

      m_rvContext.m_rv.push_back(rvToExpect);
      m_expects.push_back(std::make_tuple(aToExpect, bToExpect, cToExpect));
      m_params.push_back(std::make_tuple(aToExpect + 1, bToExpect, cToExpect)); //second call fails
      m_compare.push_back(std::make_tuple(&cmp_uint128, &cmp_uint128, &cmp_int128));
      break;
    case EasyMockTestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(rvToExpect + expectIdx);
        m_expects.push_back(std::make_tuple(aToExpect + expectIdx, bToExpect, cToExpect));
        m_params.push_back(std::make_tuple(aToExpect + expectIdx, bToExpect, cToExpect));
        m_compare.push_back(std::make_tuple(&cmp_uint128, &cmp_uint128, &cmp_int128));
      }
      break;
    case EasyMockTestCase::NoExpect:
      break;
  }
}
