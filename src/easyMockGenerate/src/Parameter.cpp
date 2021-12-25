#include "Parameter.h"
#include "TypeItf.h"
#include "EasyMock_CType.h"
#include "StructType.h"
#include "Pointer.h"

Parameter::Parameter(std::shared_ptr<TypeItf> p_type, std::string p_name) :
Declarator{std::move(p_type)},
m_name{std::move(p_name)},
m_cachedHash{0}
{
}

Parameter::~Parameter()
{
}

Parameter VoidParameter(std::string p_name)
{
  Parameter p{std::make_shared<CType>(CTYPE_VOID), p_name};
  p.cacheHash();

  return p;
}

Parameter NamedParameter(easyMock_cTypes_t p_type, std::string p_name, bool p_isPointer)
{
  std::shared_ptr<TypeItf> curType = std::make_shared<CType>(p_type);
  if(p_isPointer)
  {
    curType = std::make_shared<Pointer>(std::move(curType));
  }
  Parameter p{std::move(curType), p_name};
  p.cacheHash();

  return p;
}

Parameter StructParameter(std::string p_type, std::string p_name, ComposableType::ComposableFieldTypeVector elem, bool p_is_embedded_in_other_type)
{
  Parameter p{std::make_shared<StructType>(p_type, std::move(elem), p_is_embedded_in_other_type), p_name};
  p.cacheHash();

  return p;
}

const std::string& Parameter::getName() const
{
  return m_name;
}

bool Parameter::operator==(const Parameter& other) const
{
  return this->isEqual(other);
}

std::size_t Parameter::getHash() const noexcept
{
  if(m_cachedHash != 0)
  {
    return m_cachedHash;
  }
  std::size_t seed { Declarator::getHash() };
  //Parameters are equals only if type matches, name is not important

  return seed;
}

void Parameter::cacheHash() noexcept
{
  m_cachedHash = 0;
  Declarator::cacheHash();
  m_cachedHash = Parameter::getHash();
}

bool Parameter::isEqual(const Declarator& other) const
{
  //Parameters are equals only if type matches, name is not important
  return Declarator::isEqual(other);
}

bool Parameter::operator!=(const Parameter& other) const
{
  return (*this == other) == false;
}
