#ifndef EASYMOCK_GLUESTDLIB_H
#define EASYMOCK_GLUESTDLIB_H

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned easyMock_bool;
typedef unsigned easyMock_size_t;
#define easyMock_true (1)
#define easyMock_false (0)
#define easyMock_null (0)

extern void *easyMock_memcpy(void *__dst, const void *__src, easyMock_size_t __n);
extern int easyMock_snprintf (char *__restrict __s, easyMock_size_t __maxlen, const char *__restrict __format, ...) __attribute__ ((__format__ (__printf__, 3, 4)));

#ifdef __cplusplus
}
#endif

#endif /* EASYMOCK_GLUESTDLIB_H */

