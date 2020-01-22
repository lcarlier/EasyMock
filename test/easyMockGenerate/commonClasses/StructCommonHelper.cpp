#include <StructCommonHelper.h>

bool operator==(const struct s1 &lhs, const struct s1 &rhs)
{
  return lhs.a == rhs.a && lhs.b == rhs.b;
}

bool operator==(const struct s2 &lhs, const struct s2 &rhs)
{
  return lhs.c == rhs.c && lhs.d == rhs.d && lhs.s == rhs.s;
}

std::ostream& operator<<(std::ostream& os, const struct s1& c)
{
  return os << "a: " << c.a << " b: " << c.b;
}

std::ostream& operator<<(std::ostream& os, const struct s2& c)
{
  return os << "c: " << c.c << " d: " << c.d << " s1.a: " << c.s.a << " s1.b: " << c.s.b;
}
