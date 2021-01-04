#include <gtest/gtest.h>

#include <EasyMock_CType.h>
#include <Pointer.h>
#include <IncompleteType.h>

#include <string>

TEST(PointerType, getFullDeclarationNaked)
{
  CType cIntType(CTYPE_INT, true);
  Pointer p(cIntType.clone(), "CMyType1", false);

  EXPECT_STREQ(p.getFullDeclarationName(true).c_str(), "const int*");
  EXPECT_STREQ(p.getFullDeclarationName(false).c_str(), "CMyType1");
}