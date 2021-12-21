#include <easyMock_compileTwoFunctions.h>

void foo()
{
  struct twoFunStruct s = {0};
  compileTwoFunctions_ExpectAndReturn(s, 0, cmp_struct_twoFunStruct);
  f2_ExpectAndReturn(s, 0, cmp_struct_twoFunStruct);
}
