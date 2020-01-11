#include <easyMock.h>
#include <easyMock_framework.h>
#include <MockedFunction.h>

#include <cstdio>
#include <string>
#include <map>
#include <queue>
#include <vector>
#include <bits/stl_queue.h>
#include <stdarg.h>
#define UNW_LOCAL_ONLY
#include <libunwind.h>
#include <cxxabi.h>
#include <elfutils/libdwfl.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h>
#include <boost/core/demangle.hpp>

static void append_string(std::string &str, const char *fmt, ...);

typedef std::map<const easyMock_mockedFileRegister_t *, const easyMock_mockedFileRegister_t *> MockMap_t;
typedef std::queue<std::string> FifoCall_t;
typedef std::vector<std::string> FifoError_t;

static std::string allErrorStr;
static std::vector<const char*> cError;

class EasyMock
{
public:

  EasyMock() :
  m_checkFifoCall(false), m_printCallStack(true) { };

  void registerMock(const easyMock_mockedFileRegister_t *args)
  {
    m_registeredMock[args] = args;
  }

  void unregisterMock(const easyMock_mockedFileRegister_t *args)
  {
    m_registeredMock.erase(args);
  }

  void init()
  {
    initRegisteredMockedFile();
    emptyFifoCall();
    emptyError();
  }

  int verifyEasyMock()
  {
    int rv = 1;
    if (!verifyRegisteredMockedFile())
    {
      rv = 0;
    }
    if (!m_error.empty())
    {
      rv = 0;
    }
    return rv;
  }

  void addError(std::string error, bool callstack)
  {
    if (callstack)
    {
      error.append("\n\r");
      append_backtrace(error);
    }
    m_error.push_back(error);
  }

  const char *getErrorStr()
  {
    allErrorStr.clear();
    FifoError_t::iterator it;
    for(it = m_error.begin(); it != m_error.end(); it++)
    {
      std::string &curErr = *it;
      allErrorStr.append(curErr);
      allErrorStr.append("\n\r");
    }
    if (allErrorStr.size() == 0)
    {
      return NULL;
    }
    else
    {
      return allErrorStr.c_str();
    }
  }

  const char **getErrorArr(unsigned int *size)
  {
    cError.clear();
    std::transform(begin(m_error), end(m_error),
                   std::back_inserter(cError),
                   [](std::string &s) { return s.c_str(); }
                  );
    *size = cError.size();
    if(*size > 0)
    {
      cError.push_back(NULL);
      return &cError[0];
    }
    else
    {
      return NULL;
    }
  }

  void addCall(const std::string name)
  {
    m_fifoCall.push(name);
  }

  const std::string popCurrentCall()
  {
    if (m_fifoCall.empty())
    {
      addError("BUG IN EASYMOCK. No more current call", false);
      return "NoMoreCall";
    }
    const std::string currentCall = m_fifoCall.front();
    m_fifoCall.pop();
    return currentCall;
  }

  bool checkFifoCall()
  {
    return m_checkFifoCall;
  }

  bool printCallStack()
  {
    return m_printCallStack;
  }

  void setPrintCallStack(bool val)
  {
    m_printCallStack = val;
  }

  void setCheckFifoCall(bool val)
  {
    m_checkFifoCall = val;
  }
private:

  void initRegisteredMockedFile()
  {
    for (MockMap_t::const_iterator it = m_registeredMock.begin(); it != m_registeredMock.end(); ++it)
    {
      const easyMock_mockedFileRegister_t *f = it->second;
      f->resetMockedFile();
    }
  }

  bool verifyRegisteredMockedFile()
  {
    bool rv = true;
    for (MockMap_t::const_iterator it = m_registeredMock.begin(); it != m_registeredMock.end(); ++it)
    {
      const easyMock_mockedFileRegister_t *f = it->second;
      if (!f->verifyMockedFile())
      {
        rv = 0;
      }
    }
    return rv;
  }

  void emptyFifoCall()
  {
    while (!m_fifoCall.empty())
    {
      m_fifoCall.pop();
    }
  }

  void emptyError()
  {
    m_error.clear();
  }

  /*
   * Thanks to https://gist.github.com/banthar/1343977
   * for stack trace print
   */
  void debugInfo(std::string &error, const void* ip)
  {

    char *debuginfo_path = NULL;

    Dwfl_Callbacks callbacks = {};
    callbacks.find_elf = dwfl_linux_proc_find_elf;
    callbacks.find_debuginfo = dwfl_standard_find_debuginfo;
    callbacks.debuginfo_path = &debuginfo_path;

    Dwfl* dwfl = dwfl_begin(&callbacks);

    assert(dwfl_linux_proc_report(dwfl, getpid()) == 0);
    assert(dwfl_report_end(dwfl, NULL, NULL) == 0);

    Dwarf_Addr addr = (uintptr_t) ip;

    Dwfl_Module* module = dwfl_addrmodule(dwfl, addr);

    const char* function_name = dwfl_module_addrname(module, addr);

    append_string(error, "%s(", boost::core::demangle(function_name).c_str());

    Dwfl_Line *line = dwfl_getsrc(dwfl, addr);
    if (line != NULL)
    {
      int nline;
      Dwarf_Addr addr;
      const char* filename = dwfl_lineinfo(line, &addr, &nline, NULL, NULL, NULL);
      append_string(error, "%s:%d", strrchr(filename, '/') + 1, nline);
    }
    else
    {
      const char *module_name = dwfl_module_info(module,
              NULL, NULL, NULL, NULL, NULL, NULL, NULL);
      append_string(error, "in %s", module_name);
    }
    dwfl_end(dwfl);
  }

  void append_backtrace(std::string &error)
  {
    int skip = 0;
    unw_context_t uc;
    unw_getcontext(&uc);

    unw_cursor_t cursor;
    unw_init_local(&cursor, &uc);

    while (unw_step(&cursor) > 0)
    {

      unw_word_t ip;
      unw_get_reg(&cursor, UNW_REG_IP, &ip);

      //unw_word_t offset;
      char name[32];
      //assert(unw_get_proc_name(&cursor, name,sizeof(name), &offset)==0);

      if (skip <= 0)
      {
        append_string(error, "\tat ");
        debugInfo(error, (void*) (ip - 4));
        append_string(error, ")\n");
      }

      if (strcmp(name, "main") == 0)
        break;

      skip--;

    }
  }

  bool m_checkFifoCall;
  bool m_printCallStack;
  MockMap_t m_registeredMock;
  FifoCall_t m_fifoCall;
  FifoError_t m_error;
};

static EasyMock __attribute ((init_priority(101))) easyMock;

void easyMock_registerMock(const easyMock_mockedFileRegister_t *args)
{
  easyMock.registerMock(args);
}

void easyMock_unregisterMock(const easyMock_mockedFileRegister_t *args)
{
  easyMock.unregisterMock(args);
}

std::string easyMock_popCurrentCall()
{
  return easyMock.popCurrentCall();
}

void easyMock_addCall(const std::string call)
{
  easyMock.addCall(call);
}

void easyMock_addError(bool callstack, const char *fmt, ...)
{
  //https://en.cppreference.com/w/cpp/io/c/vfprintf
  va_list args1;
  va_start(args1, fmt);
  va_list args2;
  va_copy(args2, args1);
  std::vector<char> buf(1 + std::vsnprintf(nullptr, 0, fmt, args1));
  va_end(args1);
  std::vsnprintf(buf.data(), buf.size(), fmt, args2);
  va_end(args2);
  std::string error(buf.begin(), buf.end() - 1); //-1 to remove the \0 added by vsnprintf. The std::string takes care to terminate the string correctly

  easyMock.addError(error, callstack);
}

bool easyMock_checkFifoCall()
{
  return easyMock.checkFifoCall();
}

bool easyMock_printCallStack()
{
  return easyMock.printCallStack();
}

extern "C" void easyMock_init()
{
  easyMock.init();
}

extern "C" int easyMock_check()
{
  return easyMock.verifyEasyMock();
}

extern "C" const char *easyMock_getErrorStr()
{
  return easyMock.getErrorStr();
}

extern "C" const char **easyMock_getErrorArr(unsigned int *size)
{
  return easyMock.getErrorArr(size);
}

extern "C" void easyMock_printCallStack(bool val)
{
  easyMock.setPrintCallStack(val);
}

extern "C" void easyMock_checkFifoCall(bool val)
{
  easyMock.setCheckFifoCall(val);
}

static void append_string(std::string &str, const char *fmt, ...)
{
  //https://en.cppreference.com/w/cpp/io/c/vfprintf
  va_list args1;
  va_start(args1, fmt);
  va_list args2;
  va_copy(args2, args1);
  std::vector<char> buf(1 + std::vsnprintf(nullptr, 0, fmt, args1));
  va_end(args1);
  std::vsnprintf(buf.data(), buf.size(), fmt, args2);
  va_end(args2);
  std::string strToCopy(buf.begin(), buf.end() - 1); //-1 to remove the \0 added by vsnprintf. The std::string takes to terminate the string correctly
  str.append(strToCopy);
}
