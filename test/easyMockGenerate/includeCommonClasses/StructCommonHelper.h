#ifndef STRUCTCOMMONHELPER_H
#define STRUCTCOMMONHELPER_H

#include <ostream>
#include <structCommonDeclaration.h>

bool operator==(const struct s1 &lhs, const struct s1 &rhs);
bool operator==(const struct s2 &lhs, const struct s2 &rhs);
std::ostream& operator<<(std::ostream& os, const struct s1& c);
std::ostream& operator<<(std::ostream& os, const struct s2& c);

#endif /* STRUCTCOMMONHELPER_H */

