/*!
 * \file
 *
 * \brief This header defines the MockedFunction struct and the helper function
 * which is used by the mocked header code to help mocking a specific function.
 */
#ifndef MOCKEDFUNCTION_H
#define MOCKEDFUNCTION_H

/*
 * We do not include header from the standard library because we want our header
 * to be used on file that are compiled with -nostdinc
 */

#include <easyMock_framework.h>

#ifdef __cplusplus

#include <vector>
#include <string>
/*!
 * \brief Struct encapsulating the data needed by a mocked C++ function.
 */
template <typename T>
struct MockedCppFunction
{
  /*!
   * \brief Name of the function.
   */
  const char *name;
  /*!
   * \brief Size of the element stored in mockedData.
   */
  easyMock_size_t dataSize;
  /*!
   * \brief Store the number of the expected call.
   */
  unsigned int expectedCall;
  /*!
   * \brief Store the number of the actual call done on the mocked function.
   */
  unsigned int actualCall;
  /*!
   * \brief Store the data of a mocked function call.
   *
   * The data contains:
   * - The return value
   * - The value of the expected parameters (if any)
   * - Pointers to compare the function parameters (if any)
   */
  std::vector<T> mockedData;
};

template<typename T>
unsigned int MockedFunction_getCurrentIdx(MockedCppFunction<T>* mf)
{
  if(mf->actualCall == 0)
  {
    fprintf(stderr, "C++: Bug in the framework. Getting the index with actuallCall == 0\n\r");
    exit(1);
  }
  return mf->actualCall - 1;
}

template<typename T>
void MockedFunction_init(MockedCppFunction<T> *mf, const char* name, easyMock_size_t dataSize)
{
  mf->name = name;
  mf->dataSize = dataSize;
  mf->actualCall = 0;
  mf->expectedCall = 0;
  mf->mockedData.clear();
}

template<typename T>
void MockedFunction_addExpectedCall(MockedCppFunction<T> *mf, T* data)
{
  mf->mockedData.push_back(*data);
  mf->expectedCall++;
}

template<typename T>
easyMock_bool MockedFunction_getCurrentCallParam(MockedCppFunction<T> *mf, T* data)
{
  if(mf->mockedData.empty())
  {
    return false;
  }
  unsigned int currentIdx = MockedFunction_getCurrentIdx(mf);
  if(currentIdx > mf->expectedCall)
  {
    fprintf(stderr, "C++: Bug in the framework. Get the call of an out of bound index\n\r");
    exit(1);
  }
  *data = mf->mockedData[currentIdx];

  return true;
}

template<typename T>
const char* MockedFunction_getName(MockedCppFunction<T> *mf)
{
  return mf->name;
}

template<typename T>
easyMock_bool MockedFunction_addActualCall(MockedCppFunction<T> *mf)
{
  /*
   * Increment the actualCall anyway because MockedFunction_verify()
   * will check the equality of m_actualCall and m_expectedCall
   */
  mf->actualCall++;
  if ((mf->actualCall - 1) >= mf->expectedCall)
  {
    return false;
  }
  return true;
}

template<typename T>
unsigned int MockedFunction_getNbActualCall(MockedCppFunction<T> *mf)
{
  return mf->actualCall;
}

template<typename T>
void MockedFunction_reset(MockedCppFunction<T> *mf)
{
  mf->expectedCall = 0;
  mf->actualCall = 0;
  mf->mockedData.clear();
}

template<typename T>
easyMock_bool MockedFunction_verify(MockedCppFunction<T> *mf)
{
  if (mf->expectedCall != mf->actualCall)
  {
    easyMock_addError(false, "Error: For function '%s' bad number of call. "
                             "Expected %d, got %d",
                             mf->name, mf->expectedCall, mf->actualCall);
    return false;
  }
  return true;
}

extern "C" {
#endif

#ifndef EASYMOCK_MAX_MOCKED_CALL
#define EASYMOCK_MAX_MOCKED_CALL 256
#endif

/*!
 * \brief Struct encapsulating the data needed by a mocked function.
 */
typedef struct
{
  /*!
   * \brief Name of the function.
   */
  const char* name;
  /*!
   * \brief Size of the element stored in mockedData.
   */
  easyMock_size_t dataSize;
  /*!
   * \brief Store the number of the expected call.
   */
  unsigned int expectedCall;
  /*!
   * \brief Store the number of the actual call done on the mocked function.
   */
  unsigned int actualCall;
  /*!
   * \brief Store the data of a mocked function call.
   *
   * The data contains:
   * - The return value
   * - The value of the expected parameters (if any)
   * - Pointers to compare the function parameters (if any)
   */
  void* mockedData[EASYMOCK_MAX_MOCKED_CALL];
} MockedFunction;

/*!
 * \brief Initialise a MockedFunction
 */
void MockedFunction_init(MockedFunction *mf, const char* name, easyMock_size_t dataSize);

/*!
 * \brief Add an expected call to the MockedFunction data.
 */
void MockedFunction_addExpectedCall(MockedFunction *mf, const void* data);

/*!
 * \brief Get the data of the current expected function call.
 */
easyMock_bool MockedFunction_getCurrentCallParam(MockedFunction *mf, void* data);

/*!
 * \brief Add an actual call to the MockedFunction data.
 */
easyMock_bool MockedFunction_addActualCall(MockedFunction *mf);

/*!
 * \brief Returns the number of actual call done on the mocked function.
 *
 * This function is used to print on the error message on which call number
 * the error is.
 */
unsigned int MockedFunction_getNbActualCall(MockedFunction *mf);

/*!
 * \brief Returns the signature of the mocked function.
 */
const char* MockedFunction_getName(MockedFunction *mf);

/*!
 * \brief Reset a MockedFunction
 *
 * - The number of expected and actual call are reset to 0.
 * - The potential mocked data currently stored in MockedFunction are cleared.
 */
void MockedFunction_reset(MockedFunction *mf);

/*!
 * \brief Verify the status of a mocked function.
 *
 * This function checks that:
 * - no errors are reported.
 * - the number of actual call is equal to the number of expected call
 */
easyMock_bool MockedFunction_verify(MockedFunction *mf);

#ifdef __cplusplus
}
#endif

#endif /* MOCKEDFUNCTION_H */

