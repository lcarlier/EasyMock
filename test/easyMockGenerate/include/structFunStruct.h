#ifndef STRUCTFUNSTRUCT_H
#define STRUCTFUNSTRUCT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "structCommonDeclaration.h"

  struct onelineStruct
  {
    unsigned int a , b , c;
    unsigned int *pa , *pb , *pc;
  };

  struct s1 structFunStruct(struct s2 s, struct onelineStruct s2);


#ifdef __cplusplus
}
#endif

#endif /* STRUCTFUNSTRUCT_H */

