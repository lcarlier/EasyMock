#ifndef CTYPE_H
#define CTYPE_H

#include "TypeItf.h"

class CType : public TypeItf
{
public:
  CType();
  explicit CType(const easyMock_cTypes_t p_cType, bool isConst = false);
  easyMock_cTypes_t getCType() const override;
  bool setUnsigned(bool val);

  CType(const CType &other) = default;
  CType& operator=(const CType &other) = default;
  CType(CType &&other) = default;
  CType& operator=(CType &&other) = default;
  bool operator==(const CType &other) const;
  bool operator!=(const CType &other) const;

  bool isEqual(const TypeItf& other) const override;

  CType *clone() const override;
  /*
   * bool isEqual(const TypeItf &other);
   * Doesn't need to be overridden because the name is updated whenever the CType object changes.
   * Therefore relying on the operator== of TypeItf is good enough because the name is reliable
   */
private:
  void updateCType(easyMock_cTypes_t p_cType);
  easyMock_cTypes_t m_cType;
};

#endif /* CTYPE_H */

