#ifndef UNIONTYPEDEFFUNUNIONTYPEDDEF
#define UNIONTYPEDEFFUNUNIONTYPEDDEF

#ifdef __cplusplus
extern "C"
{
#endif

  typedef union u {
    int a;
    int b;
  } t_u;

  t_u unionTypedDefFunUnionTypedDef(t_u param);

#ifdef __cplusplus
}
#endif

#endif /* UNIONTYPEDEFFUNUNIONTYPEDDEF */

