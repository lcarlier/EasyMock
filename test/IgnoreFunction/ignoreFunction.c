#include <easyMock_compileTwoFunctions.h>

void foo()
{
  struct twoFunStruct s = {0};
  compileTwoFunctions_ExpectAndReturn(s, 0, 0);
  f2_ExpectAndReturn(s, 0, 0);
}
