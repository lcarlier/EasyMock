#ifndef VOIDFUNTYPEDEF_H
#define VOIDFUNTYPEDEF_H

#ifdef __cplusplus
extern "C" {
#endif

  typedef int MyType1;
  typedef float MyType2;
  typedef MyType2 MyType3;
  typedef const int* CMyType1;
  typedef short MyType4;

  void voidFunTypeDef(MyType1 p1, MyType2 p2, MyType3 p3, CMyType1 p4, MyType4 const* p5);
  CMyType1 ptypedefFunVoid();


#ifdef __cplusplus
}
#endif

#endif /* VOIDFUNTYPEDEF_H */

