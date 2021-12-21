#include <easyMock_structFunStruct.h>

void foo()
{
  struct s2 s2 = {0};
  struct onelineStruct oneLine = {0};
  struct s1 s1 = {0};
  structFunStruct_ExpectAndReturn(s2, oneLine, s1, cmp_struct_s2, cmp_struct_onelineStruct);
}
