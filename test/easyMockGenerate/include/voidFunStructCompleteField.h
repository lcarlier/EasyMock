#ifndef EASYMOCK_VOIDFUNSTRUCTCOMPLETEFIELD_H
#define EASYMOCK_VOIDFUNSTRUCTCOMPLETEFIELD_H

#ifdef __cplusplus
extern "C"
{
#endif

struct completeStruct
{
  struct forwardDecl3* f;
};

void voidFunStructCompleteField(struct completeStruct const* fp);

struct forwardDecl2
{
  struct completeStruct const c;
};

struct forwardDecl3
{
  void (*fun)(struct forwardDecl2*);
};

#ifdef __cplusplus
}
#endif

#endif //EASYMOCK_VOIDFUNSTRUCTCOMPLETEFIELD_H
