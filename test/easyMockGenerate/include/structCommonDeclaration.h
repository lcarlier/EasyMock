#ifndef STRUCTCOMMONDECLARATION_H
#define STRUCTCOMMONDECLARATION_H

#ifdef __cplusplus
extern "C"
{
#endif

  struct s1
  {
    int a;
    float b;
  };

  struct s2
  {
    int c;
    float d;
    struct s1 s;
  };

#ifdef __cplusplus
}
#endif

#endif /* STRUCTCOMMONDECLARATION_H */

