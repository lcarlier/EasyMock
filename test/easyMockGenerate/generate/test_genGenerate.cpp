#include <gtest/gtest.h> // googletest header file

#include <PrintObjects.h>
#include <easyMock.h>
#include <CodeGeneratorCTemplate.h>

#include <boost/algorithm/string.hpp>

#include "test_common.h"

#include <sstream>

#include <TestTypes.h>
#include <StructCommonHelper.h>
#include <UnionCommonHelper.h>

#include "genGenerate_testCase.h"

template<class T>
static std::string getElementOfTupleInsideQueue(const unsigned int idx, const T &theQueue);

template<class T>
static void printElIntoStream(std::ostringstream &s1, T* elem);

template<class T>
static void printElIntoStream(std::ostringstream &s1, T elem);

template <typename... Args,
typename std::enable_if<(sizeof...(Args) > 0), int>::type = 0>
static auto getFirstTupleElem(std::tuple<Args...>& t);

template <typename... Args,
typename std::enable_if<(sizeof...(Args) == 0), int>::type = 0>
static auto getFirstTupleElem(std::tuple<Args...>& t);

TYPED_TEST_CASE(genGenerate_testCase, GenerateTestTypes);

TYPED_TEST(genGenerate_testCase, OneExpect)
{
  void *fptr;
  void *fptr_expect;
  easyMockGenerate_baseTestCase::getFunPtr(&fptr, &fptr_expect);
  genGenerate_testCase<TypeParam>::m_factory.setupTestCase(EasyMockTestCase::OneExpect);
  genGenerate_testCase<TypeParam>::m_factory.call_fptr_expect(fptr_expect);
  auto expectedRv = genGenerate_testCase<TypeParam>::m_factory.get_expected_rv();
  auto rv = genGenerate_testCase<TypeParam>::m_factory.call_fptr(fptr);
  EXPECT_EQ(rv, expectedRv);
  int check = easyMock_check();
  EXPECT_EQ(check, 1);

  EASYMOCK_ASSERT_NO_ERROR;

  ASSERT_TRUE(isFifoCallEmpty());
}

template<typename TypeParam>
void genericExpectTest(const unsigned int nbCall, const unsigned int nbExpect, void *fptr, void *fptr_expect, EasyMockTestCase::TestCase tcToSetup)
{

  genGenerate_testCase<TypeParam>::m_factory.setupTestCase(tcToSetup);
  for(unsigned int expectIdx = 0; expectIdx < nbExpect; ++expectIdx)
  {
    genGenerate_testCase<TypeParam>::m_factory.call_fptr_expect(fptr_expect);
  }
  for(unsigned int callIdx = 0; callIdx < nbCall; ++callIdx)
  {
    auto expectedRv = genGenerate_testCase<TypeParam>::m_factory.get_expected_rv();
    auto rv = genGenerate_testCase<TypeParam>::m_factory.call_fptr(fptr);
    EXPECT_EQ(rv, expectedRv) << "call Idx " << callIdx;
  }
  int check = easyMock_check();
  EXPECT_EQ(check, 0);

  Function f = genGenerate_testCase<TypeParam>::m_factory.functionFactory();
  unsigned int size;
  const char **errorArr = easyMock_getErrorArr(&size);
  ASSERT_NE(errorArr, nullptr);
  const unsigned int nbErrors = nbCall - nbExpect + 1;
  ASSERT_EQ(size, nbErrors) << EasyMock_ErrorArrayPrinter(errorArr);

  for(unsigned int msgErrIdx = 0; msgErrIdx < nbErrors - 1; ++msgErrIdx)
  {
    //E.g: "Error : unexpected call of 'void voidFunVoid()'.\n\r\tat "
    std::string errorMessage1("Error : unexpected call of '");
    errorMessage1.append(f.getFunctionPrototype());
    errorMessage1.append("'");
    //E.g: "intFunIntInt is returning a random value
    if (*f.getReturnType() != VoidReturnValue())
    {
      errorMessage1.append(". ");
      errorMessage1.append(*f.getName());
      errorMessage1.append(" is returning a random value");
    }
#if defined(BACKTRACE_SUPPORT)
      errorMessage1.append(".\n\r\tat ");
#endif
    EXPECT_TRUE(boost::algorithm::starts_with(errorArr[msgErrIdx], errorMessage1))
            << "errorArr[" << msgErrIdx << "]: " << errorArr[msgErrIdx] << std::endl << "errorMessage1: " << errorMessage1;
  }

  //E.g: "Error: For function 'void voidFunVoid()' bad number of call. Expected 0, got 1"
  std::string errorMessage2("Error: For function '");
  errorMessage2.append(f.getFunctionPrototype());
  errorMessage2.append("' bad number of call. Expected ");
  errorMessage2.append(std::to_string(nbExpect));
  errorMessage2.append(", got ");
  errorMessage2.append(std::to_string(nbCall));
  const unsigned int lastErrorIdx = nbErrors - 1;
  EXPECT_STREQ(errorArr[lastErrorIdx], errorMessage2.c_str()) << "errorArr[" << lastErrorIdx << "]: " << errorArr[lastErrorIdx] << std::endl << "errorMessage2: " << errorMessage2;
  EXPECT_EQ(errorArr[nbErrors], nullptr);

  EXPECT_TRUE(isFifoCallEmpty());
}

TYPED_TEST(genGenerate_testCase, NoExpect)
{
  void *fptr;
  void *fptr_expect;
  const unsigned int nbCall = 3;

  easyMockGenerate_baseTestCase::getFunPtr(&fptr, &fptr_expect);
  genericExpectTest<TypeParam>(nbCall, 0, fptr, fptr_expect, EasyMockTestCase::NoExpect);
}

TYPED_TEST(genGenerate_testCase, NotEnoughExpect)
{
  void *fptr;
  void *fptr_expect;
  const unsigned int nbExpect = 3;
  const unsigned int nbCall = 5;

  easyMockGenerate_baseTestCase::getFunPtr(&fptr, &fptr_expect);
  genericExpectTest<TypeParam>(nbCall, nbExpect, fptr, fptr_expect, EasyMockTestCase::ThreeExpects);
}

TYPED_TEST(genGenerate_testCase, NotEnoughCall)
{
  void *fptr;
  void *fptr_expect;
  Function f = genGenerate_testCase<TypeParam>::m_factory.functionFactory();
  easyMockGenerate_baseTestCase::getFunPtr(&fptr, &fptr_expect);
  ASSERT_NE(fptr, nullptr);
  ASSERT_NE(fptr_expect, nullptr);
  genGenerate_testCase<TypeParam>::m_factory.setupTestCase(EasyMockTestCase::NotEnoughCall);
  genGenerate_testCase<TypeParam>::m_factory.call_fptr_expect(fptr_expect);
  genGenerate_testCase<TypeParam>::m_factory.call_fptr_expect(fptr_expect);
  genGenerate_testCase<TypeParam>::m_factory.call_fptr_expect(fptr_expect);
  genGenerate_testCase<TypeParam>::m_factory.call_fptr(fptr);
  genGenerate_testCase<TypeParam>::m_factory.call_fptr(fptr);
  int check = easyMock_check();
  EXPECT_EQ(check, 0);

  //E.g: Error: For function 'void voidFunVoid()' bad number of call. Expected 3, got 2
  std::string errorMessage1ToExpect("Error: For function '");
  errorMessage1ToExpect.append(f.getFunctionPrototype());
  errorMessage1ToExpect.append("' bad number of call. Expected 3, got 2");
  std::string errorMessage2ToExpect(errorMessage1ToExpect);
  errorMessage2ToExpect.append("\n\r");
  const char *error = easyMock_getErrorStr();
  ASSERT_NE(error, nullptr);
  ASSERT_STREQ(error, errorMessage2ToExpect.c_str()) << "error: " << error;

  unsigned int size;
  const char **errorArr = easyMock_getErrorArr(&size);
  ASSERT_NE(errorArr, nullptr);
  ASSERT_EQ(size, 1);
  ASSERT_STREQ(errorArr[0], errorMessage1ToExpect.c_str()) << "errorArr[0]: " << errorArr[0];
  ASSERT_EQ(errorArr[1], nullptr);

  ASSERT_FALSE(isFifoCallEmpty());
  ASSERT_EQ(fifoCallSize(), 1);
  const std::string& curCall = getCurrentFifoCall();
  ASSERT_STREQ(curCall.c_str(), f.getFunctionPrototype().c_str());
  genGenerate_testCase<TypeParam>::m_factory.clear_all_queues();
}

TYPED_TEST(genGenerate_testCase, ThreeExpects)
{
  void *fptr;
  void *fptr_expect;
  Function f = genGenerate_testCase<TypeParam>::m_factory.functionFactory();
  easyMockGenerate_baseTestCase::getFunPtr(&fptr, &fptr_expect);
  genGenerate_testCase<TypeParam>::m_factory.setupTestCase(EasyMockTestCase::ThreeExpects);

  const unsigned int NB_EXPECT = 3;

  for(unsigned int expect_nr = 0; expect_nr < NB_EXPECT; expect_nr++)
  {
    genGenerate_testCase<TypeParam>::m_factory.call_fptr_expect(fptr_expect);
  }

  for(unsigned int expect_nr = 0; expect_nr < NB_EXPECT; expect_nr++)
  {
    auto expectedRv = genGenerate_testCase<TypeParam>::m_factory.get_expected_rv();
    auto rv = genGenerate_testCase<TypeParam>::m_factory.call_fptr(fptr);
    EXPECT_EQ(rv, expectedRv) << "with expect_nr == " << ::testing::PrintToString(expect_nr) << " " << ::testing::PrintToString(rv) << " " << ::testing::PrintToString(expectedRv);
  }

  int check = easyMock_check();
  EXPECT_EQ(check, 1);

  EASYMOCK_ASSERT_NO_ERROR;

  ASSERT_TRUE(isFifoCallEmpty());
}

TYPED_TEST(genGenerate_testCase, OneExpectArgIsBad)
{
  void *fptr;
  void *fptr_expect;
  Function f = genGenerate_testCase<TypeParam>::m_factory.functionFactory();
  if(f.getFunctionsParameters().size() == 0)
  {
    return; //In case the function that is tested doesn't have any parameters
  }

  Parameter::Vector::const_iterator it = f.getFunctionsParameters().begin();
  const Parameter *firstParameter = *it;
  if(!firstParameter->getType()->isCType())
  {
    return; //For struct and classes, error message is fine tuned and this generic test case is not used
  }
  easyMockGenerate_baseTestCase::getFunPtr(&fptr, &fptr_expect);
  genGenerate_testCase<TypeParam>::m_factory.setupTestCase(EasyMockTestCase::OneExpectArgIsBad);

  /*
   * A lot of assumption here to be met partially by the setupTestCase function.
   * 1. The queue returns are types std::queue<std::tuple<Params...>>
   * 2. There is at least 1 element in the queue. The rest is ignored
   * 3. The first element of the tuple contains the parameter to be expected and actually given to the mock
   *    Those values differs because this test tests explicitly the error case
   *
   * We need to check the queues after setupTestCase and before the call_fptr_expect function has been called.
   */
  std::string givenParemeter = getElementOfTupleInsideQueue(0, genGenerate_testCase<TypeParam>::m_factory.get_params_queue());
  std::string expectedParemeter = getElementOfTupleInsideQueue(0, genGenerate_testCase<TypeParam>::m_factory.get_expects_queue());

  genGenerate_testCase<TypeParam>::m_factory.call_fptr_expect(fptr_expect);
  auto expectedRv = genGenerate_testCase<TypeParam>::m_factory.get_expected_rv();
  auto rv = genGenerate_testCase<TypeParam>::m_factory.call_fptr(fptr);
  EXPECT_EQ(rv, expectedRv);

  int check = easyMock_check();
  EXPECT_EQ(check, 0);

  //E.g: Error : at call 1 of 'int intFunIntInt(int a, int b)': Parameter 'a' has value '255', was expecting '5'\n\r\tat 
  std::string errorMessageToExpect("Error : at call 1 of '");
  errorMessageToExpect.append(f.getFunctionPrototype());
  errorMessageToExpect.append("': Parameter '");
  errorMessageToExpect.append(firstParameter->getName());
  errorMessageToExpect.append("' has value '");
  errorMessageToExpect.append(givenParemeter);
  errorMessageToExpect.append("', was expecting '");
  errorMessageToExpect.append(expectedParemeter);
#if defined(BACKTRACE_SUPPORT)
  errorMessageToExpect.append("'\n\r\tat ");
#endif

  const char *error = easyMock_getErrorStr();
  ASSERT_NE(error, nullptr);
  ASSERT_TRUE(boost::algorithm::starts_with(error, errorMessageToExpect.c_str())) << "error: " << error << std::endl << "errorMessageToExpect: " << errorMessageToExpect;

  unsigned int size;
  const char **errorArr = easyMock_getErrorArr(&size);
  ASSERT_NE(errorArr, nullptr);
  ASSERT_EQ(size, 1) << EasyMock_ErrorArrayPrinter(errorArr);
  ASSERT_TRUE(boost::algorithm::starts_with(errorArr[0], errorMessageToExpect.c_str())) << "errorArr[0]: " << errorArr[0] << std::endl << "errorMessageToExpect: " << errorMessageToExpect;
  ASSERT_EQ(errorArr[1], nullptr) << "errorArr[1]: " << errorArr[1];

  ASSERT_TRUE(isFifoCallEmpty());
}

TYPED_TEST(genGenerate_testCase, SecondExpectArgIsBad)
{
  void *fptr;
  void *fptr_expect;
  Function f = genGenerate_testCase<TypeParam>::m_factory.functionFactory();
  if(f.getFunctionsParameters().size() == 0)
  {
    return; //In case the function that is tested doesn't have any parameters
  }

  Parameter::Vector::const_iterator it = f.getFunctionsParameters().begin();
  const Parameter *firstParameter = *it;
  if(!firstParameter->getType()->isCType())
  {
    return; //For struct and classes, error message is fine tuned and this generic test case is not used
  }
  easyMockGenerate_baseTestCase::getFunPtr(&fptr, &fptr_expect);
  genGenerate_testCase<TypeParam>::m_factory.setupTestCase(EasyMockTestCase::SecondExpectArgIsBad);

  /*
   * A lot of assumption here to be met partially by the setupTestCase function.
   * 1. The queue returns are types std::queue<std::tuple<Params...>>
   * 2. There qre at least 2 element in the queue. The rest is ignored
   * 3. The first element of the tuple contains the parameter to be expected and actually given to the mock
   *    Those values differs because this test tests explicitly the error case
   *
   * We need to check the queues after setupTestCase and before the call_fptr_expect function has been called.
   */
  std::string givenParemeter = getElementOfTupleInsideQueue(1, genGenerate_testCase<TypeParam>::m_factory.get_params_queue());
  std::string expectedParemeter = getElementOfTupleInsideQueue(1, genGenerate_testCase<TypeParam>::m_factory.get_expects_queue());

  genGenerate_testCase<TypeParam>::m_factory.call_fptr_expect(fptr_expect);
  genGenerate_testCase<TypeParam>::m_factory.call_fptr_expect(fptr_expect);

  auto expectedRv = genGenerate_testCase<TypeParam>::m_factory.get_expected_rv();
  auto rv = genGenerate_testCase<TypeParam>::m_factory.call_fptr(fptr);
  EXPECT_EQ(rv, expectedRv);

  expectedRv = genGenerate_testCase<TypeParam>::m_factory.get_expected_rv();
  rv = genGenerate_testCase<TypeParam>::m_factory.call_fptr(fptr);
  EXPECT_EQ(rv, expectedRv);

  int check = easyMock_check();
  EXPECT_EQ(check, 0);

  //E.g: Error : at call 1 of 'int intFunIntInt(int a, int b)': Parameter 'a' has value '255', was expecting '5'\n\r\tat
  std::string errorMessageToExpect("Error : at call 2 of '");
  errorMessageToExpect.append(f.getFunctionPrototype());
  errorMessageToExpect.append("': Parameter '");
  errorMessageToExpect.append(firstParameter->getName());
  errorMessageToExpect.append("' has value '");
  errorMessageToExpect.append(givenParemeter);
  errorMessageToExpect.append("', was expecting '");
  errorMessageToExpect.append(expectedParemeter);
#if defined(BACKTRACE_SUPPORT)
  errorMessageToExpect.append("'\n\r\tat ");
#endif

  const char *error = easyMock_getErrorStr();
  ASSERT_NE(error, nullptr);
  ASSERT_TRUE(boost::algorithm::starts_with(error, errorMessageToExpect.c_str())) << "error: " << error << std::endl << "errorMessageToExpect: " << errorMessageToExpect;

  unsigned int size;
  const char **errorArr = easyMock_getErrorArr(&size);
  ASSERT_NE(errorArr, nullptr);
  ASSERT_EQ(size, 1) << EasyMock_ErrorArrayPrinter(errorArr);
  ASSERT_TRUE(boost::algorithm::starts_with(errorArr[0], errorMessageToExpect.c_str())) << "errorArr[0]: " << errorArr[0] << std::endl << "errorMessageToExpect: " << errorMessageToExpect;
  ASSERT_EQ(errorArr[1], nullptr) << "errorArr[1]: " << errorArr[1];

  ASSERT_TRUE(isFifoCallEmpty());
}

template<class T>
static std::string getElementOfTupleInsideQueue(const unsigned int idx, const T &theQueue)
{
  auto firstElem = theQueue[idx];
  auto elem = getFirstTupleElem(firstElem);
  std::ostringstream s1;
  printElIntoStream(s1, elem);
  return s1.str();
}

template <typename... Args,
typename std::enable_if<(sizeof...(Args) > 0), int>::type>
static auto getFirstTupleElem(std::tuple<Args...>& t)
{
  return std::get<0>(t);
}

template <typename... Args,
typename std::enable_if<(sizeof...(Args) == 0), int>::type>
static auto getFirstTupleElem(std::tuple<Args...>& t)
{
  return 0;
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
