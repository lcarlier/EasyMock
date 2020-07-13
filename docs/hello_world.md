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
This example will, on purpose, not use a unit test framework (such as Catch2
or Google test) because EasyMock is independent of those framework.
Therefore, the main function is actually calling the unit tests manually.

## <a name="user-content-context"></a>Context
The goal of this example is to implement a function which computes the
average of some random numbers. The random numbers are coming from a
library which we do not have the source code and that defines the following
interface in u8Rand.h

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

The first step is to create the mock of the dependecy. In order to mock our
dependency, EasyMockGenerate can be used. The following command generates a
mock implementation for the `u8Rand()` function.
```sh
EasyMockGenerate -i u8Rand.h -o .
```

The file created are:
* easyMock_u8rand.h
* easyMock_u8rand.cpp

The mock can then be compiled with the following command:
```sh
g++ -Wall -Werror -I $EASYMOCK_SOURCE/src/easyMockFramework/include/ -c easyMock_u8rand.cpp -o easyMock_u8rand.o
```

Then the code for the first test can be written.
```c
#include "easyMock_u8rand.h"
#undef NDEBUG //make sure assert are not disabled
#include <assert.h>

void test1()
{
    u8Rand_ExpectAndReturn(3); //First  call of u8Rand returns 3
    u8Rand_ExpectAndReturn(4); //Second call of u8Rand returns 4
    u8Rand_ExpectAndReturn(5); //Third  call of u8Rand returns 5
    u8Rand_ExpectAndReturn(6); //Fourth call of u8Rand returns 6

    float av = average(4);

    assert(av == 4.5);
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
g++ main.o easyMock_u8rand.o -Wl,-rpath,$EASYMOCK_BUILDIR/src/easyMockFramework/src" -L$EASYMOCK_BUILDIR/src/easyMockFramework/src -lEasyMockFramework -o testAverage
```
Note: the `-Wl,-rpath` option is to bake the path to the library into the binary
so that the .so can be find at runtime by the ELF loader.

When running the executable, the following output is given:
```sh
./testAverage
test 1 passed
```

Sweet! Our first test is passing!

It is to be noticed that even though the mocks are implemented in C++, the test
code (i.e. main) can be implemented in C and everything works eventually
with C linkage.

## <a name="user-content-sut"></a>Second unit test
It is now time to write our second unit test. What would happen if the random
number where very high? Instead of running the code several times and hoping
that high numbers come randomly twice, we can easily test that with configuring
EasyMock to return 2 big numbers.

```c
void test2()
{
    u8Rand_ExpectAndReturn(192); //First  call of u8Rand returns 192
    u8Rand_ExpectAndReturn(128); //Second call of u8Rand returns 128

    float av = average(2);

    assert(av == 160);
}
```

Now if we call this test in our main here is the output we obtain
```sh
./testAverage
test 1 passed
testAverage: main.c:39: test2: Assertion `av == 160' failed.
zsh: abort (core dumped)  ./testAverage
```

It sounds that this test is not passing. The reason is because our average
function stores the counter into an `unsigned char` and it overflows. The fix
is by writing the `average()` function like so:

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

After recompiling everything, the second test works fine

```sh
./testAverage
test 1 passed
test 2 passed
```

## <a name="user-content-conclusion"></a>Conclusion
This example shows how easy it is to reproduce corner cases with EasyMock.
Thanks to EasyMock, it is possible to mock any kind of dependency and make
them behave the way you like to make sure that the functionality you are
writing is well implemented.


[intro]: #user-content-intro
[Context]: #user-content-context
[firstVersion]: #user-content-fv
[firstUT]: #user-content-fut
[secondUT]: #user-content-sut
[conclusion]: #user-content-conclusion