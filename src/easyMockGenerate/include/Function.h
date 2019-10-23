#ifndef FUNCTION_H
#define FUNCTION_H

#include "ElementToMock.h"
#include "ReturnValue.h"

class Function : public ElementToMock
{
public:
  Function(std::string functionName, ReturnValue functionReturnType, Parameter::Vector functionParameters);
  ElementToMock_Type getMockType() const;
  const ReturnValue *getReturnType() const;

  Function(const Function &other) = default;
  Function& operator=(const Function &other) = default;
  Function(Function &&other) = default;
  Function& operator=(Function &&other) = default;

  bool operator==(const Function &other) const;
  bool operator!=(const Function &other) const;

  virtual Function* clone() const;

  static Function& toFunction(ElementToMock& elem)
  {
    return dynamic_cast<Function&>(elem);
  }
private:
  ReturnValue m_returnTypeStr;
};

#endif /* FUNCTION_H */

