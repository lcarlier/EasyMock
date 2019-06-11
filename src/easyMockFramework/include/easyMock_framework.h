#ifndef EASYMOCK_FRAMEWORK_H
#define EASYMOCK_FRAMEWORK_H

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
bool easyMock_checkFifoCall();
bool easyMock_printCallStack();

#endif /* EASYMOCK_FRAMEWORK_H */

