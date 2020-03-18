#include "UnionCommonHelper.h"

bool operator==(const union u &lhs, const union u &rhs)
{
  return lhs.a == rhs.a || lhs.b == rhs.b;
}

std::ostream& operator<<(std::ostream& os,const union u& u)
{
  return os << "u.a: " << u.a << " u.b: " << u.b;
}

bool operator==(const union u1 &lhs, const union u1 &rhs)
{
  return lhs.a == rhs.a;
}

std::ostream& operator<<(std::ostream& os,const union u1& u)
{
  return os << "u.a: " << u.a;
}

bool operator==(const union u2 &lhs, const union u2 &rhs)
{
  return lhs.b == rhs.b;
}

std::ostream& operator<<(std::ostream& os,const union u2& u)
{
  return os << "u.b: " << u.b;
}

bool operator==(const TypedDefAnonymousUnion &lhs, const TypedDefAnonymousUnion &rhs)
{
  return lhs.a == rhs.a || lhs.b == rhs.b;
}

std::ostream& operator<<(std::ostream& os,const TypedDefAnonymousUnion& u)
{
  return os << "u.a: " << u.a << " u.b: " << u.b;
}
