#ifndef VOIDFUNPTRTOPTRRECURSTRUCT_H
#define VOIDFUNPTRTOPTRRECURSTRUCT_H

#ifdef __cplusplus
extern "C" {
#endif

  struct ptrToPtrStructRecur
  {
    struct ptrToPtrStructRecur** r;
  };

  void voidFunPtrToPtrRecurStruct(struct ptrToPtrStructRecur** s);

  struct ptrToPtrStructRecur** ptrToPtrRecurStructFunVoid();

  struct structFieldptrToPtrStructRecur
  {
    struct ptrToPtrStructRecur** f;
  };

  void voidFunStructFieldptrToPtrStructRecur(struct structFieldptrToPtrStructRecur s);

  struct structAnonStructFieldptrToPtrStructRecur
  {
    int a;
    struct
    {
      struct ptrToPtrStructRecur** r;
    };
  };

  void voidFunStructAnonStructFieldptrToPtrStructRecur(struct structAnonStructFieldptrToPtrStructRecur s);


#ifdef __cplusplus
}
#endif

#endif /* VOIDFUNPTRTOPTRRECURSTRUCT_H */

