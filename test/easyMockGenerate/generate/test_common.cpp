#include "test_common.h"

#include <sys/select.h>
#include <dlfcn.h>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <unistd.h>
#include <string>
#include <limits.h>
#include <errno.h>
#include <stdlib.h>
#include <functional>
#include <iostream>
#include <fstream>

#include <CodeGeneratorCTemplate.h>

#include <easyMock.cpp> //To access easyMock static object

#include <ComposableType.h>

#define PIPE_READ 0
#define PIPE_WRITE 1

static void readStdoutStderrUntilEnd(int fdStdOut, int fdStdErr, std::string &stdOut, std::string &stdErr);
static void appendReadIntoString(int fd, std::string &str, const char *strName, bool *noMoreToRead);
static void loadSo(const char *pathToSo, const char *functionToLoadSymbol, const char *functionExpectAndReturnSymbol, const char* functionExpectReturnAndOutputSymbol, const char *comparatorToMatch, void **funcPtr, void **funcPtr_expect, void **funcPtr_matcher, void **funcPtr_output_ptr, void **handle, bool& m_rmDir, bool& m_load_function);
static void cleanTest(void **handle, const std::string &mockDir, bool rmDirectory);
static void dumpToFile(const std::string& dir, const std::string& file, std::string& data, bool append);

easyMockGenerate_baseTestCase::easyMockGenerate_baseTestCase(const std::string functionToMock, const std::string pathToFileToMock, const std::string mockDir, bool generateTypes, bool loadFunction, bool isCpp, bool rmDir) :
::testing::Test {} ,
m_functionToMock {functionToMock },
m_comparatorToMatch {"" },
m_pathToFileToMock { pathToFileToMock },
m_mockDir { mockDir + "_" + ::testing::UnitTest::GetInstance()->current_test_info()->name() },
m_rmDir { rmDir },
handle { nullptr },
m_fptr { nullptr } ,
m_fptr_expect { nullptr },
m_fptr_matcher { nullptr },
m_fptr_output_ptr { nullptr },
m_generate_types { generateTypes },
m_load_function {loadFunction },
m_finalMockDir { "" },
m_isCpp{isCpp}
{
}

void easyMockGenerate_baseTestCase::setComparatorToMatch(const std::string comparatorToMatch)
{
  m_comparatorToMatch = comparatorToMatch;
}

std::stringstream &operator<<(std::stringstream &out, const EasyMock_ErrorArrayPrinter &obj)
{
  const char **curArrChar = obj.m_in;
  const char *curChar;
  for(curChar = *curArrChar; curChar != nullptr; curArrChar++, curChar = *curArrChar)
  {
    out << curChar << std::endl;
  }
  return out;
}

bool isFifoCallEmpty()
{
  return easyMock.isCurrentCallEmpty();
}

const std::string& getCurrentFifoCall()
{
  return easyMock.getCurrentFifoCall();
}

size_t fifoCallSize()
{
  return easyMock.getFifoCallSize();
}

void easyMockGenerate_baseTestCase::SetUp()
{
  prepareTest(m_ctxt, m_functionToMock, m_comparatorToMatch, m_pathToFileToMock, m_mockDir, (void **) &m_fptr, (void **) &m_fptr_expect, (void **) &m_fptr_matcher, (void **)&m_fptr_output_ptr, &handle);

  easyMock_init();

  ExtraSetup();
}

void easyMockGenerate_baseTestCase::TearDown()
{
  if(::testing::Test::HasFailure())
  {
    m_rmDir = false;
  }
  cleanTest(&handle, m_mockDir, m_rmDir);
  ExtraTearDown();
}

void easyMockGenerate_baseTestCase::getFunPtr(void** fPtr, void** fExpectPtr)
{
  if(fPtr)
  {
    *fPtr = m_fptr;
  }
  if(fExpectPtr)
  {
    *fExpectPtr = m_fptr_expect;
  }
}

void easyMockGenerate_baseTestCase::getFunPtr(void** fPtr, void** fExpectPtr, void **fMatcher)
{
  getFunPtr(fPtr, fExpectPtr);
  if(fMatcher)
  {
    *fMatcher = m_fptr_matcher;
  }
}

void easyMockGenerate_baseTestCase::getFunPtr(void** fPtr, void** fExpectPtr, void** fMatcherPtr, void** fOutputPtr)
{
  getFunPtr(fPtr, fExpectPtr, fMatcherPtr);
  if(fOutputPtr)
  {
    *fOutputPtr = m_fptr_output_ptr;
  }
}

void createDir(const std::string &dir)
{
  boost::system::error_code errCode;
  boost::filesystem::create_directories(dir, errCode);
  ASSERT_EQ(errCode.value(), 0) << "Error creating directory " << dir << " errCode: " << errCode.message();
}

void rmDir(const std::string &dir)
{
  boost::system::error_code errCode;
  boost::filesystem::remove_all(dir, errCode);
  ASSERT_EQ(errCode.value(), 0) << "Error removing directory " << dir << " errCode: " << errCode.message();
}

void easyMockGenerate_baseTestCase::prepareTest(const ElementToMockContext &elem, const std::string &functionToMock, std::string &comparatorToMatch, const std::string &fullPathToFileToMock, const std::string &mockDir, void **fptr, void **fptr_expect, void **fptr_matcher, void **fptr_output_ptr, void **handle) {
  char cwd[PATH_MAX];
  ASSERT_NE(getcwd(cwd, PATH_MAX), nullptr)
                        << std::endl << "getcwd error. errno: " << errno << "(" << strerror(errno) << ")" << std::endl;
  CodeGeneratorCTemplate generate;
  generate.setGenerateUsedType(m_generate_types);
  generate.setGenerateStructComparator({"EasyMock_all_comparators"});
  generate.setCpp(m_isCpp);

  std::string pathAndfileNameToMock = boost::filesystem::path(fullPathToFileToMock).stem().string();
  std::string fileNameToMock = boost::filesystem::path(pathAndfileNameToMock).filename().string();
  m_finalMockDir = mockDir ;
  if (m_generate_types)
  {
    m_finalMockDir.append("/typeGenerate");
  }
  else
  {
    m_finalMockDir.append("/useHeader");
  }
  createDir(m_finalMockDir);
  bool codeGen = generate.generateCode(m_finalMockDir, fullPathToFileToMock, elem);
  ASSERT_TRUE(codeGen) << std::endl << "Generation failed." << std::endl << "cwd: " << cwd << std::endl;
  int status;

  std::string objFile(m_finalMockDir);
  objFile.append("/easyMock_");
  objFile.append(pathAndfileNameToMock);
  std::string fileToCompile(objFile);
  objFile.append(".o");
  fileToCompile.append(m_isCpp ? ".cpp" : ".c");
  std::string initLog{std::string("Log for: ") + fileToCompile + std::string("\n")};
  dumpToFile(m_finalMockDir, "stdout.txt", initLog, false);
  initLog = std::string("Log for: ") + fileToCompile + std::string("\n");
  dumpToFile(m_finalMockDir, "stderr.txt", initLog, false);
  const char *cCompiler = m_isCpp ? CXX_COMPILER_IN_USE : C_COMPILER_IN_USE;
  std::vector<const char *> compileMockCmd = {cCompiler, "-Wall", "-Werror", "-g", "-O0", "-fpic", "-I", m_finalMockDir.c_str(),
                                        "-I", PROJECT_ROOT_DIR"/src/easyMockFramework/include", "-I",
                                        PROJECT_ROOT_DIR"/test/easyMockGenerate/include", "-o", objFile.c_str(), "-c",
                                        fileToCompile.c_str()};
  if(m_isCpp)
  {
    compileMockCmd.push_back("-std=gnu++17");
  }
  compileMockCmd.push_back(nullptr);
  executeCmd(compileMockCmd, &status);
  ASSERT_EQ(status, 0) << std::endl << "Compilation mock failed " << std::endl << "cwd: " << cwd << std::endl;

  std::vector<const char *>fileObjFile =
  {
    "file",
    objFile.c_str(),
    nullptr
  };
  executeCmd(fileObjFile, &status);
  ASSERT_EQ(status, 0);

  std::string pathToLib(mockDir);
  pathToLib.append("/lib");
  pathToLib.append(fileNameToMock);
#if defined(__APPLE__)
  pathToLib.append(".dylib");
#elif defined(__linux__)
  pathToLib.append(".so");
#else
#error "OS not supported"
#endif
  std::vector<const char *> compileLibCmd =
  {
    cCompiler,
    "-shared",
#if defined(__clang__)
    "-undefined", "dynamic_lookup",
#endif
    "-o",
    pathToLib.c_str(),
    objFile.c_str(),
  };
  if(m_isCpp)
  {
    /*
     * Make sure the share library is linked against the same libc++ as test_easyMockGenerate_generate executable
     * using -L.
     * If not VERY WIERD THINGS such as integer not printed correctly in stringstream, or crash in
     * operator<<(T&) of basic_stream happens.
     */
    compileLibCmd.push_back("-L");
    compileLibCmd.push_back(LLVM_LIBDIR);
  }
  compileLibCmd.push_back(nullptr);
  executeCmd(compileLibCmd, &status);
  ASSERT_EQ(status, 0) << std::endl << "Compilation lib failed " << std::endl << "cwd: " << cwd << std::endl;

  std::vector<const char *> fileLibFile =
  {
    "file",
    pathToLib.c_str(),
    nullptr
  };
  executeCmd(fileLibFile, &status);
  ASSERT_EQ(status, 0);

  std::string mangledFunctionSymbol;
  std::string mangledExpectAndReturn;
  std::string mangledExpectReturnAndOutput;
  if(m_isCpp)
  {
    mangledFunctionSymbol = getMangledString(pathToLib.c_str(), functionToMock);
    std::string expectAndReturnSymbol = std::string{} + "EasyMock::" + functionToMock + "::ExpectAndReturn";
    mangledExpectAndReturn = getMangledString(pathToLib.c_str(), expectAndReturnSymbol);
    std::string expectReturnAndOutputSymbol = std::string{} + "EasyMock::" + functionToMock + "::ExpectReturnAndOutput";
    mangledExpectReturnAndOutput = getMangledString(pathToLib.c_str(), expectReturnAndOutputSymbol);
  }
  else
  {
    mangledFunctionSymbol = functionToMock;
    mangledExpectAndReturn = functionToMock + "_ExpectAndReturn";
    mangledExpectReturnAndOutput = functionToMock + "_ExpectReturnAndOutput";
  }
  loadSo(pathToLib.c_str(), mangledFunctionSymbol.c_str(), mangledExpectAndReturn.c_str(), mangledExpectReturnAndOutput.c_str(), comparatorToMatch.c_str(), fptr, fptr_expect, fptr_matcher, fptr_output_ptr, handle, m_rmDir, m_load_function);
}

static void cleanTest(void **handle, const std::string &mockDir, bool rmDirectory)
{
  int error;
  dlerror(); /* Clear any existing error */

  if(*handle)
  {
    error = dlclose(*handle);
    char *errorStr = dlerror();
    ASSERT_EQ(error, 0) << "Error dlclose" << std::endl << errorStr;
    *handle = nullptr;
  }
  if(rmDirectory)
  {
    rmDir(mockDir);
  }
}

static void readStdoutStderrUntilEnd(int fdStdOut, int fdStdErr, std::string &stdOut, std::string &stdErr)
{
  fd_set rfds;
  int retval;

  bool stdOutDone = false;
  bool stdErrDone = false;
  while (stdOutDone == false || stdErrDone == false)
  {
    FD_ZERO(&rfds);
    int nfds = 0;
    if (!stdOutDone)
    {
      FD_SET(fdStdOut, &rfds);
      nfds = std::max(fdStdOut, nfds) + 1;
    }
    if (!stdErrDone)
    {
      FD_SET(fdStdErr, &rfds);
      nfds = std::max(fdStdErr, nfds) + 1;
    }
    retval = select(nfds, &rfds, nullptr, nullptr, nullptr);
    if (retval == -1)
    {
      if(!(errno == EAGAIN || errno == EINTR))
      {
        ASSERT_NE(retval, -1) << "pselect error: " << errno << ": " << strerror(errno);
      }
    }
    else if (retval == 0)
    {
      stdErrDone = true;
      stdOutDone = true;
    }
    else
    {
      if (FD_ISSET(fdStdOut, &rfds))
      {
        appendReadIntoString(fdStdOut, stdOut, "stdOut", &stdOutDone);
      }
      if (FD_ISSET(fdStdErr, &rfds))
      {
        appendReadIntoString(fdStdErr, stdErr, "stdErr", &stdErrDone);
      }
    }
  }
}

static void appendReadIntoString(int fd, std::string &str, const char *strName, bool *noMoreToRead)
{
  int rv;
  const size_t bufSize = 256;
  char buf[bufSize];
  rv = read(fd, buf, bufSize);
  ASSERT_NE(rv, -1) << "Error reading " << strName << " fd " << fd << ": " << strerror(errno);
  if (rv > 0)
  {
    str.append(buf, rv);
  }
  else if (rv == 0)
  {
    *noMoreToRead = true;
  }
}

void easyMockGenerate_baseTestCase::executeCmd(const std::vector<const char*> &aArguments, int *status)
{
  std::string ignoreStdout{};
  executeCmd(aArguments, status, ignoreStdout);
}

void easyMockGenerate_baseTestCase::executeCmd(const std::vector<const char*> &aArguments, int *status, std::string& stdOutLog)
{
  std::string stdErrLog {};
  *status = -1;
  int pipeStdOut[2];
  int pipeStdErr[2];
  pid_t cpid;
  int rv;

  stdOutLog.append("executing ");
  for (int argsIdx = 0;; argsIdx++)
  {
      if (aArguments[argsIdx] == nullptr)
      {
          break;
      }
      stdOutLog.push_back(' ');
      stdOutLog.append(aArguments[argsIdx]);
  }
  stdOutLog.append("\n");
  rv = pipe(pipeStdOut);
  ASSERT_EQ(rv, 0) << "pipe stdout error: " << strerror(errno);

  rv = pipe(pipeStdErr);
  ASSERT_EQ(rv, 0) << "pipe stdout error: " << strerror(errno);

  cpid = fork();
  ASSERT_NE(cpid, -1) << "fork error: " << strerror(errno);

  if (cpid == 0)
  {
    if (dup2(pipeStdOut[PIPE_WRITE], STDOUT_FILENO) == -1)
    {
      std::fprintf(stderr, "dup2 %d stdout failed with rv %d: %s\n\r", pipeStdOut[PIPE_WRITE], rv, strerror(errno));
      exit(1);
    }
    if (dup2(pipeStdErr[PIPE_WRITE], STDERR_FILENO) == -1)
    {
      std::fprintf(stderr, "dup2 %d stderr failed: %s\n\r", pipeStdErr[PIPE_WRITE], strerror(errno));
      exit(1);
    }
    if (close(pipeStdOut[PIPE_READ]) == -1)
    {
      std::fprintf(stderr, " close stdout failed: %s\n\r", strerror(errno));
      exit(1);
    }
    if (close(pipeStdOut[PIPE_WRITE]) == -1)
    {
      std::fprintf(stderr, " close stdout failed: %s\n\r", strerror(errno));
      exit(1);
    }
    if (close(pipeStdErr[PIPE_READ]) == -1)
    {
      std::fprintf(stderr, "close stderr failed: %s\n\r", strerror(errno));
      exit(1);
    }
    if (close(pipeStdErr[PIPE_WRITE]) == -1)
    {
      std::fprintf(stderr, "close stderr failed: %s\n\r", strerror(errno));
      exit(1);
    }

    execvp(aArguments[0], (char * const *) &aArguments[0]);
    std::fprintf(stderr, "execvp error: %s", strerror(errno));
    exit(1);
  }
  else
  {
    int wstatus;
    rv = close(pipeStdOut[PIPE_WRITE]);
    ASSERT_EQ(rv, 0) << "close stdout write failed: %s" << strerror(errno);
    rv = close(pipeStdErr[PIPE_WRITE]);
    ASSERT_EQ(rv, 0) << "close stderr write failed: %s" << strerror(errno);

    readStdoutStderrUntilEnd(pipeStdOut[PIPE_READ], pipeStdErr[PIPE_READ], stdOutLog, stdErrLog);
    rv = close(pipeStdOut[PIPE_READ]);
    ASSERT_EQ(rv, 0) << "close stdout read failed: %s" << strerror(errno);
    rv = close(pipeStdErr[PIPE_READ]);
    ASSERT_EQ(rv, 0) << "close stdout read failed: %s" << strerror(errno);
    do
    {
      pid_t w = waitpid(cpid, &wstatus, WUNTRACED | WCONTINUED);
      if(w == -1)
      {
        if(!(errno == EINTR || errno == EAGAIN))
        {
          ASSERT_NE(w, -1) << "Waitpid failed: " << strerror(errno);
        }
      }
      else
      {
        if (WIFEXITED(wstatus))
        {
          //printf("exited, status=%d\n", WEXITSTATUS(wstatus));
        }
        else if (WIFSIGNALED(wstatus))
        {
          //printf("killed by signal %d\n", WTERMSIG(wstatus));
        }
        else if (WIFSTOPPED(wstatus))
        {
          //printf("stopped by signal %d\n", WSTOPSIG(wstatus));
        }
        else if (WIFCONTINUED(wstatus))
        {
          //printf("continued\n");
        }
      }
    }
    while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
    *status = WEXITSTATUS(wstatus);
    if(*status != 0)
    {
      fprintf(stdout, "stdout:\n%s\n\nstderr:\n%s\n", stdOutLog.c_str(), stdErrLog.c_str());
     /*
      * When the UT fails, do not delete the folder of the generated code
      */
      m_rmDir = false;
    }
    dumpToFile(m_finalMockDir, "stdout.txt", stdOutLog, true);
    dumpToFile(m_finalMockDir, "stderr.txt", stdErrLog, true);
  }
}

static void loadSo(const char *pathToSo, const char *functionToLoadSymbol, const char *functionExpectAndReturnSymbol, const char* functionExpectReturnAndOutputSymbol, const char *comparatorToMatch, void **funcPtr, void **funcPtr_expect, void **funcPtr_matcher, void **funcPtr_output_ptr, void **handle, bool& m_rmDir, bool& m_load_function)
{
  char *error;
  ASSERT_TRUE(functionToLoadSymbol);
  ASSERT_TRUE(functionExpectAndReturnSymbol);
  ASSERT_TRUE(functionExpectReturnAndOutputSymbol);

  dlerror(); /* Clear any existing error */
  *handle = dlopen(pathToSo, RTLD_NOW | RTLD_LOCAL);
  error = dlerror();
  if(*handle == nullptr)
  {
    m_rmDir = false;
  }
  ASSERT_NE(*handle, nullptr) << "couldn't open shared library " << pathToSo << ": " << error;

  if(m_load_function)
  {
    dlerror(); /* Clear any existing error */

    *funcPtr = dlsym(*handle, functionToLoadSymbol);
    error = dlerror();
    ASSERT_EQ(error, nullptr) << "couldn't load function '" << functionToLoadSymbol << "': " << error;

    dlerror(); /* Clear any existing error */

    *funcPtr_expect = dlsym(*handle, functionExpectAndReturnSymbol);
    error = dlerror();
    ASSERT_EQ(error, nullptr) << "couldn't load expect function '" << functionToLoadSymbol << "': " << error;

    std::string matchStr(comparatorToMatch);
    *funcPtr_matcher = dlsym(*handle, matchStr.c_str());

    *funcPtr_output_ptr = dlsym(*handle, functionExpectReturnAndOutputSymbol);
  }
}

static void dumpToFile(const std::string& p_dir, const std::string& p_file, std::string& p_data, bool append)
{
  std::string fileName { p_dir };
  fileName.push_back('/');
  fileName.append(p_file);
  std::ofstream ofile;
  ofile.open(fileName, append ? std::ios::app : std::ios::trunc);
  ofile << p_data;
  ofile.close();
}

std::string easyMockGenerate_baseTestCase::getStartLineToMatchForSymbolInSo(const char *pathToSo, const std::string& functionToMock)
{
  std::vector<const char *> nmDemangled
      {
          "nm",
          "-g",
          "-C",
          pathToSo,
          nullptr
      };
  int status;
  std::string nmDemangledOut;
  executeCmd(nmDemangled, &status, nmDemangledOut);

  std::string sToFind {functionToMock};
  sToFind.push_back('(');

  std::string symbolAddr;
  std::istringstream nmDemangledOutIs{nmDemangledOut};
  std::string curLine{};
  while (std::getline(nmDemangledOutIs, curLine))
  {
    std::string::size_type sToFindPos;
    if((sToFindPos = curLine.find(sToFind)) != std::string::npos)
    {
      symbolAddr = curLine.substr(0, sToFindPos);
    }
  }
  return symbolAddr;
}

std::string easyMockGenerate_baseTestCase::getMangleFunName(const char *pathToSo, const std::string& startLineToMatch)
{
  std::vector<const char *> nmDemangled =
      {
          "nm",
          "-g",
          pathToSo,
          nullptr
      };
  int status;
  std::string nmMangledOut;
  executeCmd(nmDemangled, &status, nmMangledOut);

  std::string symbolAddr;
  std::istringstream nmMangledOutIs{nmMangledOut};
  std::string curLine{};
  while (std::getline(nmMangledOutIs, curLine))
  {
    std::string::size_type sToFindPos;
    if((sToFindPos = curLine.find(startLineToMatch)) != std::string::npos)
    {
      std::string::size_type startLineToMatchLen = startLineToMatch.length();
      symbolAddr = curLine.substr(startLineToMatchLen, curLine.length() - startLineToMatchLen);
    }
  }
  return symbolAddr;
}

std::string easyMockGenerate_baseTestCase::getMangledString(const char *pathToSo, const std::string& functionToMock)
{
  std::string symbolAddr = getStartLineToMatchForSymbolInSo(pathToSo, functionToMock);
  std::string mangledString = getMangleFunName(pathToSo, symbolAddr);
#if defined (__APPLE__)
  /*
   * Somehow "nm -C" on MacOS returns __mangledString iso _mangledString
   * but dlsym wants _mangleString ¯\_(ツ)_/¯
   */
  mangledString.erase(0, 1);
#endif
  return mangledString;
}
