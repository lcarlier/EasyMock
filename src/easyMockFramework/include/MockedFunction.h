#ifndef MOCKEDFUNCTION_H
#define MOCKEDFUNCTION_H

#include <easyMock_framework.h>

#include <string>
#include <queue>

template <class T>
class MockedFunction
{
private:
  typedef std::queue<T> MockedData_t;
public:

  MockedFunction(const std::string name) :
  m_name(name), m_expectedCall(0), m_actualCall(0)
  {
    emptyMockedDataQueue();
  }

  void addExpectedCall(T param)
  {
    m_mockedData.push(param);
    m_expectedCall++;
  }

  bool getCurrentCallParam(T& param)
  {
    if(m_mockedData.empty())
    {
      return false;
    }
    param = m_mockedData.front();
    m_mockedData.pop();
    return true;
  }

  bool addActualCall()
  {
    //Increment the actualCall anyway because verify() will check the equality of m_actualCall and m_expectedCall
    m_actualCall++;
    if ((m_actualCall - 1) == m_expectedCall)
    {
      return false;
    }
    return true;
  }

  unsigned int getNbActualCall()
  {
    return m_actualCall;
  }

  const std::string &getName()
  {
    return m_name;
  }

  void reset()
  {
    m_expectedCall = 0;
    m_actualCall = 0;
    emptyMockedDataQueue();
  }

  bool verify()
  {
    if (m_expectedCall != m_actualCall)
    {
      easyMock_addError(false, "Error: For function '%s' bad number of call. Expected %d, got %d", m_name.c_str(), m_expectedCall, m_actualCall);
      return false;
    }
    return true;
  }

private:
  void emptyMockedDataQueue()
  {
    while(!m_mockedData.empty())
    {
      m_mockedData.pop();
    }
  }
  std::string m_name;
  unsigned int m_expectedCall;
  unsigned int m_actualCall;
  MockedData_t m_mockedData;
};

#endif /* MOCKEDFUNCTION_H */

