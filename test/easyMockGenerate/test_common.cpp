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

#include <easyMock.h>
#include <CodeGeneratorCTemplate.h>

#include <easyMock.cpp> //To access easyMock static object

#define PIPE_READ 0
#define PIPE_WRITE 1

static void readStdoutStderrUntilEnd(int fdStdOut, int fdStdErr, std::string *stdOut, std::string *stdErr);
static void appendReadIntoString(int fd, std::string *str, const char *strName, bool *noMoreToRead);
static void loadSo(const char *pathToSo, const char *functionToLoad, void **funcPtr, void **functExpectPtr, void **handle);
static void executeCmd(const char * const aArguments[], std::string *stdOut, std::string *stdErr, int *status);
static void prepareTest(const ElementToMockVector &elem, const std::string &functionToMock, const std::string &fullPathToFileToMock, const std::string &mockDir, void **funcPtr, void **functExpectPtr, void **handle);
static void cleanTest(void **handle, const std::string &mockDir, bool rmDirectory);

easyMockGenerate_baseTestCase::easyMockGenerate_baseTestCase(const std::string functionToMock, const std::string pathToFileToMock, const std::string mockDir, bool rmDir) :
::testing::Test(),
m_functionToMock(functionToMock),
m_pathToFileToMock(pathToFileToMock),
m_mockDir(mockDir),
m_rmDir(rmDir)
{
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
  prepareTest(m_elem, m_functionToMock, m_pathToFileToMock, m_mockDir, (void **) &m_fptr, (void **) &m_fptr_expect, &handle);

  easyMock_init();
}

void easyMockGenerate_baseTestCase::TearDown()
{
  cleanTest(&handle, m_mockDir, m_rmDir);
}

void easyMockGenerate_baseTestCase::getFunPtr(void** fPtr, void** fExpectPtr)
{
  *fPtr = m_fptr;
  *fExpectPtr = m_fptr_expect;
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

static void prepareTest(const ElementToMockVector &elem, const std::string &functionToMock, const std::string &fullPathToFileToMock, const std::string &mockDir, void **fptr, void **fptr_expect, void **handle)
{
  char cwd[PATH_MAX];
  ASSERT_NE(getcwd(cwd, PATH_MAX), nullptr) << std::endl << "getcwd error. errno: " << errno << "(" << strerror(errno) << ")" << std::endl;
  CodeGeneratorCTemplate generate;

  std::string pathAndfileNameToMock = boost::filesystem::path(fullPathToFileToMock).stem().string();
  std::string fileNameToMock = boost::filesystem::path(pathAndfileNameToMock).filename().string();
  createDir(mockDir);
  bool codeGen = generate.generateCode(mockDir, fullPathToFileToMock, elem);
  ASSERT_TRUE(codeGen) << std::endl << "Generation failed." << std::endl << "cwd: " << cwd << std::endl;
  std::string stdOut;
  std::string stdErr;
  int status;

  std::string objFile(mockDir);
  objFile.append("/easyMock_");
  objFile.append(pathAndfileNameToMock);
  std::string fileToCompile(objFile);
  objFile.append(".o");
  fileToCompile.append(".cpp");
  const char * const compileMockCmd[] = {"g++", "-Wall", "-Werror", "-g", "-fpic", "-I", mockDir.c_str(), "-I", PROJECT_ROOT_DIR"/src/easyMockFramework/include", "-I", PROJECT_ROOT_DIR"/test/easyMockGenerate/include", "-o", objFile.c_str(), "-c", fileToCompile.c_str(), NULL};
  executeCmd(compileMockCmd, &stdOut, &stdErr, &status);
  ASSERT_EQ(status, 0) << std::endl << "Compilation mock failed " << std::endl << "cwd: " << cwd << std::endl << "stdout: " << std::endl << stdOut << std::endl << "stderr:" << std::endl << stdErr << std::endl;

  std::string pathToLib(mockDir);
  pathToLib.append("/lib");
  pathToLib.append(fileNameToMock);
  pathToLib.append(".so");
  const char * const compileLibCmd[] = {"g++", "-shared", "-o", pathToLib.c_str(), objFile.c_str(), NULL};
  executeCmd(compileLibCmd, &stdOut, &stdErr, &status);
  ASSERT_EQ(status, 0) << std::endl << "Compilation lib failed " << std::endl << "cwd: " << cwd << std::endl << "stdout: " << std::endl << stdOut << std::endl << "stderr:" << std::endl << stdErr << std::endl;

  loadSo(pathToLib.c_str(), functionToMock.c_str(), fptr, fptr_expect, handle);
}

static void cleanTest(void **handle, const std::string &mockDir, bool rmDirectory)
{
  int error;
  dlerror(); /* Clear any existing error */

  error = dlclose(*handle);
  char *errorStr = dlerror();
  ASSERT_EQ(error, 0) << "Error dlclose" << std::endl << errorStr;
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
    ASSERT_NE(retval, -1) << "pselect error %s" << strerror(errno);
    if (retval == 0)
    {
      stdErrDone = true;
      stdOutDone = true;
    }
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
      ASSERT_NE(w, -1) << "Waitpid failed: " << strerror(errno);

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
    while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
    *status = WEXITSTATUS(wstatus);
  }
}

static void loadSo(const char *pathToSo, const char *functionToLoad, void **funcPtr, void **funcPtr_expect, void **handle)
{
  char *error;

  dlerror(); /* Clear any existing error */
  *handle = dlopen(pathToSo, RTLD_NOW | RTLD_LOCAL);
  error = dlerror();
  ASSERT_NE(*handle, nullptr) << "couldn't open shared library " << pathToSo << ": " << error;

  dlerror(); /* Clear any existing error */

  *funcPtr = dlsym(*handle, functionToLoad);
  error = dlerror();
  ASSERT_EQ(error, nullptr) << "couldn't load function " << functionToLoad << ": " << error;

  std::string expectStr(functionToLoad);
  expectStr.append("_ExpectAndReturn");

  *funcPtr_expect = dlsym(*handle, expectStr.c_str());
  error = dlerror();
  ASSERT_EQ(error, nullptr) << "couldn't load expect function " << functionToLoad << ": " << error;
}
