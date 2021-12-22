#include <easyMock_mainInclude.h>

void foo()
{
  mainIncludeToBeTaken_ExpectAndReturn();
  //In this case it isn't ignored since --generate-included-functions is given to EasyMock
  mainIncludeToBeIgnored_ExpectAndReturn();
}
