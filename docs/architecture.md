# Architecture of EasyMock

## Table of content
* [Introduction][intro]
* [Structure of the repository][sotr]
* [libEasyMockFramework.so's overall software architecture][losa]
    * [Registration of mocks to libEasyMockFramework.so][romtl]
* [EasyMockGenerate's overall software architecture][eosa]
    * [EasyMock internal objects][eio]
    * [Command line parsing][clp]
* [Architecture choices][archChoices]
    * [Memory management][memMgmt]
* [Tests][tests]
    * [EasyMock internal objects tests][eioTests]
    * [easyMockGenerate][easyMockGenerate]
        * [Factories as test classes][fatc]
        * [Test of the parser (parser directory)][totp]
        * [Test of generated mock (generate directory)][togm]
    * [End-to-end tests][e2e]

## <a name="user-content-intro"></a> Introduction

The goal of this page is to give a description of the overall software
architecture, how the code is organised and also what are the concepts
that were followed when writing EasyMock.

There is also be an explanation on all the tests that have been written and
how they are organised.

This page is not going over the specific of the classes, interfaces and the
implementation since all of this information is available in the doxygen
documentation.

To generate the doxygen documentation, you can use the following line
```sh
cd $EASYMOCK_SOURCE
doxygen docs/doxygen/Doxyfile
```
The documentation will then be available in `$EASYMOCK_SOURCE/docs/doxygen/html`

Open the file `index.html` with your favorite web browser.

## <a name="user-content-sotr"></a> Structure of the repository

```
docs ──────────────────────────────> Contains the MD documentation of the project
├── doxygen ───────────────────────> Contains the doxygen documentation of the project
src
├── easyMockFramework ─────────────> Contains the code to generate libEasyMockFramework.so
│   ├── include
│   └── src
├── easyMockGenerate ──────────────> Contains the code to generate EasyMockGenerate executable
│   ├── include
│   └── src
│       ├── CTemplateGenerator
│       ├── CXXOptsCmdLineParser
│       └── LLVMParser
test ──────────────────────────────> Contains the code of all the tests
├── ...
├── FunctionAttributeGen
├── ...
├── easyMockGenerate
│   ├── CommandLineParser
│   ├── common
│   ├── commonClasses
│   ├── generate
│   ├── include
│   ├── includeCommonClasses
│   └── parser
├── ...
└── StructType
```

## <a name="user-content-losa"></a>libEasyMockFramework.so's overall software architecture

libEasyMockFramework.so defines the following APIs into the following header
files:

* `easyMock.h`: Defines the API which is called by the unit tests using the
mocked header file.
* `easyMock_framework.h`: Defines the API which is called by the mocked header
code.
* `MockedFunction.h`: Defines the MockedFunction class which is a templated
class used by the mocked header code to help to mock a specific function.

Consult the Doxygen documentation for more details about those APIs. The
documentation of `easyMock.h` is also available in the main documentation
page.

### <a name="user-content-romtl"></a>Registration of mocks to libEasyMockFramework.so

When `libEasyMockFramework.so` is loaded, all the static object are initialised.
One of the static object is the EasyMock class. It is initialised with the
following attribute `__attribute ((init_priority(101)))`.

Afterwards, the mocks can register themselves by calling the
`easyMock_registerMockedFile` function defined in `easyMock_framework.h`. To do
that, the mock defines a static function with the following attribute
`__attribute__((constructor(102)))`.

Playing with the loading priorities allows the EasyMock objects
to be properly initialised before the mocks can register themselves.

## <a name="user-content-eosa"></a> EasyMockGenerate's overall software architecture

The logic of the main code is actually very simple and written to be modular.

There are 2 modules:
- the parser: responsible for parsing the C code and to return a representation
of the functions that are parsed in a specific header file. The parsed function
are represented using the [EasyMock internal objects](#user-content-eio).
- the code generator: responsible for taking the representation given by the parser
and to generate the code that mocks the functions.

Each of those modules is instantiated and executed as needed by the main
function.

Both of the module have their own interface which means that it is easy
to replace one implementation with another if needed.
- The interface's name of the parser is `CodeParserItf`.
- The interface's name of the code generator is `CodeGeneratorItf`.

The current implementation provides an implementation for the parser and
the code generator:
- the implementation of the parser is based on LLVM.
- the implementation of the code generate uses Google ctemplate.

If for any reason, there might be a need to change the parser implementation
using another library, the work to be done is just to implement a new parser
by inheriting `CodeParserItf` and to modify the main code to give the choice to
the user to choose in between both of implementation.

The representation of the parsed function is done via the
[EasyMock internal objects](#user-content-eio).

### <a name="user-content-eio"></a> EasyMock internal objects

Here is the class diagram of the EasyMock internal objects.

![TypeItf class diagram](classTypeItf__inherit__graph.png)

It gives all what all the necessaries to represent any C function and any C type.

For complete information about each of the classes consult the doxygen documentation.

Beside those object, there is also another class tree to represent the concept
of `structure's field`, `parameter` and `return value`. This can be seen from
the following class diagram.

![Declarator class diagram](classDeclarator__inherit__graph.png)

A complete explanation of those classes is available in the doxygen documentation.

[All the care has been taken][iotcamc] to make sure that all the internal
objects of Easymock are movable. Copy is not allowed to ensure that the memory footprint
remains as small as possible.

### <a name="user-content-clp"></a> Command line parsing
The command line parsing functionality is a custom-made command line parser library.
Libraries like [ccxopts](https://github.com/jarro2783/cxxopts) have been considered
but none of them was flexible enough for EasyMock's use case.

This library is abstracted by the CommandLineParserItf interface. It is defined
in `$EASYMOCK_SOURCE/src/EasyMockGenerate/include/CommandLineParserItf.h`. 
Tests validating the `CommandLineParserItf` interface are implemented.

This means that the command line parsing can be swapped if the need arises.

## <a name="user-content-arch-choices"></a> Architecture choices
Personal note from the author:
```
This project is the opportunity to improve my C++ skills in my own way.
I first took the choice to implement manually copy and move operators which was a
valuable learning experience.

However, I learned the hard way that even though it is possible and
quite easy to implement copy and move constructor/operators using technics like
copy and swap idiom, it results of doing deep copies of objects which is 
not memory efficient. Some runs could reach more than 10G of memory
usage.

Up to change 2e147c3170cc5e965a36ced4f8b2e7bde8935682, the old memory management
system was used and is now replaced by the usage of smart pointers.
```

### <a name="user-content-memory-management"></a>Memory management
The [EasyMock internal objects][eio] are movable only I.e. the copy constructor/operator
have been explicitly deleted to avoid accidental copies of objects.

All the objects inheriting from the `Declarator` base class have a `std::shared_ptr<TypeItf>`
member containing the type that the declarator declares. Using a `std::shared_ptr<TypeItf>` is
a good idea because different declarators (e.g. different function parameters) can declare a variable
of the same type and having a copy of the type would be a waste of memory. The same applies for
type objects, I.e. inheriting from `TypeItf`, pointing to other types. Examples of such types are
`Pointer` and `TypeDefType` objects. They have a `std::shared_ptr<TypeItf>` member as well since having a copy
of the type would be a waste of memory. For example, `Pointer` and `TypeDefType` objects can refer to
types that are used by `Parameter` objects directly.

The `ElementToMockContext` objects gets populated by the parser with a vector of `ElementToMockContextElement`
I.e. an `ElementToMockContextList` object.
```c++
using ElementToMockContextList = std::vector<ElementToMockContextElement>;
```
Each `ElementToMockContextElement` object is a variant of `FunctionDeclaration`.
```c++
using ElementToMockContextElement = std::variant<FunctionDeclaration>;
```
A variant is used here for the following reasons:
* A function declaration is a unique instance, so it is needed to store a full unique copy of the object.
* To reduce the impact on heap. Indeed, `std::unique_ptr<ElementToMock>` would be possible but inefficient. 
* When C++ will be supported, new element to mock, such as class declaration, can be added to the variant.

## <a name="user-content-tests"></a> Tests

EasyMock is thoroughly tested. The test framework chosen is GoogleTests.
In order to run the tests, the command `make check` can be used.

There are 3 types of tests implemented:
* EasyMock internal objects tests
* easyMockGenerate tests comprising parser and generator tests
* End-to-end tests

### <a name="user-content-eio-tests"></a> EasyMock internal objects tests
Validates the specific behavior of the EasyMock internal objects works as expected.

The tests are in a folder named after the class name (e.g. StructType) and has a
single .cpp file containing all the test cases for that particular class.

### <a name="user-content-easyMockGenerate"></a> easyMockGenerate
This folder contains all the logic to validate EasyMockGenerate.
`libEasyMockFramework.so` is also validated here because the generated mocks
uses libEasyMockFramework.so.

The sub-directories are organised as followed:
* CommandLineParser: Contains the code which test the command line parser of
EasyMockGenerate.
* common: Contains the UT which tests the copyability and movability of all
the [EasyMock internal objects][eio].
* commonClasses: Implementation of all the function factories test code.
* generate: Contains the tests that verifies that the generated mocks compiles
and works as expected.
* include: Contains the header file that are mocked by the tests.
* includeCommonClasses: Contains the definition of the function factories
test code.
* parser: Contains the test which verifies the parser functionalities.

The tests present in this folder are divided in 2 categories
1. [Test the parser][totp]
2. [Test of generated mocks][togm]

#### <a name="user-content-fatc"></a>Factories as test classes
To help to test the parsing of the header file and the generation of the mocks,
factories are implemented. One factory represents a specific C function to be
mocked/tested. This gives the flexibility for adding new function to the tests
easily. If a new function (e.g. taking a specific new specific struct
as parameter) needs to be tested, it is only required to implement the factory,
register it into the list and all the already implemented tests will run
against it automatically. The factory actually represents a `"test class"`
and is implemented using Google's templated test case. The interface of the
factory defined in FunctionFactory.h is described into the doxygen documentation.

#### <a name="user-content-totp"></a> Test of the parser (parser directory)
Each of the test class which verify the generated mocks perform the following
actions:
1. Gets the path to the header file to be parsed from the factory.
2. Calls the API that parses the header file.
3. Verifies that the set of [EasyMock internal object][eio] returned by the
parser is as expected.

#### <a name="user-content-togm"></a> Test of generated mocks (generate directory)
Each of the test class which verify the generated mocks perform the following
actions:
1. Receives a hardcoded set of [EasyMock internal object][eio] from the factory.
2. Calls the API to generate the mocks.
3. Compiles a .so containing the results of the compilation of the file created
in step 2. This step actually tests that the generated code can be compiled
properly.
4. Load the .so
5. Calls the mocks. This step is different in each test case within the test
class and validate that the generated code can be executed without any error.
6. Verifies the status of EasyMock. I.E Checks whether an error has occurred
when it should, etc...

The very generic tests classes are implemented inside `test_genGenerate.cpp`,
`test_compileOnly.cpp` and `test_genGenerateOutputPtr`. Other more specific
tests classes are implemented in the same directory. The only difference is
that they will target a specific factory instead of being able of executing
their test cases against a list of factories.

### <a name="user-content-end2end"></a> End-to-end tests

The end-to-end tests validates that the EasyMockGenerate binary is
working properly. Rather than separating the call of the parser and the call
of the generator in 2 different tests (like in the
[easyMockGenerate directory][easyMockGenerate]), those tests call directly the
EasyMockGenerate binary to validate that the end user experience is working
as it is expected. Eventually, some small test cases using the generated
mocks (as the user would write them) are run.

The name of end-to-end tests directories corresponds to the test case name
(e.g `FunctionAttributeGen`). End-to-end tests have a `runTest.sh` which is called
by CMake. The validation of the test is done in `runTest.sh`.

[intro]: #user-content-intro
[sotr]: #user-content-sotr
[losa]: #user-content-losa
[romtl]: #user-content-romtl
[eosa]: #user-content-eosa
[eio]: #user-content-eio
[clp]: #user-content-clp
[archChoices]: #user-content-arch-choices
[memMgmt]: #user-content-memory-management
[iotcamc]: #user-content-iotcamc
[tests]: #user-content-tests
[eioTests]: #user-content-eio-tests
[easyMockGenerate]: #user-content-easyMockGenerate
[fatc]: #user-content-fatc
[totp]: #user-content-totp
[togm]: #user-content-togm
[e2e]: #user-content-end2end
