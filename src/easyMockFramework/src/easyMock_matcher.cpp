#include <easyMock.h>
#include <stdio.h>

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


