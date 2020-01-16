#include <gtest/gtest.h> // googletest header file

#include <easyMock.h>
#include <CodeGeneratorCTemplate.h>

#include <boost/algorithm/string.hpp>

#include "test_common.h"
#include "TypeItf.h"

#include <sstream>

#include <TestTypes.h>


static std::string getElementOfTupleInsideQueue(const unsigned int idx, const auto &theQueue);
static void printElIntoStream(std::ostringstream &s1, auto* elem);
static void printElIntoStream(std::ostringstream &s1, auto elem);

template <typename... Args,
typename std::enable_if<(sizeof...(Args) > 0), int>::type = 0>
static auto getFirstTupleElem(std::tuple<Args...>& t);

template <typename... Args,
typename std::enable_if<(sizeof...(Args) == 0), int>::type = 0>
static auto getFirstTupleElem(std::tuple<Args...>& t);

template<class T>
class genGenerate_testCase : public easyMockGenerate_baseTestCase
{
public:
  genGenerate_testCase() : easyMockGenerate_baseTestCase(m_factory.functionGetFunctionName(), m_factory.functionGetIncludeDir(), m_factory.functionGetMockDir())
  {
    ElementToMock *f = m_factory.newFunctionFactory();
    m_elem.push_back(f);
  }

  void ExtraTearDown() override
  {
    ASSERT_TRUE(m_factory.is_rv_queue_empty());
    ASSERT_TRUE(m_factory.is_expect_rv_cur_call_queue_empty());
    ASSERT_TRUE(m_factory.is_params_queue_empty());
    ASSERT_TRUE(m_factory.is_expects_queue_empty());
    ASSERT_TRUE(m_factory.is_compare_queue_empty());
  }

  static T m_factory;
};

template<class T>
T genGenerate_testCase<T>::m_factory;

TYPED_TEST_CASE(genGenerate_testCase, TestTypes);

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

  ASSERT_NO_ERROR;

  ASSERT_TRUE(isFifoCallEmpty());
}

TYPED_TEST(genGenerate_testCase, NoExpect)
{
  void *fptr;
  void *fptr_expect;

  easyMockGenerate_baseTestCase::getFunPtr(&fptr, &fptr_expect);
  genGenerate_testCase<TypeParam>::m_factory.setupTestCase(EasyMockTestCase::NoExpect);
  genGenerate_testCase<TypeParam>::m_factory.call_fptr(fptr);
  int check = easyMock_check();
  EXPECT_EQ(check, 0);

  Function f = genGenerate_testCase<TypeParam>::m_factory.functionFactory();
  unsigned int size;
  const char **errorArr = easyMock_getErrorArr(&size);
  ASSERT_NE(errorArr, nullptr);
  ASSERT_EQ(size, 2) << EasyMock_ErrorArrayPrinter(errorArr);

  //E.g: "Error : unexpected call of 'void voidFunVoid()'.\n\r\tat EasyMock::addError"
  std::string errorMessage1("Error : unexpected call of '");
  errorMessage1.append(f.getFunctionPrototype());
  errorMessage1.append("'");
  //E.g: "intFunIntInt is returning a random value
  if(*f.getReturnType() != VoidReturnValue())
  {
    errorMessage1.append(". ");
    errorMessage1.append(*f.getName());
    errorMessage1.append(" is returning a random value");
  }
  errorMessage1.append(".\n\r\tat EasyMock::addError");
  ASSERT_TRUE(boost::algorithm::starts_with(errorArr[0], errorMessage1)) << "errorArr[0]: " << errorArr[0] << std::endl << "errorMessage1: " << errorMessage1;

  //E.g: "Error: For function 'void voidFunVoid()' bad number of call. Expected 0, got 1"
  std::string errorMessage2("Error: For function '");
  errorMessage2.append(f.getFunctionPrototype());
  errorMessage2.append("' bad number of call. Expected 0, got 1");
  ASSERT_STREQ(errorArr[1], errorMessage2.c_str()) << "errorArr[1]: " << errorArr[1] << std::endl << "errorMessage2: " << errorMessage2;
  ASSERT_EQ(errorArr[2], nullptr);

  ASSERT_TRUE(isFifoCallEmpty());
}

TYPED_TEST(genGenerate_testCase, NotEnoughCall)
{
  void *fptr;
  void *fptr_expect;
  Function f = genGenerate_testCase<TypeParam>::m_factory.functionFactory();
  easyMockGenerate_baseTestCase::getFunPtr(&fptr, &fptr_expect);
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
  std::string curCall = getCurrentFifoCall();
  ASSERT_STREQ(curCall.c_str(), f.getFunctionPrototype().c_str());
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
    EXPECT_EQ(rv, expectedRv) << "with expect_nr == " << expect_nr << " " << rv << " " << expectedRv;
  }

  int check = easyMock_check();
  EXPECT_EQ(check, 1);

  ASSERT_NO_ERROR;

  ASSERT_TRUE(isFifoCallEmpty());
}

TYPED_TEST(genGenerate_testCase, OneExpectArgIsBad)
{
  void *fptr;
  void *fptr_expect;
  Function f = genGenerate_testCase<TypeParam>::m_factory.functionFactory();
  if(f.getFunctionsParameters()->size() == 0)
  {
    return; //In case the function that is tested doesn't have any parameters
  }

  Parameter::Vector::const_iterator it = f.getFunctionsParameters()->begin();
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

  //E.g: Error : at call 1 of 'int intFunIntInt(int a, int b)': Parameter 'a' has value '255', was expecting '5'\n\r\tat EasyMock::addError
  std::string errorMessageToExpect("Error : at call 1 of '");
  errorMessageToExpect.append(f.getFunctionPrototype());
  errorMessageToExpect.append("': Parameter '");
  errorMessageToExpect.append(firstParameter->getName());
  errorMessageToExpect.append("' has value '");
  errorMessageToExpect.append(givenParemeter);
  errorMessageToExpect.append("', was expecting '");
  errorMessageToExpect.append(expectedParemeter);
  errorMessageToExpect.append("'\n\r\tat EasyMock::addError");

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
  if(f.getFunctionsParameters()->size() == 0)
  {
    return; //In case the function that is tested doesn't have any parameters
  }

  Parameter::Vector::const_iterator it = f.getFunctionsParameters()->begin();
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
   * 2. There is at least 2 element in the queue. The rest is ignored
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

  //E.g: Error : at call 1 of 'int intFunIntInt(int a, int b)': Parameter 'a' has value '255', was expecting '5'\n\r\tat EasyMock::addError
  std::string errorMessageToExpect("Error : at call 2 of '");
  errorMessageToExpect.append(f.getFunctionPrototype());
  errorMessageToExpect.append("': Parameter '");
  errorMessageToExpect.append(firstParameter->getName());
  errorMessageToExpect.append("' has value '");
  errorMessageToExpect.append(givenParemeter);
  errorMessageToExpect.append("', was expecting '");
  errorMessageToExpect.append(expectedParemeter);
  errorMessageToExpect.append("'\n\r\tat EasyMock::addError");

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

static std::string getElementOfTupleInsideQueue(const unsigned int idx, const auto &theQueue)
{
  auto firstElem = theQueue[idx];
  auto elem = getFirstTupleElem(firstElem);
  std::ostringstream s1;
  printElIntoStream(s1, elem);
  return s1.str();
}

template <typename... Args,
typename std::enable_if<(sizeof...(Args) > 0), int>::type = 0>
static auto getFirstTupleElem(std::tuple<Args...>& t)
{
  return std::get<0>(t);
}

template <typename... Args,
typename std::enable_if<(sizeof...(Args) == 0), int>::type = 0>
static auto getFirstTupleElem(std::tuple<Args...>& t)
{
  return 0;
}

/*
 * When auto is char* or unsigned char*, the ostringstream class
 * is (too) smart and try to derefence the pointer. In the UT in general
 * I provide dummy pointers with dummy addresses.
 * Since I'm only interested in the value of the pointer (not to what it
 * points), I have a redefinition of printElIntoStream which cast the pointer
 * to void* and is selected whenever elem is a pointer of any type.
 */
static void printElIntoStream(std::ostringstream &s1, auto* elem)
{
    s1 << (void*)elem;
}

static void printElIntoStream(std::ostringstream &s1, auto elem)
{
  s1 << std::fixed << std::setprecision(6) << elem;
}