#include "EasyMock_CType.h"

CType::CType() : CType(CTYPE_INVALID)
{
}

CType::CType(const easyMock_cTypes_t p_cType, bool isConst) :
CType(p_cType, "", isConst)
{
}

CType::CType(const easyMock_cTypes_t p_cType, std::string p_typeDefName, bool isConst) :
TypeItf(easyMock_arrayCTypeStr[p_cType], p_typeDefName), m_cType(p_cType), m_initAsNakedChar(p_cType == CTYPE_CHAR)
{
  this->setConst(isConst);
  this->setCType(true);
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
    //signed to unsigned
    switch(m_cType)
    {
#if IS_CHAR_DEFAULT_SIGNED
      case CTYPE_CHAR:
#endif
      case CTYPE_SCHAR:
        newCtype = CTYPE_UCHAR;
#if IS_CHAR_DEFAULT_UNSIGNED
        if(m_initAsNakedChar)
        {
          newCtype = CTYPE_CHAR;
        }
#endif
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
    //unsigned to signed
    switch(m_cType)
    {
#if IS_CHAR_DEFAULT_UNSIGNED
      case CTYPE_CHAR:
#endif
      case CTYPE_UCHAR:
        newCtype = CTYPE_SCHAR;
#if IS_CHAR_DEFAULT_SIGNED
        if(m_initAsNakedChar)
        {
          newCtype = CTYPE_CHAR;
        }
#endif
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
  updateCType(newCtype);
  return true;
}

//Private
void CType::updateCType(easyMock_cTypes_t p_cType)
{
  m_cType = p_cType;
  this->setName(easyMock_arrayCTypeStr[m_cType]);
}


CType* CType::clone() const
{
  return new CType(*this);
}

bool CType::isEqual(const TypeItf& p_other) const
{
  bool parentEq = TypeItf::isEqual(p_other);
  if(!parentEq)
  {
    return false;
  }
  if(!p_other.isCType())
  {
    return false;
  }
  const CType &other = dynamic_cast<const CType &>(p_other);
  bool ctypeEq = this->m_cType == other.m_cType;

  return ctypeEq;
}

bool CType::operator==(const CType& other) const
{
  return this->isEqual(other);
}

bool CType::operator!=(const CType& other) const
{
  return (*this == other) == false;
}

