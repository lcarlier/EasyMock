/*!
 * \file
 *
 * \brief This header defines the MockedFunction struct and the helper function
 * which is used by the mocked header code to help mocking a specific function.
 */
#ifndef MOCKEDFUNCTION_H
#define MOCKEDFUNCTION_H

#include <easyMock_framework.h>

#include <stddef.h>

#ifdef __cplusplus
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
  size_t dataSize;
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
void MockedFunction_init(MockedFunction *mf, const char* name, size_t dataSize);

/*!
 * \brief Add an expected call to the MockedFunction data.
 */
void MockedFunction_addExpectedCall(MockedFunction *mf, const void* data);

/*!
 * \brief Get the data of the current expected function call.
 */
bool MockedFunction_getCurrentCallParam(MockedFunction *mf, void* data);

/*!
 * \brief Add an actual call to the MockedFunction data.
 */
bool MockedFunction_addActualCall(MockedFunction *mf);

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
bool MockedFunction_verify(MockedFunction *mf);

#ifdef __cplusplus
}
#endif

#endif /* MOCKEDFUNCTION_H */

