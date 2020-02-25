#ifndef STRUCTSUBSTRUCTRECURSIVETYPE_H
#define STRUCTSUBSTRUCTRECURSIVETYPE_H

#ifdef __cplusplus
extern "C"
{
#endif

struct st1;

struct st2
{
  struct st1 *st2SubSt1;
  struct st2 *st2SubSt2;
};

struct st1
{
  struct st2 st1SubSt2;
};

void structSubStructRecursiveType(struct st1 st1Val);


#ifdef __cplusplus
}
#endif

#endif /* STRUCTSUBSTRUCTRECURSIVETYPE_H */

