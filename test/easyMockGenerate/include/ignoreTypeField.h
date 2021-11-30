#ifndef EASYMOCK_IGNORETYPEFIELD_H
#define EASYMOCK_IGNORETYPEFIELD_H

struct type_to_ignore
{
  int a;
};

struct container_type_to_ignore
{
  struct type_to_ignore a;
  int b;
};

void funTypeToIgnore(struct container_type_to_ignore s);

#endif //EASYMOCK_IGNORETYPEFIELD_H
