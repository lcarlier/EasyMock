#ifndef EASYMOCK_FRAMEWORK_H
#define EASYMOCK_FRAMEWORK_H

#include <MockedFunction.h>

typedef struct
{
  const char *mockedFileName;
  void (*resetMockedFile) ();
  bool (*verifyMockedFile) ();
} easyMock_mockedFileRegister_t;

void easyMock_registerMock(const easyMock_mockedFileRegister_t *args);
const char *easyMock_popCurrentCall();
void easyMock_addError(bool callback, const char *fmt, ...);
void easyMock_addCall(const char *call);

#endif /* EASYMOCK_FRAMEWORK_H */

