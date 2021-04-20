# Hello world example

## Table of content
* [Introduction][intro]
* [Context][context]
* [Makefile][Makefile]
* [First implementation][firstVersion]
* [First unit test][firstUT]
* [Second unit test][secondUT]
* [Conclusion][conclusion]

## <a name="user-content-intro"></a>Introduction
This page contains an example on how to create a unit test using EasyMock.
This example does, on purpose, NOT use a unit test framework (such as Catch2
or Google test) because EasyMock is independent from those frameworks.
Instead, the tests are implemented in the main function using some rudimentary asserts.

The purpose of this example is to show how easy it is to create unit tests without having to compile
integrate all the dependencies. That way, the unit test remains fast to build and run.

## <a name="user-content-context"></a>Context
The goal of this example is to implement a function which computes the
average of some random numbers. The random numbers are coming from a
library from which the source code is not available. The library defines the following interface in `u8rand.h`

```c
#ifndef U8_RAND_H
#define U8_RAND_H

unsigned char u8rand();

#endif
```

## <a name="user-content-makefile"></a>Makefile
In order to compile this example, the following Makefile can be used:
```makefile
testAverage: average.o main.o easyMock_u8rand.o
	# Note: the `-Wl,-rpath` option is to bake the path to the library into the binary
	# so that the .so can be found at runtime by the ELF loader.
	gcc main.o easyMock_u8rand.o average.o -Wl,-rpath,${EASYMOCK_BUILDIR}/src/easyMockFramework/src -L${EASYMOCK_BUILDIR}/src/easyMockFramework/src -lEasyMockFramework -o testAverage

average.o: average.c
	gcc -Wall -Werror -c average.c -o average.o

main.o: easyMock_u8rand.h main.c
	gcc -Wall -Werror -I ${EASYMOCK_SOURCE}/src/easyMockFramework/include/ -c main.c -o main.o

easyMock_u8rand.c easyMock_u8rand.h: u8rand.h
	${EASYMOCK_BUILDIR}/EasyMockGenerate -i u8rand.h -o .

easyMock_u8rand.o: easyMock_u8rand.c easyMock_u8rand.h
	gcc -Wall -Werror -I ${EASYMOCK_SOURCE}/src/easyMockFramework/include/ -c easyMock_u8rand.c -o easyMock_u8rand.o

clean:
	rm -rf *.o easyMock_u8rand.* testAverage
```
Make sure to export `EASYMOCK_BUILDIR` and `EASYMOCK_SOURCE` to the place where `EasyMockGenerate` has been build
and to the root directory of EasyMock's source code respectively.

It is to be noted that the Makefile handles the generation of the mock. The rule depends on the header to be mocked
(in this case `u8rand.h`). It is important to do so because it is needed to regenerate the mock everytime the header
file changes.

Finally, this Makefile contains good examples of the commands to be issued to generate mock and compile it.

The rest of this page will explain the content of each file as the explanation goes through.

## <a name="user-content-fut"></a>First unit test

When writing unit tests, it is good practice to use test driven development aka TDD.

Let's create our first test and verify that it fails. It is created inside `main.c`

```c
#include "average.h"

//Include the generated mock
#include "easyMock_u8rand.h"

#include <stdio.h>

//Crude assert implementation
#define my_assert(condition) \
({ \
  int assert_rv = 0; \
  if(!(condition)) \
  { \
    printf("assert failed: %s\n", #condition); \
    assert_rv = 1; \
  } \
  assert_rv; \
})

int test1()
{
  int test_rv = 0;
  easyMock_init();

  u8rand_ExpectAndReturn(3); //First  call of u8rand returns 3
  u8rand_ExpectAndReturn(4); //Second call of u8rand returns 4
  u8rand_ExpectAndReturn(5); //Third  call of u8rand returns 5
  u8rand_ExpectAndReturn(6); //Fourth call of u8rand returns 6

  float av = average(4);

  //Average of [3, 4, 5, 6] == 4.5
  test_rv |= my_assert(av == 4.5);
  
  if(!easyMock_check())
  {
    printf("%s\n", easyMock_getErrorStr());
  }
  
  if(test_rv == 0)
  {
    printf("test 1 passed\n");
  }

  return test_rv;
}

int main(int argc, char *argv[])
{
  int rv = 0;
  rv |= test1();

  return rv;
}
```

It is also needed to provide a first implementation of the `average` function. Since the test must fail, an empty
implementation can be provided like so.

In `average.h`
```c
#ifndef AVERAGE
#define AVERAGE

float average(int nbNumber);

#endif
```

In `average.c`
```c
#include "average.h"

float average(int nbNumber)
{
  return 0;
}
```

The project looks now like so:
```shell
$ tree          
.
├── average.c
├── average.h
├── main.c
├── Makefile
└── u8rand.h
```

Let's now compile it using make
```shell
$ make
gcc -Wall -Werror -c average.c -o average.o
/tmp/EasyMock/build/EasyMockGenerate -i u8rand.h -o .
Generating u8rand.h in .
Generating u8rand.h with using original headers in .
gcc -Wall -Werror -I /tmp/EasyMock/src/easyMockFramework/include/ -c main.c -o main.o
gcc -Wall -Werror -I /tmp/EasyMock/src/easyMockFramework/include/ -c easyMock_u8rand.c -o easyMock_u8rand.o
# Note: the `-Wl,-rpath` option is to bake the path to the library into the binary
# so that the .so can be found at runtime by the ELF loader.
gcc main.o easyMock_u8rand.o average.o -Wl,-rpath,/tmp/EasyMock/build/src/easyMockFramework/src -L/tmp/EasyMock/build/src/easyMockFramework/src -lEasyMockFramework -o testAverage
```

It is to be noted that the mocked header has been generated as part of the build process.

When running the executable, the following output is given:
```sh
$ ./testAverage 
assert failed: av == 4.5
Error: For function 'unsigned char u8rand()' bad number of call. Expected 4, got 0
```

The output tells 2 information:
1. The `average` function failed to return the expected value. I.e the implementation is not working properly.
2. The expected number of calls to the mocked function was not the expected one. In this particular case,
   not enough call has been made to `u8rand`.

## <a name="user-content-fv"></a>First implementation

Now that the test is ready, let's implement the first version of the average function.

It can be implemented like so:
```c
#include "average.h"
#include "u8rand.h"

float average(int nbNumber)
{
  unsigned char counter = 0;
  for(unsigned int i = 0; i < nbNumber; i++)
  {
    counter += u8rand();
  }
  float av = (float)counter/nbNumber;

  return av;
}
```

After recompiling everything,
```shell
$ make         
gcc -Wall -Werror -c average.c -o average.o
# Note: the `-Wl,-rpath` option is to bake the path to the library into the binary
# so that the .so can be found at runtime by the ELF loader.
gcc main.o easyMock_u8rand.o average.o -Wl,-rpath,/tmp/EasyMock/build/src/easyMockFramework/src -L/tmp/EasyMock/build/src/easyMockFramework/src -lEasyMockFramework -o testAverage

```
the output of the unit test is the following:
```shell
$ ./testAverage 
test 1 passed
```

Sweet! The first test is passing!

## <a name="user-content-sut"></a>Second unit test
It is now time to write a second unit test. What would happen if the random generated numbers were higher?
Without EasyMock, the unit test would have to run the actual implementation of `u8rand` and hope that 2
consecutive high numbers are generated. This is not very likely and nor reproducible.
However, when using EasyMock, it is easy to configure the mock to return 2 high numbers.

```c
//... int test1()

int test2()
{
  int test_rv = 0;
  easyMock_init();

  u8rand_ExpectAndReturn(192); //First  call of u8rand returns 192
  u8rand_ExpectAndReturn(128); //Second call of u8rand returns 128

  float av = average(2);

  //Average of [192, 128] == 160
  test_rv |= my_assert(av == 160);
  if(!easyMock_check())
  {
    printf("%s\n", easyMock_getErrorStr());
  }

  if(test_rv == 0)
  {
    printf("test 2 passed\n");
  }

  return test_rv;
}

int main(int argc, char *argv[])
{
  int rv = 0;
  rv |= test1();
  rv |= test2();

  return rv;
}
```

Let's now recompile everything and run the tests:
```sh
$ ./testAverage 
test 1 passed
assert failed: av == 160
```

It shows that the second test is not passing. The number of calls to `u8rand` is correct but the
average sum is not correctly computed. The reason is because the `average` function stores the counter into
an `unsigned char` and it overflows. The fix for this bug is to fix the `average` function like so:

```c
#include "average.h"
#include "u8rand.h"

float average(int nbNumber)
{
  unsigned int counter = 0;
  for(unsigned int i = 0; i < nbNumber; i++)
  {
      counter += u8rand();
  }
  float av = (float)counter/nbNumber;

  return av;
}
```

After recompiling everything, the second test passes.

```sh
$ ./testAverage
test 1 passed
test 2 passed
```

## <a name="user-content-conclusion"></a>Conclusion
This example shows how easy it is to reproduce corner cases with EasyMock.
When an interface is well known, it is easy to reproduce its behaviour by using EasyMock.
Thanks to EasyMock, it is possible to mock any kind of dependencies and make it behave the way it is needed
to make sure that correct operational code is written. In this particular example, the implementation of
the `u8rand` function wasn't known (and wasn't needed either) in order to write the unit tests.

[intro]: #user-content-intro
[Context]: #user-content-context
[Makefile]: #user-content-makefile
[firstVersion]: #user-content-fv
[firstUT]: #user-content-fut
[secondUT]: #user-content-sut
[conclusion]: #user-content-conclusion
