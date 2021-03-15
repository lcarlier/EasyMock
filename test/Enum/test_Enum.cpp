#include <gtest/gtest.h>

#include <Enum.h>

#include <string>

TEST(Parameter, isAnonymous)
{
  Enum e("");
  ASSERT_TRUE(e.isAnonymous());
}
