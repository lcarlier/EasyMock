#include <easyMock.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

#define IMPLEMENT_MATCHER(typeName, cType, printFormat) \
  extern "C" DECLARE_MATCHER(typeName) \
  { \
    cType currentCall_val = *((cType *)currentCall_ptr); \
    cType expectedCall_val = *((cType *)expectedCall_ptr); \
    if(currentCall_val == expectedCall_val) { \
      return 0; \
    } \
     snprintf(errorMessage, EASYMOCK_MAX_CMP_ERR, \
     "Parameter '%s' has value '" printFormat "', was expecting '" printFormat "'", \
           paramName, currentCall_val, expectedCall_val); \
    return -1; \
  } \
  \
  extern "C" DECLARE_DEREF_PTR_MATCHER(typeName) \
  { \
    cType **currentCall_val = (cType **)currentCall_ptr; \
    cType **expectedCall_val = (cType **)expectedCall_ptr; \
    return cmp_ ## typeName ((const void*)*currentCall_val, (const void*)*expectedCall_val, paramName, errorMessage); \
  }


IMPLEMENT_MATCHER(char, char, "%c");
IMPLEMENT_MATCHER(u_char, unsigned char, "%c");
IMPLEMENT_MATCHER(short, short, "%hi");
IMPLEMENT_MATCHER(u_short, unsigned short, "%hu");
IMPLEMENT_MATCHER(int, int, "%d");
IMPLEMENT_MATCHER(u_int, unsigned int, "%u");
IMPLEMENT_MATCHER(long, long, "%li");
IMPLEMENT_MATCHER(u_long, unsigned long, "%lu");
IMPLEMENT_MATCHER(long_long, long long, "%lli");
IMPLEMENT_MATCHER(u_long_long, unsigned long long, "%llu");
IMPLEMENT_MATCHER(float, float, "%f");
IMPLEMENT_MATCHER(double, double, "%lf");
IMPLEMENT_MATCHER(long_double, long double, "%Lf");
IMPLEMENT_MATCHER(pointer, void *, "%p");

extern "C" int cmp_str(const void *currentCall_ptr, const void *expectedCall_ptr, const char *paramName, char *errorMessage )
{
  char* currentCall_val = *((char **)currentCall_ptr);
  char* expectedCall_val = *((char **)expectedCall_ptr);
  if(strcmp(currentCall_val, expectedCall_val) == 0)
  {
    return 0;
  }
  snprintf(errorMessage, EASYMOCK_MAX_CMP_ERR,
  "Parameter '%s' has value '%s', was expecting '%s'",
        paramName, currentCall_val, expectedCall_val);
  return -1;
}

extern "C" int cmp_int128(const void *currentCall_ptr, const void *expectedCall_ptr, const char *paramName, char *errorMessage )
{
  __int128_t currentCall_val = *((__int128_t *)currentCall_ptr);
  __int128_t expectedCall_val = *((__int128_t *)expectedCall_ptr);
  if(currentCall_val == expectedCall_val)
  {
    return 0;
  }
  uint64_t lowDigitCurrent = currentCall_val & 0xffffffffffffffff;
  uint64_t lowDigitExpected = expectedCall_val & 0xffffffffffffffff;
  uint64_t highDigitCurrent = currentCall_val >> 64;
  uint64_t highDigitExpected = expectedCall_val >> 64;
  snprintf(errorMessage, EASYMOCK_MAX_CMP_ERR,
  "Parameter '%s' has value '%#" PRIx64 "%" PRIx64 "', was expecting '%#" PRIx64 "%" PRIx64 "'",
        paramName, highDigitCurrent, lowDigitCurrent, highDigitExpected, lowDigitExpected);
  return -1;
}
extern "C" int cmp_uint128(const void *currentCall_ptr, const void *expectedCall_ptr, const char *paramName, char *errorMessage )
{
  __uint128_t currentCall_val = *((__uint128_t *)currentCall_ptr);
  __uint128_t expectedCall_val = *((__uint128_t *)expectedCall_ptr);
  if(currentCall_val == expectedCall_val)
  {
    return 0;
  }
  uint64_t lowDigitCurrent = currentCall_val & 0xffffffffffffffff;
  uint64_t lowDigitExpected = expectedCall_val & 0xffffffffffffffff;
  uint64_t highDigitCurrent = currentCall_val >> 64;
  uint64_t highDigitExpected = expectedCall_val >> 64;
  snprintf(errorMessage, EASYMOCK_MAX_CMP_ERR,
  "Parameter '%s' has value '%#" PRIx64 "%" PRIx64 "', was expecting '%#" PRIx64 "%" PRIx64 "'",
        paramName, highDigitCurrent, lowDigitCurrent, highDigitExpected, lowDigitExpected);
  return -1;
}
