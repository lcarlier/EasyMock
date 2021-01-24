#include <easyMock_glueStdlib.h>

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

void *easyMock_memcpy(void *__dst, const void *__src, easyMock_size_t __n)
{
  return memcpy(__dst, __src, __n);
}

int easyMock_snprintf (char *__restrict __s, easyMock_size_t __maxlen, const char *__restrict __format, ...)
{
  va_list arglist;
  va_start( arglist, __format );
  int rv = vsnprintf(__s, __maxlen, __format, arglist);
  va_end(arglist);
  return rv;
}
