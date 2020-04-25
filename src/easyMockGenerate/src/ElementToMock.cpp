#include "ElementToMock.h"

ElementToMock::ElementToMock(std::string name, const Parameter::Vector functionParameters)
: m_name(name), m_parameters(functionParameters), m_isVariadic(false) { }

const Parameter::Vector& ElementToMock::getFunctionsParameters() const
{
  return m_parameters;
}

const std::string* ElementToMock::getName() const
{
  return &m_name;
}

bool ElementToMock::isVariadic() const
{
  return m_isVariadic;
}

void ElementToMock::setVariadic(bool value)
{
  m_isVariadic = value;
}

bool ElementToMock::operator==(const ElementToMock& other) const
{
  return this->m_name == other.m_name &&
          this->m_parameters == other.m_parameters &&
          this->m_isVariadic == other.m_isVariadic;
}

bool ElementToMock::operator!=(const ElementToMock& other) const
{
  return (*this == other) == false;
}


ElementToMock::~ElementToMock() { }
