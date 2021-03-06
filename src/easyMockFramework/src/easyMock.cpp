#include <easyMock.h>
#include <easyMock_framework.h>
#include <MockedFunction.h>

#include <algorithm>
#include <cstdio>
#include <string>
#include <map>
#include <queue>
#include <vector>
#include <cstdarg>

#include <cstring>
#include <sys/types.h>
#include <unistd.h>
#include <boost/core/demangle.hpp>
#include <cstdbool>

#undef NDEBUG
#include <cassert>

#ifdef BACKTRACE_SUPPORT
#define UNW_LOCAL_ONLY
#include <libunwind.h>
#include <cxxabi.h>
#include <elfutils/libdwfl.h>
#endif

#ifdef BACKTRACE_SUPPORT
static void append_string(std::string &str, const char *fmt, ...);
#endif
typedef std::map<const easyMock_mockedFileRegister_t *, const easyMock_mockedFileRegister_t *> MockMap_t;
typedef std::queue<std::string> FifoCall_t;
typedef std::vector<std::string> FifoError_t;

static std::string allErrorStr;
static std::vector<const char*> cError;

namespace EasyMock
{

class EasyMock
{
public:

  EasyMock() :
  m_checkCallsOrder(false), m_printCallStack(true)
  {
  }

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
    if (allErrorStr.empty())
    {
      return nullptr;
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
      cError.push_back(nullptr);
      return &cError[0];
    }
    else
    {
      return nullptr;
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

  bool checkCallsOrder()
  {
    return m_checkCallsOrder;
  }

  bool printCallStack()
  {
#if defined(BACKTRACE_SUPPORT)
    return m_printCallStack;
#else
    return false;
#endif
  }

  void setPrintCallStack(bool val)
  {
    m_printCallStack = val;
  }

  void setCheckCallsOrder(bool val)
  {
    m_checkCallsOrder = val;
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
#ifdef BACKTRACE_SUPPORT
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
#endif
  }

  void append_backtrace(std::string &error)
  {
#ifdef BACKTRACE_SUPPORT
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
      //char name[32];
      //assert(unw_get_proc_name(&cursor, name,sizeof(name), &offset)==0);

      if (skip <= 0)
      {
        append_string(error, "\tat ");
        debugInfo(error, (void*) (ip - 4));
        append_string(error, ")\n");
      }

      /*if (strcmp(name, "main") == 0)
        break;*/

      skip--;

    }
#endif
  }

  bool m_checkCallsOrder;
  bool m_printCallStack;
  MockMap_t m_registeredMock;
  FifoCall_t m_fifoCall;
  FifoError_t m_error;
};

}

static EasyMock::EasyMock __attribute__ ((init_priority(101))) easyMock;

extern "C" void easyMock_registerMockedFile(const easyMock_mockedFileRegister_t *args)
{
  easyMock.registerMock(args);
}

extern "C" void easyMock_unregisterMockedFile(const easyMock_mockedFileRegister_t *args)
{
  easyMock.unregisterMock(args);
}

extern "C" cstring easyMock_popCurrentCall()
{
  std::string poppedCalled = easyMock.popCurrentCall();
  cstring rv = cstring_new_init(poppedCalled.c_str());
  return rv;
}

extern "C" void easyMock_addCall(const char* call)
{
  std::string newCall(call);
  easyMock.addCall(newCall);
}

extern "C" void easyMock_addError(easyMock_bool callstack, const char *fmt, ...)
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

extern "C" easyMock_bool easyMock_checkCallsOrder()
{
  easyMock_bool rv = easyMock.checkCallsOrder() ? easyMock_true : easyMock_false;
  return rv;
}

extern "C" easyMock_bool easyMock_printCallStack()
{
  easyMock_bool rv = easyMock.printCallStack() ? easyMock_true : easyMock_false;
  return rv;
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

extern "C" void easyMock_setPrintCallStack(easyMock_bool val)
{
  easyMock.setPrintCallStack(val);
}

extern "C" void easyMock_setCheckCallsOrder(easyMock_bool val)
{
  easyMock.setCheckCallsOrder(val);
}

#ifdef BACKTRACE_SUPPORT
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
#endif
