#ifndef EASYMOCK_VOIDFUNALIASEDFUN_H
#define EASYMOCK_VOIDFUNALIASEDFUN_H

void funToBeAliased();

#define funToBeAliased voidFunAliasedFun

void voidFunAliasedFun();

#endif //EASYMOCK_VOIDFUNALIASEDFUN_H
