# Hello world example

## Table of content
* [Introduction][intro]
* [Context][context]
* [First version][firstVersion]
* [First unit test][firstUT]
* [Second unit test][secondUT]
* [Conclusion][conclusion]

## <a name="user-content-intro"></a>Introduction
This page contains an example on how to create a unit test using EasyMock.
This example does, on purpose, NOT use a unit test framework (such as Catch2
or Google test) because EasyMock is independent from those frameworks.
Instead, the tests are implemented in the main function using some rudimentary asserts.

## <a name="user-content-context"></a>Context
The goal of this example is to implement a function which computes the
average of some random numbers. The random numbers are coming from a
library from which the source code is not available (but obviously the .so is!).
The library defines the following interface in u8Rand.h

```c
#ifndef U8_RAND_H
#define U8_RAND_H

unsigned char u8Rand();

#endif
```

## <a name="user-content-fv"></a>First version

The first version of the average function can be implemented like this

```c
#include "u8Rand.h"

float average(int nbNumber)
{
  unsigned char counter = 0;
  for(unsigned int i = 0; i < nbNumber; i++)
  {
    counter += u8Rand();
  }
  float av = (float)counter/nbNumber;

  return av;
}
```

## <a name="user-content-fut"></a>First unit test

The first step is to create the mock of the dependency. For that purpose,
EasyMockGenerate can be used. The following command generates a
mock for the `u8Rand()` function.
```sh
EasyMockGenerate -i u8Rand.h -o .
```

The files created are:
* easyMock_u8rand.h
* easyMock_u8rand.c

The mock can be compiled with the following command:
```sh
gcc -Wall -Werror -I $EASYMOCK_SOURCE/src/easyMockFramework/include/ -c easyMock_u8rand.c -o easyMock_u8rand.o
```

Afterwards, the code for the first test can be written like so:
```c
#include "easyMock_u8rand.h"
#undef NDEBUG //make sure asserts are not disabled
#include <assert.h>

void test1()
{
  easyMock_init();

  u8Rand_ExpectAndReturn(3); //First  call of u8Rand returns 3
  u8Rand_ExpectAndReturn(4); //Second call of u8Rand returns 4
  u8Rand_ExpectAndReturn(5); //Third  call of u8Rand returns 5
  u8Rand_ExpectAndReturn(6); //Fourth call of u8Rand returns 6

  float av = average(4);

  assert(av == 4.5);
  printf("test 1 passed\n");
}

int main(int argc, char *argv[])
{
  test1();

  return 0;
}
```

The `main.o` object can be compiled with the following command:
```sh
gcc  -Wall -Werror -I $EASYMOCK_SOURCE/src/easyMockFramework/include/ -c main.c -o main.o
```

And eventually the final binary can be obtained with:
```sh
gcc main.o easyMock_u8rand.o -Wl,-rpath,$EASYMOCK_BUILDIR/src/easyMockFramework/src" -L$EASYMOCK_BUILDIR/src/easyMockFramework/src -lEasyMockFramework -o testAverage
```
Note: the `-Wl,-rpath` option is to bake the path to the library into the binary
so that the .so can be found at runtime by the ELF loader.

When running the executable, the following output is given:
```sh
./testAverage
test 1 passed
```

Sweet! The first test is passing!

## <a name="user-content-sut"></a>Second unit test
It is now time to write the second unit test. What would happen if the random
numbers were higher? Instead of running the code several times and hoping
that high numbers come randomly twice, it is easy to configure
EasyMock to return 2 high numbers from the mock.

```c
void test2()
{
  easyMock_init();

  u8Rand_ExpectAndReturn(192); //First  call of u8Rand returns 192
  u8Rand_ExpectAndReturn(128); //Second call of u8Rand returns 128

  float av = average(2);

  assert(av == 160);
  printf("test 2 passed\n");
}
```

When this test is called in the main function, the following output is given:
```sh
./testAverage
test 1 passed
testAverage: main.c:39: test2: Assertion `av == 160' failed.
zsh: abort (core dumped)  ./testAverage
```

It shows that the test is not passing. The reason is because the average
function stores the counter into an `unsigned char` and it overflows. The fix
for this bug is to re-write the `average()` function like so:

```c
float average(int nbNumber)
{
  unsigned int counter = 0;
  for(unsigned int i = 0; i < nbNumber; i++)
  {
      counter += u8Rand();
  }
  float av = (float)counter/nbNumber;

  return av;
}
```

After recompiling everything, the second test works fine.

```sh
./testAverage
test 1 passed
test 2 passed
```

## <a name="user-content-conclusion"></a>Conclusion
This example shows how easy it is to reproduce corner cases with EasyMock.
Thanks to EasyMock, it is possible to mock any kind of dependency and make
it behave the way it is needed to make sure that correct code is written.


[intro]: #user-content-intro
[Context]: #user-content-context
[firstVersion]: #user-content-fv
[firstUT]: #user-content-fut
[secondUT]: #user-content-sut
[conclusion]: #user-content-conclusion
