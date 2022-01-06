#include <gtest/gtest.h>

#include <cstring.h>

#define LOREM_IPSUM "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Etiam eget est nec urna laoreet luctus. Cras pharetra tellus metus, vel commodo lorem aliquet sit amet. Vestibulum vitae elit ac justo lacinia tempor. Donec auctor mi in lacus porttitor tincidunt. Ut pulvinar quam id mollis pharetra. Donec accumsan augue tortor, ac faucibus ante efficitur et. In placerat dui nibh. Aenean leo lacus, dignissim id mi sit amet, pretium interdum dui. Sed nulla nibh, porttitor non purus quis, interdum varius arcu. Phasellus et placerat est, non venenatis nulla. Suspendisse potenti. Vestibulum eget metus dignissim odio sagittis interdum imperdiet vitae odio. Mauris venenatis convallis dictum. In sapien augue, volutpat quis felis eget, venenatis egestas magna. "

TEST(test_ctype, creation)
{
  CSTRING_AUTOCLEAN(s) = cstring_new();

  ASSERT_EQ(cstring_length(&s), 0);
}

TEST(test_ctype, creation_init)
{
  CSTRING_AUTOCLEAN(s) = cstring_new_init("foo");

  ASSERT_EQ(cstring_length(&s), 3);
  ASSERT_STREQ(cstring_c_str(&s), "foo");
  ASSERT_EQ(cstring_compare_const_char(&s, "foo"), 0);
}

TEST(test_ctype, creation_init_big_string)
{
  const char* bigString = LOREM_IPSUM;
  size_t lenOfBigString = strlen(bigString);

  CSTRING_AUTOCLEAN(s) = cstring_new_init(bigString);
  ASSERT_EQ(cstring_length(&s), lenOfBigString);
  ASSERT_STREQ(cstring_c_str(&s), bigString);
  ASSERT_EQ(cstring_compare_const_char(&s, bigString), 0);
}

TEST(test_ctype, append)
{
  CSTRING_AUTOCLEAN(s) = cstring_new();

  cstring_append(&s, "toAppend");

  ASSERT_TRUE(cstring_length(&s) == 8);
  ASSERT_STREQ(cstring_c_str(&s), "toAppend");
  ASSERT_EQ(cstring_compare_const_char(&s, "toAppend"), 0);
}

TEST(test_ctype, append_big_string)
{
  const char* bigString = LOREM_IPSUM;
  size_t lenOfBigString = strlen(bigString);

  CSTRING_AUTOCLEAN(s) = cstring_new();

  cstring_append(&s, bigString);

  ASSERT_EQ(cstring_length(&s), lenOfBigString);
  ASSERT_STREQ(cstring_c_str(&s), bigString);
  ASSERT_EQ(cstring_compare_const_char(&s, bigString), 0);
}

TEST(test_ctype, append_non_empty)
{
  CSTRING_AUTOCLEAN(s) = cstring_new_init("foo");

  cstring_append(&s, "bar");

  ASSERT_EQ(cstring_length(&s), 6);
  ASSERT_STREQ(cstring_c_str(&s), "foobar");
  ASSERT_EQ(cstring_compare_const_char(&s, "foobar"), 0);
}

TEST(test_ctype, append_non_empty_big_string)
{
  const char* bigString = LOREM_IPSUM;
  size_t lenOfBigString = strlen(bigString);

  CSTRING_AUTOCLEAN(s) = cstring_new_init("bar");

  cstring_append(&s, LOREM_IPSUM);

  ASSERT_EQ(cstring_length(&s), lenOfBigString + 3);
  ASSERT_STREQ(cstring_c_str(&s), "bar" LOREM_IPSUM );
  ASSERT_EQ(cstring_compare_const_char(&s, "bar" LOREM_IPSUM ), 0);
}

TEST(test_ctype, append_big_string_to_init_big_string)
{
  const char* bigString = LOREM_IPSUM;
  size_t lenOfBigString = strlen(bigString);

  CSTRING_AUTOCLEAN(s) = cstring_new_init(bigString);

  cstring_append(&s, LOREM_IPSUM);

  ASSERT_EQ(cstring_length(&s), lenOfBigString + lenOfBigString);
  ASSERT_STREQ(cstring_c_str(&s), LOREM_IPSUM LOREM_IPSUM );
  ASSERT_EQ(cstring_compare_const_char(&s, LOREM_IPSUM LOREM_IPSUM ), 0);
}
