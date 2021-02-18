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

static void readStdoutStderrUntilEnd(int fdStdOut, int fdStdErr, std::string *stdOut, std::string *stdErr);
static void appendReadIntoString(int fd, std::string *str, const char *strName, bool *noMoreToRead);
static void loadSo(const char *pathToSo, const char *functionToLoad, const char *comparatorToMatch, void **funcPtr, void **functExpectPtr, void **functMatcherPtr, void **functOutputPtr, void **handle, bool & m_rmDir);
static void executeCmd(const char * const aArguments[], std::string *stdOut, std::string *stdErr, int *status);
static void cleanTest(void **handle, const std::string &mockDir, bool rmDirectory);
static void dumpToFile(const std::string& dir, const std::string& file, const std::string& data);

easyMockGenerate_baseTestCase::easyMockGenerate_baseTestCase(const std::string functionToMock, const std::string pathToFileToMock, const std::string mockDir, bool generateTypes, bool rmDir) :
::testing::Test(),
m_functionToMock(functionToMock),
m_comparatorToMatch(""),
m_pathToFileToMock(pathToFileToMock),
m_mockDir(mockDir),
m_rmDir(rmDir),
handle(NULL),
m_fptr(NULL),
m_fptr_expect(NULL),
m_fptr_matcher(NULL),
m_fptr_output_ptr(NULL),
m_generate_types(generateTypes)
{
  ComposableType::setFileHash(std::hash<std::string>{}(pathToFileToMock));
}

void easyMockGenerate_baseTestCase::setComparatorToMatch(const std::string comparatorToMatch)
{
  m_comparatorToMatch = comparatorToMatch;
}

std::stringstream &operator<<(std::stringstream &out, const EasyMock_ErrorArrayPrinter &obj)
{
  const char **curArrChar = obj.m_in;
  const char *curChar;
  for(curChar = *curArrChar; curChar != NULL; curArrChar++, curChar = *curArrChar)
  {
    out << curChar << std::endl;
  }
  return out;
}

bool isFifoCallEmpty()
{
  return easyMock.m_fifoCall.empty();
}

std::string getCurrentFifoCall()
{
  return easyMock.m_fifoCall.front();
}

int fifoCallSize()
{
  return easyMock.m_fifoCall.size();
}

void easyMockGenerate_baseTestCase::SetUp()
{
  prepareTest(m_ctxt, m_functionToMock, m_comparatorToMatch, m_pathToFileToMock, m_mockDir, (void **) &m_fptr, (void **) &m_fptr_expect, (void **) &m_fptr_matcher, (void **)&m_fptr_output_ptr, &handle);

  easyMock_init();

  ExtraSetup();
}

void easyMockGenerate_baseTestCase::TearDown()
{
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

void easyMockGenerate_baseTestCase::setGenerateTypes(bool p_generateTypes)
{
  m_generate_types = p_generateTypes;
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

void easyMockGenerate_baseTestCase::prepareTest(const ElementToMockContext &elem, const std::string &functionToMock, std::string &comparatorToMatch, const std::string &fullPathToFileToMock, const std::string &mockDir, void **fptr, void **fptr_expect, void **fptr_matcher, void **fptr_output_ptr, void **handle)
{
  char cwd[PATH_MAX];
  ASSERT_NE(getcwd(cwd, PATH_MAX), nullptr) << std::endl << "getcwd error. errno: " << errno << "(" << strerror(errno) << ")" << std::endl;
  CodeGeneratorCTemplate generate;
  generate.setGenerateUsedType(m_generate_types);

  std::string pathAndfileNameToMock = boost::filesystem::path(fullPathToFileToMock).stem().string();
  std::string fileNameToMock = boost::filesystem::path(pathAndfileNameToMock).filename().string();
  std::string finalMockDir(mockDir);
  if(m_generate_types)
  {
    finalMockDir.append("/typeGenerate");
  }
  else
  {
    finalMockDir.append("/useHeader");
  }
  createDir(finalMockDir);
  bool codeGen = generate.generateCode(finalMockDir, fullPathToFileToMock, elem);
  ASSERT_TRUE(codeGen) << std::endl << "Generation failed." << std::endl << "cwd: " << cwd << std::endl;
  std::string stdOut;
  std::string stdErr;
  int status;

  std::string objFile(finalMockDir);
  objFile.append("/easyMock_");
  objFile.append(pathAndfileNameToMock);
  std::string fileToCompile(objFile);
  objFile.append(".o");
  fileToCompile.append(".c");
#if defined(__clang__)
  const char *cCompiler = "clang";
  const char *cppCompiler = "clang++";
#elif defined(__GNUC__) || defined(__GNUG__)
  const char *cCompiler = "gcc";
  const char *cppCompiler = "g++";
#else
#error "Compiler not supported"
#endif
  const char * const compileMockCmd[] = {cCompiler, "-Wall", "-Werror", "-g", "-O0", "-fpic", "-I", finalMockDir.c_str(), "-I", PROJECT_ROOT_DIR"/src/easyMockFramework/include", "-I", PROJECT_ROOT_DIR"/test/easyMockGenerate/include", "-o", objFile.c_str(), "-c", fileToCompile.c_str(), NULL};
  executeCmd(compileMockCmd, &stdOut, &stdErr, &status);
  if(status != 0)
  {
    /*
     * When the UT fails, do not delete the folder of the generated code
     */
    m_rmDir = false;
    dumpToFile(finalMockDir, "stdout.txt", stdOut);
    dumpToFile(finalMockDir, "stderr.txt", stdErr);
  }
  ASSERT_EQ(status, 0) << std::endl << "Compilation mock failed " << std::endl << "cwd: " << cwd << std::endl << "stdout: " << std::endl << stdOut << std::endl << "stderr:" << std::endl << stdErr << std::endl;

  std::string pathToLib(mockDir);
  pathToLib.append("/lib");
  pathToLib.append(fileNameToMock);
  pathToLib.append(".so");
  const char * const compileLibCmd[] =
  {
    cppCompiler,
    "-shared",
#if defined(__clang__)
    "-undefined", "dynamic_lookup",
#endif
    "-o",
    pathToLib.c_str(),
    objFile.c_str(),
    NULL
  };
  executeCmd(compileLibCmd, &stdOut, &stdErr, &status);
  if(status != 0)
  {
    /*
     * When the UT fails, do not delete the folder of the generated code
     */
    m_rmDir = false;
  }
  ASSERT_EQ(status, 0) << std::endl << "Compilation lib failed " << std::endl << "cwd: " << cwd << std::endl << "stdout: " << std::endl << stdOut << std::endl << "stderr:" << std::endl << stdErr << std::endl;

  loadSo(pathToLib.c_str(), functionToMock.c_str(), comparatorToMatch.c_str(), fptr, fptr_expect, fptr_matcher, fptr_output_ptr, handle, m_rmDir);
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
    *handle = NULL;
  }
  if(rmDirectory)
  {
    rmDir(mockDir);
  }
}

static void readStdoutStderrUntilEnd(int fdStdOut, int fdStdErr, std::string *stdOut, std::string *stdErr)
{
  fd_set rfds;
  int retval;

  bool stdOutDone = false;
  bool stdErrDone = false;
  stdOut->clear();
  stdErr->clear();
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
    retval = select(nfds, &rfds, NULL, NULL, NULL);
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

static void appendReadIntoString(int fd, std::string *str, const char *strName, bool *noMoreToRead)
{
  int rv;
  const size_t bufSize = 256;
  char buf[bufSize];
  rv = read(fd, buf, bufSize);
  ASSERT_NE(rv, -1) << "Error reading " << strName << " fd " << fd << ": " << strerror(errno);
  if (rv > 0)
  {
    str->append(buf, rv);
  }
  else if (rv == 0)
  {
    *noMoreToRead = true;
  }
}

static void executeCmd(const char * const aArguments[], std::string *stdOut, std::string *stdErr, int *status)
{
  *status = -1;
  int pipeStdOut[2];
  int pipeStdErr[2];
  pid_t cpid;
  int rv;
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

    std::fprintf(stdout, "executing ");
    for (int argsIdx = 0;; argsIdx++)
    {
      if (aArguments[argsIdx] == NULL)
      {
        break;
      }
      fprintf(stdout, "%s ", aArguments[argsIdx]);
    }
    std::fprintf(stdout, "\n");
    execvp(aArguments[0], (char * const *) aArguments);
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

    readStdoutStderrUntilEnd(pipeStdOut[PIPE_READ], pipeStdErr[PIPE_READ], stdOut, stdErr);
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
  }
}

static void loadSo(const char *pathToSo, const char *functionToLoad, const char *comparatorToMatch, void **funcPtr, void **funcPtr_expect, void **funcPtr_matcher, void **funcPtr_output_ptr, void **handle, bool& m_rmDir)
{
  char *error;

  dlerror(); /* Clear any existing error */
  *handle = dlopen(pathToSo, RTLD_NOW | RTLD_LOCAL);
  error = dlerror();
  if(*handle == nullptr)
  {
    m_rmDir = false;
  }
  ASSERT_NE(*handle, nullptr) << "couldn't open shared library " << pathToSo << ": " << error;

  dlerror(); /* Clear any existing error */

  *funcPtr = dlsym(*handle, functionToLoad);
  error = dlerror();
  ASSERT_EQ(error, nullptr) << "couldn't load function " << functionToLoad << ": " << error;

  std::string expectStr(functionToLoad);
  expectStr.append("_ExpectAndReturn");

  dlerror(); /* Clear any existing error */

  *funcPtr_expect = dlsym(*handle, expectStr.c_str());
  error = dlerror();
  ASSERT_EQ(error, nullptr) << "couldn't load expect function " << functionToLoad << ": " << error;

  std::string matchStr(comparatorToMatch);
  *funcPtr_matcher = dlsym(*handle, matchStr.c_str());

  std::string funPtrOutPtr(functionToLoad);
  funPtrOutPtr.append("_ExpectReturnAndOutput");
  *funcPtr_output_ptr = dlsym(*handle, funPtrOutPtr.c_str());
}

static void dumpToFile(const std::string& p_dir, const std::string& p_file, const std::string& p_data)
{
  std::string fileName { p_dir };
  fileName.push_back('/');
  fileName.append(p_file);
  std::ofstream ofile;
  ofile.open(fileName, std::ios::trunc);
  ofile << p_data;
  ofile.close();
}
