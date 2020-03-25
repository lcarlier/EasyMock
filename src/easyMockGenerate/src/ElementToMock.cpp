#include "ElementToMock.h"

ElementToMock::ElementToMock(std::string name, const Parameter::Vector functionParameters)
: m_name(name), m_parameters(functionParameters) { }

const Parameter::Vector& ElementToMock::getFunctionsParameters() const
{
  return m_parameters;
}

const std::string* ElementToMock::getName() const
{
  return &m_name;
}

bool ElementToMock::operator==(const ElementToMock& other) const
{
  return this->m_name == other.m_name && this->m_parameters == other.m_parameters;
}

bool ElementToMock::operator!=(const ElementToMock& other) const
{
  return (*this == other) == false;
}


ElementToMock::~ElementToMock() { }
