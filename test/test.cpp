#include <gtest/gtest.h> // googletest header file
#include <errno.h>
#include <stdlib.h>
#include <sys/select.h>
#include <dlfcn.h>
#include <easyMock.h>

#define PIPE_READ 0
#define PIPE_WRITE 1

#include "CodeGeneratorCTemplate.h"
#include <test/stub_header.h>

#include <string>

static void createDir(const char *dir);
static void executeCmd(const char * const aArguments[], std::string *stdOut, std::string *stdErr, int *status);
static void readStdoutStderrUntilEnd(int fdStdOut, int fdStdErr, std::string *stdOut, std::string *stdErr);
static void appendReadIntoString(int fd, std::string *str, const char *strName, bool *noMoreToRead);
static void loadSo(const char *pathToSo, const char *functionToLoad, void **funcPtr, void **functExpectPtr, void **handle);

TEST(GenerateStub, voidFunction_void)
{
  CodeGeneratorCTemplate generate;
  ElementToStubVector elem;
  Function *f = new Function("function", "void",{});
  elem.push_back(f);

  createDir("test");
  generate.generateCode("test", "header.h", elem);
  std::string stdOut;
  std::string stdErr;
  int status;
  const char * const compileStubCmd[] = {"g++", "-Wall", "-Werror", "-g", "-fpic", "-I", "test", "-I", PROJECT_ROOT_DIR"/src/easyMockFramework/include", "-o", "test/stub_header.o", "-c", "test/stub_header.cpp", NULL};
  executeCmd(compileStubCmd, &stdOut, &stdErr, &status);
  ASSERT_EQ(status, 0) << std::endl << "Compilation stub failed " << std::endl << "stdout: " << std::endl << stdOut << std::endl << "stderr:" << std::endl << stdErr << std::endl;

  /*const char * const compileEasyMock[] = {"g++", "-Wall", "-Werror", "-g", "-fpic", "-I", "test", "-I", PROJECT_ROOT_DIR"/src/easyMockFramework/include", "-o", "test/easyMock.o", "-c", PROJECT_ROOT_DIR"/src/easyMockFramework/src/easyMock.cpp", NULL};
  executeCmd(compileEasyMock, &stdOut, &stdErr, &status);
  ASSERT_EQ(status, 0) << std::endl << "Compilation stub failed " << std::endl << "stdout: " << std::endl << stdOut << std::endl << "stderr:" << std::endl << stdErr << std::endl;*/

  const char * const compileLibCmd[] = {"g++", "-shared", "-o", "test/libtest.so", "test/stub_header.o", "test/easyMock.o", NULL};
  executeCmd(compileLibCmd, &stdOut, &stdErr, &status);
  ASSERT_EQ(status, 0) << std::endl << "Compilation lib failed " << std::endl << "stdout: " << std::endl << stdOut << std::endl << "stderr:" << std::endl << stdErr << std::endl;

  void *handle;
  void (*fptr)();
  void (*fptr_expect)();
  loadSo("test/libtest.so", "function", (void **) &fptr, (void **)&fptr_expect, &handle);
  fptr_expect();
  fptr();
  int check = easyMock_check();
  EXPECT_EQ(check, 1);

  const char *error = easyMock_getErrorStr();
  ASSERT_NE(error, nullptr);
  printf("%s", error);

  //Close handle after check because easyMock_check and easyMock_getErrorStr uses some function of the .so
  dlclose(handle);

}

static void createDir(const char *dir)
{
  std::string stdOut;
  std::string stdErr;
  int status;
  const char * const cmdMkDir[] = {"mkdir", "-p", dir, NULL};
  executeCmd(cmdMkDir, &stdOut, &stdErr, &status);
  ASSERT_EQ(status, 0) << "Couldn't create directory" << dir << std::endl
          << "stdout: " << std::endl
          << stdOut << std::endl
          << stdErr;
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
    ASSERT_EQ(rv, 0) << "close stdout failed: %s" << strerror(errno);
    rv = close(pipeStdErr[PIPE_WRITE]);
    ASSERT_EQ(rv, 0) << "close stderr failed: %s" << strerror(errno);

    readStdoutStderrUntilEnd(pipeStdOut[PIPE_READ], pipeStdErr[PIPE_READ], stdOut, stdErr);
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

static void loadSo(const char *pathToSo, const char *functionToLoad, void **funcPtr, void **funcPtr_expect, void **handle)
{
  char *error;

  *handle = dlopen(pathToSo, RTLD_NOW | RTLD_LOCAL);
  ASSERT_NE(*handle, nullptr) << "couldn't open shared library " << pathToSo << ": " << strerror(errno);

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