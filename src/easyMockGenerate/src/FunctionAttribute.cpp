#include <FunctionAttribute.h>

#include <boost/functional/hash.hpp>

FunctionAttribute::FunctionAttribute(std::string p_name):
FunctionAttribute(std::move(p_name), ParametersList{})
{}

FunctionAttribute::FunctionAttribute(std::string p_name, ParametersList p_parameters):
m_name{std::move(p_name)}, m_parameters{std::move(p_parameters)}
{}

const std::string & FunctionAttribute::getName() const
{
  return m_name;
}

const FunctionAttribute::ParametersList & FunctionAttribute::getParameters() const
{
  return m_parameters;
}

bool FunctionAttribute::operator==(const FunctionAttribute& other) const
{
  const bool nameEq = this->m_name == other.m_name;
  const bool paramEq = this->m_parameters == other.m_parameters;

  return nameEq && paramEq;
}

std::size_t FunctionAttribute::getHash() const
{
  std::size_t seed { 0 };
  boost::hash_combine(seed, m_name);
  boost::hash_combine(seed, m_parameters);

  return seed;
}

bool FunctionAttribute::operator!=(const FunctionAttribute& other) const
{
  return (*this == other) == false;
}
