#ifndef VOIDFUNSTRUCTWITHCONSTMEMBER_H
#define VOIDFUNSTRUCTWITHCONSTMEMBER_H

#ifdef __cplusplus
extern "C" {
#endif

struct structWithConstMember
{
  char const* f;
  short const f2;
};

void voidFunStructWithConstMember(struct structWithConstMember s);

#ifdef __cplusplus
}
#endif

#endif /* VOIDFUNSTRUCTWITHCONSTMEMBER_H */

