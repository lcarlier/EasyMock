#ifndef EASYMOCK_VOIDFUNDECLANDDEF_H
#define EASYMOCK_VOIDFUNDECLANDDEF_H

//Parameters are unnamed on purpose.
static __attribute__((unused)) void voidFunDeclAndDef(char , char );

static __attribute__((unused)) void voidFunDeclAndDef(char a, char b)
{
  (void)a;
  (void)b;
}

#endif //EASYMOCK_VOIDFUNDECLANDDEF_H
