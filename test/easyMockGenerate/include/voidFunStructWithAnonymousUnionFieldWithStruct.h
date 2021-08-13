#ifndef EASYMOCK_VOIDFUNSTRUCTWITHANONYMOUSUNIONFIELDWITHSTRUCT_H
#define EASYMOCK_VOIDFUNSTRUCTWITHANONYMOUSUNIONFIELDWITHSTRUCT_H

struct subAnonUnion1
{
  int a;
  int b;
};

struct subAnonUnion2
{
  int a;
};

struct structWithUnionFieldWithStruct
{
  struct {
    int a;
  } f1;
  struct {
    union
    {
      struct subAnonUnion1* s1;
      struct subAnonUnion2* s2;
    };
  } f2;
};

void voidFunStructWithAnonymousUnionFieldWithStruct(struct structWithUnionFieldWithStruct t);

#endif //EASYMOCK_VOIDFUNSTRUCTWITHANONYMOUSUNIONFIELDWITHSTRUCT_H
