#ifndef VOIDFUNSTRUCTFORWARDDECLARED_H
#define VOIDFUNSTRUCTFORWARDDECLARED_H

#ifdef __cplusplus
extern "C" {
#endif

    struct forwardDeclaredParent;

    struct forwardDeclaredChild
    {
        struct forwardDeclaredParent* p;
    };

    struct forwardDeclaredParent
    {
        struct forwardDeclaredChild c;
    };

    void voidFunStructForwardDeclared(struct forwardDeclaredParent p);


#ifdef __cplusplus
}
#endif

#endif /* VOIDFUNSTRUCTFORWARDDECLARED_H */

