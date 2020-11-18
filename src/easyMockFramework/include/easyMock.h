/*!
 * \file
 *
 * \brief This header file contains the interface that can be used by the unit tests
 * using EasyMock.
 */
#ifndef EASYMOCK_H
#define EASYMOCK_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>

  /*!
   * \brief Defines the maximum size of an error message.
   */
#define EASYMOCK_MAX_CMP_ERR 256

  /*!
   * \brief Helper macro to defines the parameter given to a comparator function.
   *
   * This macro can be used in the following way:
   *
   * int my_comparator(EASYMOCK_MATCHER_PARAM)
   * {
   *   //Do your business
   * }
   *
   * \see EasyMock_Matcher
   */
#define EASYMOCK_MATCHER_PARAM void *currentCall_ptr, void *expectedCall_ptr, const char *paramName, char *errorMessage

  /*!
   * \brief Aliases the type of a function pointer to a comparator.
   */
  typedef int(*EasyMock_Matcher)(EASYMOCK_MATCHER_PARAM);

  /*!
   * \brief Helper macro used to declare a function of a specific type.
   */
#define DECLARE_MATCHER(typeName) \
  int cmp_ ## typeName (EASYMOCK_MATCHER_PARAM)

  /*!
   * \brief Initialises EasyMock.
   *
   * This function must be called at the beginning of every test case.
   */
  void easyMock_init();

  /*!
   * \brief Checks that EasyMock has reported at least one error.
   *
   * This must called at the end of a unit test after the function being tested
   * has been called. If an error has happened, the API easyMock_getError* can be
   * used to retrieve the error messages.
   *
   * \return 1 if no error has happened.
   * \return 0 if at least an error has happened.
   */
  int easyMock_check();

  /*!
   * \brief Returns all the errors in a single buffer.
   *
   * The buffer can directly printed to the standard output if needed.
   *
   * The returned buffer must not be freed by the caller.
   */
  const char *easyMock_getErrorStr();

  /*!
   * \brief Returns all the errors in an array of pointer to constant array of characters.
   *
   * The parameter size is an output value which tells how many errors
   * are reported into the array.
   *
   * The returned buffer must not be freed by the caller.
   */
  const char ** easyMock_getErrorArr(unsigned int *size);

  /*!
   * \brief Sets whether the error messages should contain the call stack or not.
   *
   * The default is to print the callstack into the error messages.
   */
  void easyMock_setPrintCallStack(bool val);

  /*!
   * \brief Sets whether the mock should verify if the mocks have been called in the
   * order they have been expected.
   *
   * The default is to check that the mocks have been called in the order they
   * have been expected (via the *_ExpectAndReturn* API)
   */
  void easyMock_setCheckCallsOrder(bool val);

  /*!
   * \brief Comparator to be used to compare char type.
   */
  DECLARE_MATCHER(char);
  /*!
   * \brief Comparator to be used to compare unsigned char type.
   */
  DECLARE_MATCHER(u_char);
  /*!
   * \brief Comparator to be used to compare short type.
   */
  DECLARE_MATCHER(short);
  /*!
   * \brief Comparator to be used to compare unsigned char type.
   */
  DECLARE_MATCHER(u_short);
  /*!
   * \brief Comparator to be used to compare int type.
   */
  DECLARE_MATCHER(int);
  /*!
   * \brief Comparator to be used to compare unsigned int type.
   */
  DECLARE_MATCHER(u_int);
  /*!
   * \brief Comparator to be used to compare char type.
   */
  DECLARE_MATCHER(long);
  /*!
   * \brief Comparator to be used to compare long type.
   */
  DECLARE_MATCHER(u_long);
  /*!
   * \brief Comparator to be used to compare unsigned long type.
   */
  DECLARE_MATCHER(long_long);
  /*!
   * \brief Comparator to be used to compare long long type.
   */
  DECLARE_MATCHER(u_long_long);
  /*!
   * \brief Comparator to be used to compare unsigned long long type.
   */
  DECLARE_MATCHER(float);
  /*!
   * \brief Comparator to be used to compare float type.
   */
  DECLARE_MATCHER(double);
  /*!
   * \brief Comparator to be used to compare double type.
   */
  DECLARE_MATCHER(long_double);
  /*!
   * \brief Comparator to be used to compare long double type.
   */
  DECLARE_MATCHER(pointer);
  /*!
   * \brief Comparator to be used to compare pointer type.
   *
   * This will compare the value of the pointer, not the pointed value.
   */

  /*!
   * \brief Comparator to be used to compare C string/
   */
  int cmp_str( void *currentCall_ptr, void *expectedCall_ptr, const char *paramName, char *errorMessage );

#ifdef __cplusplus
}
#endif

#endif /* EASYMOCK_H */

