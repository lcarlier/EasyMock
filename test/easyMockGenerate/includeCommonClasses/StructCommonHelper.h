#ifndef STRUCTCOMMONHELPER_H
#define STRUCTCOMMONHELPER_H

#include <ostream>
#include <structCommonDeclaration.h>
#include <structRecursivePtrType.h>
#include <structAnonymousTypedDefFunStructAnonymousTypedDef.h>
#include <structTypedDefFunStructTypedDef.h>
#include <structWithUnionFunStructWithUnion.h>
#include <voidFunStructBitfield.h>

bool operator==(const struct s1 &lhs, const struct s1 &rhs);
bool operator==(const struct s2 &lhs, const struct s2 &rhs);
bool operator==(const TypedDefStruct &lhs, const TypedDefStruct &rhs);
bool operator==(const TypedDefAnonymousStruct &lhs, const TypedDefAnonymousStruct &rhs);
bool operator==(const sWithUnion &lhs, const sWithUnion &rhs);
bool operator==(const struct BoxPropsContainer& lhs, const struct BoxPropsContainer& rhs);
std::ostream& operator<<(std::ostream& os, const struct s1& c);
std::ostream& operator<<(std::ostream& os, const struct s2& c);
std::ostream& operator<<(std::ostream& os, const struct recurs& c);
std::ostream& operator<<(std::ostream& os, const TypedDefStruct& c);
std::ostream& operator<<(std::ostream& os, const TypedDefAnonymousStruct& c);
std::ostream& operator<<(std::ostream& os, const sWithUnion& st);

#endif /* STRUCTCOMMONHELPER_H */

