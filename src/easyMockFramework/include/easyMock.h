#ifndef EASYMOCK_H
#define EASYMOCK_H

#ifdef __cplusplus
extern "C"
{
#endif

  void easyMock_init();
  int easyMock_check();
  const char *easyMock_getErrorStr();

#ifdef __cplusplus
}
#endif

#endif /* EASYMOCK_H */

