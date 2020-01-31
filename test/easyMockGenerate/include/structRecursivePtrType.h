#ifndef STRUCTRECURSIVEPTRTYPE_H
#define STRUCTRECURSIVEPTRTYPE_H

#ifdef __cplusplus
extern "C"
{
#endif

  struct recurs
  {
    struct recurs *val;
  };

  void structRecursivePtrType(struct recurs rec);


#ifdef __cplusplus
}
#endif

#endif /* STRUCTRECURSIVEPTRTYPE_H */

