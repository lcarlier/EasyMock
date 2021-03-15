/*!
 * \file
 *
 * \brief Contains functions to glue the mock to the C stdlib
 *
 * The glue is used by the generated mocks to have access to some C stdlib functionality without having to actually
 * including the header file. The functions are then linked to the final binaries via the libEasyMockFramework.so.
 *
 * This is useful when EasyMock is used with the generate types option.
 */
#ifndef EASYMOCK_GLUESTDLIB_H
#define EASYMOCK_GLUESTDLIB_H

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \brief EasyMock type for boolean
 */
typedef unsigned easyMock_bool;

/*!
 * \brief EasyMock type for size_t
 */
typedef unsigned easyMock_size_t;

/*!
 * \brief EasyMock representation of boolean true
 */
#define easyMock_true (1)

/*!
 * \brief EasyMock representation of boolean false
 */
#define easyMock_false (0)

/*!
 * \brief EasyMock representation of NULL
 */
#define easyMock_null (0)

/*!
 * \brief see man memcpy
 */
extern void *easyMock_memcpy(void *__dst, const void *__src, easyMock_size_t __n);

/*!
 * \brief see man 3 printf
 */
extern int easyMock_snprintf(char *__restrict __s, easyMock_size_t __maxlen, const char *__restrict __format, ...) __attribute__ ((__format__ (__printf__, 3, 4)));

#ifdef __cplusplus
}
#endif

#endif /* EASYMOCK_GLUESTDLIB_H */
