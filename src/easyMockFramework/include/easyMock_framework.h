#ifndef EASYMOCK_FRAMEWORK_H
#define EASYMOCK_FRAMEWORK_H

#include <MockedFunction.h>
#include <string>

typedef struct
{
  const char *mockedFileName;
  void (*resetMockedFile) ();
  bool (*verifyMockedFile) ();
} easyMock_mockedFileRegister_t;

void easyMock_registerMock(const easyMock_mockedFileRegister_t *args);
void easyMock_unregisterMock(const easyMock_mockedFileRegister_t *args);
std::string easyMock_popCurrentCall();
void easyMock_addError(bool callback, const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
void easyMock_addCall(const std::string call);

#endif /* EASYMOCK_FRAMEWORK_H */

