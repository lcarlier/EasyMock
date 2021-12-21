#ifndef EASYMOCK_STRUCTEMPTYTYPEARRAY_H
#define EASYMOCK_STRUCTEMPTYTYPEARRAY_H

struct emptyType
{

};

typedef struct emptyType t_emptyType;

struct emptyTypeArray
{
  struct emptyType f1[3];
  t_emptyType f2[3];
  struct emptyType const f3[3];
  t_emptyType const f4[3];
};

void funStructEmptyTypeArray(struct emptyTypeArray p);

#endif //EASYMOCK_STRUCTEMPTYTYPEARRAY_H
