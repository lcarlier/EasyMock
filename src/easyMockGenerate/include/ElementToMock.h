#ifndef ELEMENTTOMOCK_H
#define ELEMENTTOMOCK_H

#include "Parameter.h"
#include "ReturnValue.h"

enum ElementToMock_Type
{
  ETS_function
};

class ElementToMock
{
public:
  ElementToMock(std::string name, const Parameter::Vector functionParameters);

  typedef AutoCleanVectorPtr<ElementToMock> Vector;

  const std::string *getName() const;
  const Parameter::Vector *getFunctionsParameters() const;
  virtual ElementToMock_Type getMockType() const = 0;
  virtual const ReturnValue *getReturnType() const = 0;

  ElementToMock(const ElementToMock &other) = default;
  ElementToMock& operator=(const ElementToMock &other) = default;
  ElementToMock(ElementToMock &&other) = default;
  ElementToMock& operator=(ElementToMock &&other) = default;

  bool operator==(const ElementToMock &other) const;
  bool operator!=(const ElementToMock &other) const;

  virtual ElementToMock* clone() const = 0;
  virtual ~ElementToMock();

protected:
  std::string m_name;
  Parameter::Vector m_parameters;
};

#endif /* ELEMENTTOMOCK_H */

