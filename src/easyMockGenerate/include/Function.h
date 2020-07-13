/*! \file
 * \brief Contains the class to represent a function.
 */
#ifndef FUNCTION_H
#define FUNCTION_H

#include "ElementToMock.h"
#include "ReturnValue.h"

#include <string>

/*!
 * \brief Represents a function.
 */
class Function : public ElementToMock
{
public:
  Function(std::string functionName, ReturnValue functionReturnType, Parameter::Vector functionParameters);
  ElementToMock_Type getMockType() const;
  const ReturnValue *getReturnType() const;
  std::string getFunctionPrototype() const;

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
  ReturnValue m_returnType;
};

#endif /* FUNCTION_H */

