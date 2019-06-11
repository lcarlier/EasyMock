#ifndef EASYMOCK_H
#define EASYMOCK_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>

#define EASYMOCK_MAX_CMP_ERR 256

#define EASYMOCK_MATCHER_PARAM void *currentCall_ptr, void *expectedCall_ptr, const char *paramName, char *errorMessage

  typedef int(*EasyMock_Matcher)(EASYMOCK_MATCHER_PARAM);

#define DECLARE_MATCHER(typeName) \
  int cmp_ ## typeName (EASYMOCK_MATCHER_PARAM)

  void easyMock_init();
  int easyMock_check();
  const char *easyMock_getErrorStr();
  void easyMock_printCallStack(bool val);
  void easyMock_checkFifoCall(bool val);

  DECLARE_MATCHER(char);
  DECLARE_MATCHER(u_char);
  DECLARE_MATCHER(short);
  DECLARE_MATCHER(u_short);
  DECLARE_MATCHER(int);
  DECLARE_MATCHER(u_int);
  DECLARE_MATCHER(long);
  DECLARE_MATCHER(u_long);
  DECLARE_MATCHER(long_long);
  DECLARE_MATCHER(u_long_long);
  DECLARE_MATCHER(float);
  DECLARE_MATCHER(double);
  DECLARE_MATCHER(long_double);

#ifdef __cplusplus
}
#endif

#endif /* EASYMOCK_H */

