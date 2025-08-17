#ifndef EASYMOCK_TEST_GENGENERATECOMMON_H
#define EASYMOCK_TEST_GENGENERATECOMMON_H

#include <sstream>
#include <iomanip>

#include "genGenerate_testCase.h"
#include "test_common.h"

template<int v, class T>
static std::string getElementOfTupleInsideQueue(const unsigned int idx, const T &theQueue);

template<class T>
static void printElIntoStream(std::ostringstream &s1, T* elem);

template<class T>
static void printElIntoStream(std::ostringstream &s1, T elem);

template <int v, typename... Args,
    typename std::enable_if<(sizeof...(Args) > 0), int>::type = 0>
static auto getTupleElem(std::tuple<Args...>& t);

template <int v, typename... Args,
    typename std::enable_if<(sizeof...(Args) == 0), int>::type = 0>
static auto getTupleElem(std::tuple<Args...>& t);

template<typename TypeParam, typename TestCaseType>
void OneExpectTest(easyMockGenerate_baseTestCase& tc_class, TestCaseType tc)
{
  void *fptr;
  void *fptr_expect;
  tc_class.getFunPtr(&fptr, &fptr_expect);
  genGenerate_testCase<TypeParam>::m_factory.setupTestCase(tc);
  genGenerate_testCase<TypeParam>::m_factory.call_fptr_expect(fptr_expect);
  auto expectedRv = genGenerate_testCase<TypeParam>::m_factory.get_expected_rv();
  auto rv = genGenerate_testCase<TypeParam>::m_factory.call_fptr(fptr);
  EXPECT_EQ(rv, expectedRv);
  int check = easyMock_check();
  EXPECT_EQ(check, 1);

  EASYMOCK_ASSERT_NO_ERROR;

  ASSERT_TRUE(isFifoCallEmpty());
}


template<int v, class T>
static std::string getElementOfTupleInsideQueue(const unsigned int idx, const T &theQueue)
{
  static_assert(v >= 0 && v <= 1);
  auto firstElem = theQueue[idx];
  auto elem = getTupleElem<v>(firstElem);
  std::ostringstream s1;
  printElIntoStream(s1, elem);
  return s1.str();
}

/*
 * When T is char* or unsigned char*, the ostringstream class
 * is (too) smart and try to dereference the pointer. In the UT in general
 * I provide dummy pointers with dummy addresses.
 * Since I'm only interested in the value of the pointer (not to what it
 * points), I have a redefinition of printElIntoStream which cast the pointer
 * to void* and is selected whenever elem is a pointer of any type.
 */
template<class T>
static void printElIntoStream(std::ostringstream &s1, T* elem)
{
  s1 << (void*)elem;
}

template<class T>
static void printElIntoStream(std::ostringstream &s1, T elem)
{
  s1 << std::fixed << std::setprecision(6) << elem;
}

template <int v, typename... Args,
    typename std::enable_if<(sizeof...(Args) > 0), int>::type>
static auto getTupleElem(std::tuple<Args...>& t)
{
  return std::get<v>(t);
}

template <int v, typename... Args,
    typename std::enable_if<(sizeof...(Args) == 0), int>::type>
static auto getTupleElem(std::tuple<Args...>& t)
{
  return 0;
}

#endif //EASYMOCK_TEST_GENGENERATECOMMON_H
