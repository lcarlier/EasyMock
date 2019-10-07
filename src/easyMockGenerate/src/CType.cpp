#include "CType.h"

CType::CType(const easyMock_cTypes_t p_cType) :
TypeItf(easyMock_arrayCTypeStr[p_cType]), m_cType(p_cType)
{}

bool CType::isCType() const
{
  return true;
}

const easyMock_cTypes_t CType::getCType() const
{
  return m_cType;
}

CType* CType::clone() const
{
  return new CType(*this);
}

bool CType::operator==(const CType& other) const
{
  return TypeItf::operator ==(other) && m_cType == other.m_cType;
}

bool CType::operator!=(const CType& other) const
{
  return (*this == other) == false;
}

