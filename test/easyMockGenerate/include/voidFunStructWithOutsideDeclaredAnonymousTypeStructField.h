#ifndef EASYMOCK_VOIDFUNSTRUCTWITHOUTSIDEDECLAREDANONYMOUSTYPESTRUCTFIELD_H
#define EASYMOCK_VOIDFUNSTRUCTWITHOUTSIDEDECLAREDANONYMOUSTYPESTRUCTFIELD_H

typedef unsigned long sval_t;

typedef struct
{
  sval_t val;
} val_t;

struct structWithOutsideAnonymousDeclaredStruct
{
  struct
  {
    /*
     * Pointer to val_t is the root cause of the bug that is fixed by
     * voidFunStructWithOutsideDeclaredAnonymousTypeStructField
     */
    val_t* o;
  };
};

void voidFunStructWithOutsideDeclaredAnonymousTypeStructField(struct structWithOutsideAnonymousDeclaredStruct s);

struct structWithOutsideAnonymousDeclaredStruct structWithOutsideAnonymousDeclaredStructFunVoid();

#endif //EASYMOCK_VOIDFUNSTRUCTWITHOUTSIDEDECLAREDANONYMOUSTYPESTRUCTFIELD_H
