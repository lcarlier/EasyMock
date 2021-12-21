#include <easyMock_structAnonymousTypedDefFunStructAnonymousTypedDef.h>

void foo()
{
  TypedDefAnonymousStruct p1 = {0};
  TypedDefAnonymousStruct2 p2 = {0};
  TypedDefAnonymousStruct ret = {0};
  structAnonymousTypedDefFunStructAnonymousTypedDef_ExpectAndReturn(p1, p2, ret, cmp_TypedDefAnonymousStruct, cmp_TypedDefAnonymousStruct);
}
