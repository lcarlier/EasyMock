#include <easyMock_ignoreTypeField.h>

void foo()
{
  struct container_type_to_ignore s;
  s.b = 42;
  s.a.a = 42;
  (void)s;
}
