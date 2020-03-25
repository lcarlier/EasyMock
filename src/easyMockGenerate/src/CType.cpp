#include "CType.h"

CType::CType() : CType(CTYPE_INVALID)
{
}

CType::CType(const easyMock_cTypes_t p_cType) :
TypeItf(easyMock_arrayCTypeStr[p_cType]), m_cType(p_cType)
{
  m_isCType = true;
}

easyMock_cTypes_t CType::getCType() const
{
  return m_cType;
}

bool CType::setUnsigned(bool val)
{
  easyMock_cTypes_t newCtype = CTYPE_INVALID;

  if(val)
  {
    switch(m_cType)
    {
      case CTYPE_CHAR:
        newCtype = CTYPE_UCHAR;
        break;
      case CTYPE_SHORT:
        newCtype = CTYPE_USHORT;
        break;
      case CTYPE_INT:
        newCtype = CTYPE_UINT;
        break;
      case CTYPE_LONG:
        newCtype = CTYPE_ULONG;
        break;
      case CTYPE_LONG_LONG:
        newCtype = CTYPE_ULONG_LONG;
        break;
      default:
        newCtype = CTYPE_INVALID;
    }
  }
  else
  {
    switch(m_cType)
    {
      case CTYPE_UCHAR:
        newCtype = CTYPE_CHAR;
        break;
      case CTYPE_USHORT:
        newCtype = CTYPE_SHORT;
        break;
      case CTYPE_UINT:
        newCtype = CTYPE_INT;
        break;
      case CTYPE_ULONG:
        newCtype = CTYPE_LONG;
        break;
      case CTYPE_ULONG_LONG:
        newCtype = CTYPE_LONG_LONG;
        break;
      default:
        newCtype = CTYPE_INVALID;
    }
  }
  if(newCtype == CTYPE_INVALID)
  {
    return false;
  }
  setCType(newCtype);
  return true;
}

void CType::setCType(easyMock_cTypes_t p_cType)
{
  m_cType = p_cType;
  this->setName(easyMock_arrayCTypeStr[m_cType]);
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

