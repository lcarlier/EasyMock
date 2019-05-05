#ifndef MOCKEDFUNCTION_H
#define MOCKEDFUNCTION_H

#include <string>

class MockedFunction
{
public:
  MockedFunction(const std::string name);
  void addExpectedCall();
  bool addActuallCall();
  const char *getName();
  void reset();
  bool verify();
private:
  std::string m_name;
  unsigned int m_expectedCall;
  unsigned int m_actualCall;
};

#endif /* MOCKEDFUNCTION_H */

