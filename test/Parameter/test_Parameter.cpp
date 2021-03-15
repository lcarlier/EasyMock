#include <gtest/gtest.h>

#include <EasyMock_CType.h>
#include <Pointer.h>
#include <ConstQualifiedType.h>
#include <TypedefType.h>
#include <Parameter.h>

#include <string>

TEST(Parameter, pointerToConstVoid)
{
  Pointer* pointer = new Pointer(new ConstQualifiedType(new CType(CTYPE_VOID)) );
  Parameter parameter { pointer, "p" };
  ASSERT_STREQ(parameter.getDeclareString().c_str(), "void const*");
}
