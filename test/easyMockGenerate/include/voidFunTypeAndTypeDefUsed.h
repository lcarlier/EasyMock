#ifndef EASYMOCK_VOIDFUNTYPEANDTYPEDEFUSED_H
#define EASYMOCK_VOIDFUNTYPEANDTYPEDEFUSED_H

typedef struct notTypedefUsed *typedefUsed;

void voidFunTypeDefUsed(typedefUsed t);

struct notTypedefUsed
{
  int a;
};

void voidFunTypeAndTypeDefUsed(struct notTypedefUsed s);

#endif //EASYMOCK_VOIDFUNTYPEANDTYPEDEFUSED_H
