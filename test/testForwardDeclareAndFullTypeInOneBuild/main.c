#include <easyMock_forwardDeclare.h>
#include <easyMock_fullDeclaration.h>

#include <stdio.h>

int main(int argc, char* argv[])
{
  struct myStruct a;
  a.a = 4;
  printf("hello world %d\n", a.a);
  return 0;
}