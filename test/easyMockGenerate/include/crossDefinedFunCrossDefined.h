#ifndef CROSSDEFINEDFUNCROSSDEFINED_H
#define CROSSDEFINEDFUNCROSSDEFINED_H

#ifdef __cplusplus
extern "C" {
#endif

#define DEF1 int
#define DEF2 float

#define FUN_TYPE_MACRO(a, b) \
do {                         \
printf("foo %d", a);         \
printf("bar %d", b);         \
}

#define TM_PRINTF(f_, ...) printf((f_), __VA_ARGS__)

#define BIGER_THAN_ZERO(x) (x > 0)

  DEF2 crossDefinedFunCrossDefined(DEF1 p);

#ifdef __cplusplus
}
#endif

#endif /* CROSSDEFINEDFUNCROSSDEFINED_H */

