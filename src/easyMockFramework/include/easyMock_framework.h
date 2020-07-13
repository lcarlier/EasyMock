/*! \file
 * \brief This header file contains the interface that is used by the generated
 * mocked function I.e. the code generated by EasyMockGenerate
 */
#ifndef EASYMOCK_FRAMEWORK_H
#define EASYMOCK_FRAMEWORK_H

#include <string>

/*!
 * \brief Type defining the information needed by a header file to register
 * itself to libEasyMockFramework.so
 */
typedef struct
{
  /*!
   * \brief The name of the header file
   */
  const char *mockedFileName;
  /*!
   * \brief Callback function to reset all the mock of the mocked header file.
   *
   * This callback is called by easyMock_init().
   */
  void (*resetMockedFile) ();
  /*!
   * \brief Callback function to verify whether mocks of the header file have
   * been called the expected amount of time.
   *
   * This callback is called by easyMock_check().
   */
  bool (*verifyMockedFile) ();
} easyMock_mockedFileRegister_t;

/*!
 * \brief Registers a header file to libEasyMockFramework.so
 *
 * This function is called automatically by the mocked header code whenever
 * the mock is loaded using the GCC attribute of function `constructor`
 *
 * \see [GCC Declaring Attributes of Functions](https://gcc.gnu.org/onlinedocs/gcc-4.7.0/gcc/Function-Attributes.html)
 * \see [main architectural page](md_docs_architecture.html#user-content-romtl)
 */
void easyMock_registerMockedFile(const easyMock_mockedFileRegister_t *args);
/*!
 * \brief Unregister a header file to libEasyMockFramework.so
 *
 * This function is called automatically by the mocked header code whenever
 * the mock is unloaded using the GCC attribute of function `destructor`
 *
 * \see [GCC Declaring Attributes of Functions](https://gcc.gnu.org/onlinedocs/gcc-4.7.0/gcc/Function-Attributes.html)
 * \see [main architectural page](md_docs_architecture.html#user-content-romtl)
 */
void easyMock_unregisterMockedFile(const easyMock_mockedFileRegister_t *args);
/*!
 * \brief Adds an expected call to the EasyMock expected call stack.
 *
 * This function is called by the mocked header code whenever a function from
 * the `*_ExpectAndReturn*` family is called.
 */
void easyMock_addCall(const std::string call);
/*!
 * \brief Removes an expected call from EasyMock expected call stack.
 *
 * This function is called by the mocked header code whenever a function from
 * the mocked function is called from the code being tested.
 */
std::string easyMock_popCurrentCall();
/*!
 * \brief Reports an error to EasyMock.
 *
 * This function is called by the mocked header code whenever an error has
 * to be reported.
 */
void easyMock_addError(bool callback, const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
/*!
 * \brief Returns whether the order of call of mocked function must be checked.
 *
 * This function is called by the mocked header code to report an error if the
 * wrong function was called.
 */
bool easyMock_checkCallsOrder();
/*!
 * \brief Returns whether the call stack must be part of the error messages.
 */
bool easyMock_printCallStack();

#endif /* EASYMOCK_FRAMEWORK_H */

