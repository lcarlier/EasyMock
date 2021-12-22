# Welcome to EasyMock
## <a name="user-content-wie"></a> What is EasyMock ?
EasyMock is a tool which generates mocks of C functions by parsing a header file.
The mocks can be configured to return a specific value on a specific call. When
the mocked function is called, the input argument can be compared to a specific
value to verify that the code calling them gives the correct parameters to the
mock.

Mocks are very useful when writing unit tests. Thanks to the mocks, the build
of the unit tests remains very small because it cuts the dependencies as soon as
possible. Also, mocks can be used to validate that a specific functions calls
the dependencies with the correct parameters. Then, mocks can be used to check
that the function you are testing processes correctly the data returned by
the dependencies.

EasyMock is very flexible to reproduce production scenarios because of its
flexibility of configuring the mocks.

## Table of content
* [What is EasyMock ?][whatIsEasymock]
* [How to compile EasyMock ?][compileEasymock]
    * [Release vs Debug build][relVsDeb]
    * [Dependencies][dependencies]
        * [Linux][linux]
        * [MacOS][macos]
    * [Compilation steps][compilationSteps]
* [libEasyMockFramework's API][libEasyAPI]
* [Create a mock][createAMock]
* [Generated functions][genFun]
* [Using the mocks][usingMock]
* [Unit tested][ut]
* [I want to participate in the development of EasyMock][participate]
* [Restriction][restriction]
* [Bug report][bugReport]
* [License of the tool][loft]
* [License of the generated code][logc]
* [The final note][finalNote]
* [Thanks][thanks]

## <a name="user-content-htce"></a> How to compile EasyMock ?

EasyMock can be compiled on Linux or macOS x86_64/arm.

### <a name="user-content-dependencies"></a> Dependencies

EasyMock uses the following mandatory libraries:
* libclang/llvm
* libctemplate
* libncurse
* liboost (system, filesystem)

Additionally, the following optional libraries can be installed to enable printing the
backtrace in the error messages:
* libunwind
* libdw

The following mandatory tools must be installed:
* A C/C++ compiler:
  * gcc/g++ 
  * clang/clang++ (Minimum version 8.0)
* cmake
* pkg-config

For generating the documentation, the following tools must be installed:
* doxygen
* graphviz

#### <a name="user-content-linux"></a> Linux

The dependencies can be installed on Ubuntu by using the following command:
```sh
sudo apt install \
    gcc \
    g++ \
    cmake \
    pkg-config \
    libunwind-dev \
    llvm-10-dev \
    libclang-10-dev \
    libncurses-dev \
    libboost-system-dev \
    libboost-filesystem-dev \
    libctemplate-dev \
    libdw-dev \
    doxygen \
    graphviz
```

#### <a name="user-content-macos"></a> MacOS

libunwind and libdw are not available in macOS, as such the backtrace support
is not supported in macOS.

libclang/llvm and libncurse libraries as well as pkg-config and cmake tool can
be installed via brew.
```sh
brew install llvm
brew install ncurses
brew install pkg-config
brew install cmake
brew install doxygen
brew install graphviz
```

Note: At the time of writing, brew is not officially supported on the Apple Silicon (M1)
but the brew command can be executed with the `-s` option to compile and install from source.

libctemplate must be compiled and installed from [source](https://github.com/OlafvdSpek/ctemplate).
For instance by executing the following commands:
```sh
git clone https://github.com/OlafvdSpek/ctemplate.git
cd ctemplate
./autogen.sh
mkdir build
export LIBCTEMPLATE_INSTALL=$(pwd)/install
mkdir ${LIBCTEMPLATE_INSTALL}
cd build
../configure --prefix=${LIBCTEMPLATE_INSTALL}
make
make install
```

### <a name="user-content-compilation-steps"></a> Compilation steps

EasyMock uses CMake as software build management. The commands below can be
used to compile the tool. Before copying and pasting those lines in your terminal,
make sure first to set the EASYMOCK_SOURCE environment variable to the place
where the EasyMock's code is installed.
```sh
cd $EASYMOCK_SOURCE
mkdir build #Referred as $EASYMOCK_BUILDDIR below
cd build
cmake ..
make -j $(nproc)
```

On macOS, the path to `libctemplate` must be given to cmake by using the `CTEMPLATE_LIB_INSTALL` cache entries.
I.E:
```sh
cmake ../ -DDCTEMPLATE_LIB_INSTALL=${LIBCTEMPLATE_INSTALL}
```

Note: On macOS, the following command `cmake ../ -GXcode <rest of parameters>` can be used to generate the
Xcode project to be opened with [Xcode IDE](https://developer.apple.com/xcode/), but the Makefiles
work just fine.

When the compilation is finished
* on Linux:
    * the binary to generate the mock called [EasyMockGenerate][createAMock] is
under `$EASYMOCK_BUILDDIR/src/easyMockGenerate/src/EasyMockGenerate`
    * the shared library to be linked to the unit test called
[libEasyMockFramework.so][libEasyAPI]
is under `$EASYMOCK_BUILDDIR/src/easyMockFramework/src/libEasyMockFramework.so`
* on macOS:
    * the binary to generate the mock called [EasyMockGenerate][createAMock] is
under `$EASYMOCK_BUILDDIR/src/easyMockGenerate/src/<buildType>/EasyMockGenerate`
    * the shared library to be linked to the unit test called
[libEasyMockFramework.dylib][libEasyAPI]
is under `$EASYMOCK_BUILDDIR/src/easyMockFramework/src/<buildType>/libEasyMockFramework.dylib`

### <a name="user-content-rvdb"></a> Release vs Debug build

If you download the compressed archive of EasyMock, the release build is
compiled. The release build produces:
* [EasyMockGenerate][createAMock] which is the binary which can be used to
generate mocks.
* `libEasyMockFramework.so` which is a shared library to be linked to the
final unit test binary. See the [hello world example][helloWorldExample] for a
full example on how to use it.

The debug build is selected when one of the following condition is met
- the directory `$EASYMOCK_SOURCE/.git` is present (it can be empty).
- the directory `$EASYMOCK_SOURCE/.hg` is present (it can be empty).
- the following parameter is given to the cmake command: `-DCMAKE_BUILD_TYPE=Debug`

The debug build passes extra debug compilation flags and takes longer because it
also compiles all the [tests][ut]. After the debug build has been
built, use the command `make check` to run all the tests.

## <a name="user-content-libeasyapi"></a> libEasyMockFramework's API

The unit test which is using `libEasyMockFramework.so` should include
`easyMock.h` which is in `$EASYMOCK_SOURCE/src/easyMockFramework/include/`.
A good practice to allow your code to be able to include that header
is to use the `-I` option to point to that directory.

That file defines a set of C api to initialise the EasyMock framework and check
that the mocks have been called as expected.

Even though EasyMock is implemented in C++, it was chosen to provide a C API
to not force the unit test to be written in C++.

For the ease of accessibility, the documentation has been copied into this page.

See the [hello world example][helloWorldExample] for a full example on how
to use them.

```c
/*
 * Initialises EasyMock.
 *
 * This must be called at the beginning of every test case.
 */
void easyMock_init();

/*
 * Checks that EasyMock has reported at least one error.
 *
 * This must be called at the end of a unit test after the function being tested
 * has been called. If an error has happened, the API easyMock_getError* can be
 * used to retrieve the error messages.
 *
 * Returns 1 if no error has happened.
 * Returns 0 if at least an error has happened.
 */
int easyMock_check();

/*
 * Returns all the errors in a single buffer.
 *
 * The buffer can directly be printed to the standard output if needed.
 *
 * The returned buffer must not be freed by the caller.
 */
const char *easyMock_getErrorStr();

/*
 * Returns all the errors in an array of pointer to constant array of characters.
 *
 * The parameter size is an output value which tells how many errors
 * are reported into the array.
 *
 * The returned buffer must not be freed by the caller.
 */
const char ** easyMock_getErrorArr(unsigned int *size);

/*
 * Sets whether the error messages should contain the call stack or not.
 *
 * The default is to print the callstack into the error messages.
 */
void easyMock_printCallStack(bool val);

/*
 * Sets whether the mock should verify if the mocks have been called in the
 * order they have been expected.
 *
 * The default is to check that the mocks have been called in the order they
 * have been expected (via the *_ExpectAndReturn* API)
 */
void easyMock_checkCallsOrder(bool val);
```

## <a name="user-content-cam"></a>Create a mock

A good start to get acquainted with EasyMockGenerate is to look at its help.

```
# ./EasyMockGenerate -h
Generate mocks to be used into unit tests.

EasyMock takes a header file ('-i') and generate a mocked version of functions declared in that header file in a target directory ('-o').
The tool generates mocks for functions directly declared in the header file. I.e. not coming from other included files.
'--generate-included-functions' option can be used to generate mocks of functions declared in included files.

Parameters not recognised by EasyMock (e.g. -I, -D) are given to the parser responsible for parsing the header file.
The same options used by a Clang compiler are recognised by EasyMock's parser.

Usage:
./EasyMockGenerate [OPTIONS...]

OPTIONS are:
	-i <header>                    Input header file.

	-o <directory>                 Output directory.

	--cwd <directory>              Change to the directory passed on this parameter before running the parser.
	                               Relative paths given to '-i' and '-o' will be taken from the path given to '--cwd'.

	--mock-only <function>         Mock only the function specified in this parameter.

	--generate-types               Generate the used type instead of including the original header.
	                               When using this option, the original header (i.e. the header given to -i) doesn't
	                               need to be used when compiling the mock.
	                               The generated functions signature will not contain any function attribute unless
	                               the --generate-attribute option is used.

	--generate-included-functions  Generate the mocks of functions declared in header files that the input file ('-i') includes.

	--generate-comparator-of       Generate comparator function of the given type. The comparator can be used in the *_ExpectAndReturn function.
	                               If comparators of the same type are generated on several header file with function that use
	                               the same type, then compiling and linking the generated mocked together will generate double
	                               symbol definition.
	                               Special value 'EasyMock_all_comparators' can be used to generate the comparator of all the composable types.
	                               Can be used several times.

	--generate-attribute           Generate the function attribute if the function has been declared with it.
	                               E.G. if a function has been declared with the format attribute, give the parameter
	                               "--generate-attribute format" will generate the code __attribute__((format(x, y, z))) where
	                               x, y and z are the parameters given to the format attribute.
	                               Can be used several times.

	--ignore-generation-of         Ignore the parsing and the generation of the given function.
	                               Can be used several times.

	--ignore-field-generation-of   Ignore the field generation of the given struct or union type.
	                               Consider using this option if mocking some types takes too much time.
	                               The list is given to the parser which ignores the reporting the fields of
	                               the given types.
	                               Can be used several times.

	-h, --help                     Print usage.
```

As stated in the help, the parameters not recognised by EasyMock will be passed
to the parser responsible for parsing the header file. Currently, the parser is
LLVM. Typically, the same compile flags (such as `-I` and `-D`) that are given
to compile the source file including the header that is being mocked in the
production code should be given as extra parameters to EasyMock.

When using the `cwd` parameter, any relative parameter given to `-i` or `-o` will
be used after EasyMock has changed his current working directory.

## <a name="user-content-gf"></a>Generated functions

To configure the generated mocks, EasyMock generates 2 function families
1. `*_ExpectAndReturn`
2. `*_ExpectReturnAndOutput`

On top of that, EasyMock implements the mocked function with all the code
needed to fake its behaviour.

The `*_ExpectAndReturn` family is used to configure the mock for expecting
a set of parameters (if any) as well as the return value (if any).

The `*_ExpectReturnAndOutput` family does the same as `*_ExpectAndReturn` family,
but it also allows specifying values that copied onto parameters that are pointer
to represent the fact that the mocked function is using those parameters as
output parameter.

For instance, considering the following function

```c
bool foo(int bar, int *outParam);
```
EasyMock generates those 2 functions
```c
void foo_ExpectAndReturn(int bar, int *out, bool to_return, EasyMock_Matcher easyMock_match_bar, EasyMock_Matcher easyMock_match_out);
void foo_ExpectReturnAndOutput(int bar, int *out, bool to_return, EasyMock_Matcher easyMock_match_bar, EasyMock_Matcher easyMock_match_out, int *out_outParam);
```
Note that the `to_return` parameter is not present because the mocked function's
return value is `void`.

In the specific case where a void pointer is part of the mocked function
parameter's list, the `*_ExpectReturnAndOuput` family will have 2 parameters to
specify the output data. The first being the pointer onto which to copy the
data and the second being the size of the data to copy. The user of the mock
can use those 2 parameters to specifies values that are returned by the mocked
function via its output parameter.

I.e. When mocking
```c
void voidOut(void *outParam);
```
The following `*_ExpectReturnAndOutput` function's family is generated
```c
void voidOut_ExpectReturnAndOutput(void* out_outParam, size_t out_outParam_size);
```
EasyMock_Matcher is a pointer to function type defined as following:
```c
typedef int(*EasyMock_Matcher)(void *currentCall_ptr, void *expectedCall_ptr, const char *paramName, char *errorMessage)
```
The purpose of a matcher is to compare the value given by the function calling
the mock with the value that was passed to the corresponding parameter of the
`*_ExpectAndReturn` family or `*_ExpectReturnAndOutput` family.
It returns 0 if everything matches or anything else if it does not.

EasyMock defines the following matchers into `easyMock.h` which compares
the C basic types:
```
cmp_char
cmp_u_char
cmp_short
cmp_u_short
cmp_int
cmp_u_int
cmp_long
cmp_u_long
cmp_long_long
cmp_u_long_long
cmp_float
cmp_double
cmp_long_double
cmp_pointer
cmp_str
```

Whenever a struct is present in the list of the mocked function parameters
and the `--generate-comparator-of` parameter is given to EasyMock,
EasyMock generates the corresponding matcher which compares the struct
fields one by one and yield an error if one of the field's value is not
matching. The name of the generated struct matcher is in the form of
```
cmp_<structName>
```

If a pointer to a struct is present in the list of mocked function parameters,
and the `--generate-comparator-of` parameter is given to EasyMock,
EasyMock generates the corresponding matcher which first dereference the struct pointer
and call the matcher which compares the struct fields one by one and yield an
error if one of the field's value is not matching. The name of the generated 
struct matcher is in the form of
```
cmp_deref_ptr_<structName>
```

Attention must be taken that in the following situation
```c
struct s1
{
  int a;
};

struct s2
{
  struct s1 f;
};
```
if the parameter `--generate-comparator-of s2` is given, the parameter
`--generate-comparator-of s1` must also be given else the generated mock will not compile.
The reason is that the generated comparator assumes that comparators of contained fields
types are available.

A user can implement its own version of EasyMock matchers by creating
functions that match the `EasyMock_Matcher` type.

## <a name="user-content-utm"></a>Using the mock
Once the mocks have been generated, the unit test must call the
`*_ExpectAndReturn` and/or `*_ExpectReturnAndOutput` function family to
configure the behaviour of the mock. For each time the function to be
tested calls the mocked dependency, a call to the `*_ExpectAndReturn` or
`*_ExpectReturnAndOutput` must be made to configure how the mock must behave
i.e. which value it must return, which parameter to expects.

Simply put:
* The first call to `*_ExpectAndReturn` or `*_ExpectReturnAndOutput` configures
how the mock will be behaving when the mock is call the first time.
* The second call to `*_ExpectAndReturn` or `*_ExpectReturnAndOutput` configures
how the mock will be behaving when the mock is call the second time.
* ...

A complete example on how to use the mock is present in the
[hello world example][helloWorldExample].

## <a name="user-content-ut"></a>Unit tested
Because EasyMock's main usage is to be used for writing unit tests,
it is important that it thoroughly tested. The last thing we want to do is
to begin to debug the mocking framework when writing test code. When
configured to build the Debug version, the command `make check` is available
to run the massive amount of test cases implemented.

See all the badges:

| Test results |
| :----------: |
| ![Ubuntu 18.04 x86 gcc](https://github.com/lcarlier/EasyMock/actions/workflows/validate-ubuntu-18-04-x86-gcc.yml/badge.svg?branch=master) |
| ![Ubuntu 18.04 x86 clang](https://github.com/lcarlier/EasyMock/actions/workflows/validate-ubuntu-18-04-x86-clang.yml/badge.svg?branch=master) |
| ![Ubuntu 20.04 x86 gcc](https://github.com/lcarlier/EasyMock/actions/workflows/validate-ubuntu-20-04-x86-gcc.yml/badge.svg?branch=master) |
| ![Ubuntu 20.04 x86 clang](https://github.com/lcarlier/EasyMock/actions/workflows/validate-ubuntu-20-04-x86-clang.yml/badge.svg?branch=master) |
| ![Ubuntu 18.04 arm64 gcc](https://github.com/lcarlier/EasyMock/actions/workflows/validate-ubuntu-18-04-arm64-gcc.yml/badge.svg?branch=master) |
| ![Ubuntu 18.04 arm64 gcc](https://github.com/lcarlier/EasyMock/actions/workflows/validate-ubuntu-18-04-arm64-clang.yml/badge.svg?branch=master) |
| ![Ubuntu 20.04 arm64 gcc](https://github.com/lcarlier/EasyMock/actions/workflows/validate-ubuntu-20-04-arm64-gcc.yml/badge.svg?branch=master) |
| ![Ubuntu 20.04 arm64 clang](https://github.com/lcarlier/EasyMock/actions/workflows/validate-ubuntu-20-04-arm64-clang.yml/badge.svg?branch=master) |
| ![MacOS 10.15 gcc](https://github.com/lcarlier/EasyMock/actions/workflows/validate-macos-10-15-gcc.yml/badge.svg?branch=master) |
| ![MacOS 10.15 clang](https://github.com/lcarlier/EasyMock/actions/workflows/validate-macos-10-15-clang.yml/badge.svg?branch=master) |

## <a name="user-content-iwtpttdoe"></a> I want to participate in the development of EasyMock
That's great! A good place to start is by reading the [architecture][arch] of EasyMock.

## <a name="user-content-restriction"></a> Restriction
Currently, EasyMock only supports mocking of C functions.
Mocking of C++ functions and classes is planned.

## <a name="user-content-br"></a> Bug report
If you find a bug, it is very appreciated creating a [bug report](issues).
Please attach into the bug report, the command that you gave to
EasyMockGenerate and also the header file (or the relevant part of it) which
was used to generate the mock.

## <a name="user-loft"></a> License of the tool
This project is released under the GPL-v3 license.

## <a name="user-logc"></a> License of the generated code
The code that the tool generates is under the MIT license as followed
```
MIT License

Copyright (c) 2021 Laurent Carlier

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

## <a name="user-content-tfn"></a> The final note
The best of care and attention was given to implement and document EasyMock.
If something is unclear or is not correct, it is very much appreciated contacting
the author and asking for further explanation or fix.

## <a name="user-content-thanks"></a> Thanks
EasyMock's principle is based on [opmock](https://sourceforge.net/p/opmock/wiki/Home/)
created by Pascal Ognibene. EasyMock is however not a fork because I
implemented it from scratch without looking at the source code of opmock.

[whatIsEasymock]: #user-content-wie
[compileEasymock]: #user-content-htce
[dependencies]: #user-content-dependencies
[linux]: #user-content-linux
[macos]: #user-content-macos
[compilationSteps]: #user-content-compilation-steps
[relVsDeb]: #user-content-rvdb
[libEasyAPI]: #user-content-libeasyapi
[createAMock]: #user-content-cam
[genFun]: #user-content-gf
[usingMock]: #user-content-utm
[ut]: #user-content-ut
[participate]: #user-content-iwtpttdoe
[restriction]: #user-content-restriction
[bugReport]: #user-content-br
[loft]: #user-loft
[logc]: #user-logc
[finalNote]: #user-content-tfn
[thanks]: #user-content-thanks

[helloWorldExample]: docs/hello_world.md
[arch]: docs/architecture.md
