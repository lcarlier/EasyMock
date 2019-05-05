#include <easyMock.h>
#include <easyMock_framework.h>
#include <MockedFunction.h>

#include <cstdio>
#include <string>
#include <vector>
#include <queue>
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
/*
 * Thanks to https://gist.github.com/banthar/1343977
 * for stack trace print
 */


typedef std::vector<const easyMock_mockedFileRegister_t *> MockVector_t;
typedef std::queue<std::string> FifoCall_t;
typedef std::queue<std::string> FifoError_t;

static std::string allErrorStr;

class EasyMock
{
public:

  EasyMock() { };

  void registerMock(const easyMock_mockedFileRegister_t *args)
  {
    m_registeredMock.push_back(args);
  }

  void initRegisteredMockedFile()
  {
    for (MockVector_t::const_iterator it = m_registeredMock.begin(); it != m_registeredMock.end(); ++it)
    {
      const easyMock_mockedFileRegister_t *f = *it;
      f->resetMockedFile();
    }
  }

  int verifyRegisteredMockedFile()
  {
    int rv = 1;
    for (MockVector_t::const_iterator it = m_registeredMock.begin(); it != m_registeredMock.end(); ++it)
    {
      const easyMock_mockedFileRegister_t *f = *it;
      if (!f->verifyMockedFile())
      {
        rv = 0;
      }
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
    m_error.push(error);
  }

  const char *getErrorStr()
  {
    allErrorStr.clear();
    while (!m_error.empty())
    {
      std::string &curErr = m_error.front();
      allErrorStr.append(curErr);
      allErrorStr.append("\n\r");
      m_error.pop();
    }
    return allErrorStr.c_str();
  }

  void addCall(const char *name)
  {
    m_fifoCall.push(name);
  }

  const char *popCurrentCall()
  {
    if (m_fifoCall.empty())
    {
      addError("BUG IN EASYMOCK. No more current call", false);
      return "NoMoreCall";
    }
    const std::string currentCall = m_fifoCall.front();
    m_fifoCall.pop();
    return currentCall.c_str();
  }
private:

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
#if 0
    unw_cursor_t cursor;
    unw_context_t context;

    unw_getcontext(&context);
    unw_init_local(&cursor, &context);

    int n = 0;
    while (unw_step(&cursor))
    {
      unw_word_t ip, sp, off;

      unw_get_reg(&cursor, UNW_REG_IP, &ip);
      unw_get_reg(&cursor, UNW_REG_SP, &sp);

      char symbol[256] = {"<unknown>"};
      char *name = symbol;

      if (!unw_get_proc_name(&cursor, symbol, sizeof (symbol), &off))
      {
        int status;
        if ((name = abi::__cxa_demangle(symbol, NULL, NULL, &status)) == 0)
          name = symbol;
      }

      append_string(error, "#%-2d 0x%016" PRIxPTR " sp=0x%016" PRIxPTR " %s + 0x%" PRIxPTR "\n",
              ++n,
              static_cast<uintptr_t> (ip),
              static_cast<uintptr_t> (sp),
              name,
              static_cast<uintptr_t> (off));

      if (name != symbol)
        free(name);
    }
#endif
  }

  void append_string(std::string &str, const char *fmt, ...)
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

  MockVector_t m_registeredMock;
  bool m_checkFifoCall;
  FifoCall_t m_fifoCall;
  FifoError_t m_error;
};

static EasyMock __attribute ((init_priority(101))) easyMock;

void easyMock_registerMock(const easyMock_mockedFileRegister_t *args)
{
  easyMock.registerMock(args);
}

const char *easyMock_popCurrentCall()
{
  return easyMock.popCurrentCall();
}

void easyMock_addCall(const char *call)
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
  std::string error(buf.begin(), buf.end() - 1); //-1 to remove the \0 added by vsnprintf. The std::string takes to terminate the string correctly

  easyMock.addError(error, callstack);
}

extern "C" void easyMock_init()
{
  easyMock.initRegisteredMockedFile();
}

extern "C" int easyMock_check()
{
  return easyMock.verifyRegisteredMockedFile();
}

extern "C" const char *easyMock_getErrorStr()
{
  return easyMock.getErrorStr();
}

MockedFunction::MockedFunction(const std::string name) :
m_name(name), m_expectedCall(0), m_actualCall(0) { }

void MockedFunction::addExpectedCall()
{
  m_expectedCall++;
}

bool MockedFunction::addActuallCall()
{
  //Increment the actualCall anyway becayse very will check the equality of m_actualCall and m_expectedCall
  m_actualCall++;
  if ((m_actualCall - 1) == m_expectedCall)
  {
    return false;
  }
  return true;
}

const char *MockedFunction::getName()
{
  return m_name.c_str();
}

void MockedFunction::reset()
{
  m_expectedCall = 0;
  m_actualCall = 0;
}

bool MockedFunction::verify()
{
  if (m_expectedCall != m_actualCall)
  {
    easyMock_addError(false, "Error: For function '%s' bad number of call. Expected %d, got %d", m_name.c_str(), m_expectedCall, m_actualCall);
    return false;
  }
  return true;
}
