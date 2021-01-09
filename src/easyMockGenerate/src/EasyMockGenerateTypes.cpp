#include "EasyMockGenerateTypes.h"

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

const char *easyMock_arrayCTypeStr[] =
{
  "char",
  "unsigned char",
  "signed char",
  "short",
  "unsigned short",
  "int",
  "unsigned int",
  "long",
  "unsigned long",
  "long long",
  "unsigned long long",
  "float",
  "double",
  "long double",
  "__int128",
  "unsigned __int128",
  "void",
  "invalid"
};
static_assert(ARRAY_SIZE(easyMock_arrayCTypeStr) == CTYPE_INVALID+1);

const char *easyMock_printfFormat[] =
{
  "c",
  "c",
  "c",
  "hi",
  "hu",
  "d",
  "u",
  "li",
  "lu",
  "lli",
  "llu",
  "f",
  "lf",
  "Lf",
  "lf%lf",
  "Lf%Lf",
  "voidInvalidPrintfFormat",
  "invalidPrintfFormat"
};
static_assert(ARRAY_SIZE(easyMock_printfFormat) == CTYPE_INVALID+1);

