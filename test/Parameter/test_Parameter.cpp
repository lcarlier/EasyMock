#include <gtest/gtest.h>

#include <EasyMock_CType.h>
#include <Pointer.h>
#include <ConstQualifiedType.h>
#include <TypedefType.h>
#include <Parameter.h>

#include <string>

TEST(Parameter, pointerToConstVoid)
{
  auto pointer = std::make_shared<Pointer>(std::make_shared<ConstQualifiedType>(std::make_shared<CType>(CTYPE_VOID)) );
  Parameter parameter { std::move(pointer), "p" };
  ASSERT_STREQ(parameter.getDeclareString().c_str(), "void const*");
}
