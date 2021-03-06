#include <StructCommonHelper.h>

bool operator==(const struct s1 &lhs, const struct s1 &rhs)
{
  return lhs.a == rhs.a && lhs.b == rhs.b;
}

bool operator==(const struct s2 &lhs, const struct s2 &rhs)
{
  return lhs.c == rhs.c && lhs.d == rhs.d && lhs.s == rhs.s;
}

bool operator==(const TypedDefStruct &lhs, const TypedDefStruct &rhs)
{
  return lhs.a == rhs.a;
}

bool operator==(const TypedDefAnonymousStruct &lhs, const TypedDefAnonymousStruct &rhs)
{
  return lhs.a == rhs.a;
}

bool operator==(const sWithUnion &lhs, const sWithUnion &rhs)
{
  return lhs.u.a == rhs.u.a || lhs.u.b == rhs.u.b;
}


bool operator==(const struct BoxPropsContainer& lhs, const struct BoxPropsContainer& rhs)
{
  return lhs.b.opaque == rhs.b.opaque ||
          lhs.b.fill_color == rhs.b.fill_color ||
          lhs.b.show_border == rhs.b.show_border ||
          lhs.b.border_color == rhs.b.border_color ||
          lhs.b.border_style == rhs.b.border_style ||
          lhs.b.width == rhs.b.width ||
          lhs.b.height == rhs.b.height;
}

std::ostream& operator<<(std::ostream& os, const struct s1& c)
{
  return os << "a: " << c.a << " b: " << c.b;
}

std::ostream& operator<<(std::ostream& os, const struct s2& c)
{
  return os << "c: " << c.c << " d: " << c.d << " s1.a: " << c.s.a << " s1.b: " << c.s.b;
}

std::ostream& operator<<(std::ostream& os, const struct recurs& c)
{
  return os << "c.val: " << c.val;
}

std::ostream& operator<<(std::ostream& os, const TypedDefStruct& c)
{
  return os << "c.a: " << c.a;
}

std::ostream& operator<<(std::ostream& os, const TypedDefAnonymousStruct& c)
{
  return os << "c.a: " << c.a;
}
std::ostream& operator<<(std::ostream& os, const sWithUnion& st)
{
  return os << "st.u.a: " << st.u.a << " st.u.b: " << st.u.b;
}
