#ifndef UNIONCOMMONHELPER_H
#define UNIONCOMMONHELPER_H

#include <ostream>
#include <unionTypedDefFunUnionTypedDef.h>
#include <unionFunUnion.h>
#include <unionAnonymousTypedDefFunUnionAnonymousTypedDef.h>

bool operator==(const union u &lhs, const union u &rhs);
std::ostream& operator<<(std::ostream& os,const union u& c);
bool operator==(const union u1 &lhs, const union u1 &rhs);
std::ostream& operator<<(std::ostream& os,const union u1& c);
bool operator==(const union u2 &lhs, const union u2 &rhs);
std::ostream& operator<<(std::ostream& os,const union u2& c);
bool operator==(const TypedDefAnonymousUnion &lhs, const TypedDefAnonymousUnion &rhs);
std::ostream& operator<<(std::ostream& os,const TypedDefAnonymousUnion& c);

#endif /* UNIONCOMMONHELPER_H */

