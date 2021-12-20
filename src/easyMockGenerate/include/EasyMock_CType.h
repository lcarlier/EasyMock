/*! \file
 * \brief Contains the class to represent any of the C basic types
 */
#ifndef CTYPE_H
#define CTYPE_H

#include "TypeItf.h"

#include <string>
#include <limits.h>


#define IS_CHAR_DEFAULT_SIGNED (CHAR_MIN != 0)
#define IS_CHAR_DEFAULT_UNSIGNED (!(IS_CHAR_DEFAULT_SIGNED))

/*!
 * \brief This class represents any of the C basic types
 */
class CType : public TypeItf
{
public:
  /*!
   * \brief Creates a new CType.
   *
   * When using the default constructor, the CType will be invalid
   * and doesn't correspond to any valid C type.
   */
  CType();
  /*!
   * \brief Creates a new CType.
   *
   * \param p_cType The C basic data type.
   */
  CType(const easyMock_cTypes_t p_cType);

  /*!
   * \brief returns the type represented by this instance.
   * \return returns the type represented by this instance. See ::easyMock_cTypes_t.
   */
  easyMock_cTypes_t getCType() const override;

  /*!
   * \brief set whether the type is unsigned or not.
   *
   * \param val <tt>true</tt> to set the type as <tt>signed</tt>. <tt>false</tt> to set the type as unsigned;
   *
   * e.g. <tt>char</tt> is signed while <tt>unsigned char</tt> is unsigned.
   *
   * The return value must be checked.
   *
   * \return true if the signed has been successfully set
   * \return false if the signed has not been set
   *
   * \return This function returns <tt>false</tt> if the represented type cannot be unsigned (e.g. <tt>float</tt>).
   *
   * \return This functions returns <tt>false</tt> if it is tried to set the same
   * "<tt>unsigned</tt>" value as the existing type. E.g. trying to call
   * <tt>setUnsigned(true)</tt> on a variable which represents <tt>unsigned int</tt>
   * returns false.
   */
  bool setUnsigned(bool val);

  /*!
   * \copydoc ::TypeItf::getDeclarationPrefix
   */
  virtual std::string getDeclarationPrefix(bool p_naked = false) const override;

  CType(const CType &other) = default;
  CType& operator=(const CType &other) = default;
  CType(CType &&other) = default;
  CType& operator=(CType &&other) = default;

  /*!
   * \brief Checks the equality in between 2 CType.
   */
  bool operator==(const TypeItf &other) const;
  bool operator!=(const TypeItf &other) const;

  /*!
   * \copydoc ::EasyMock::Hashable::getHash()
   */
  std::size_t getHash() const noexcept override;

  /*
   * bool isEqual(const TypeItf &other);
   * Doesn't need to be overridden because the name is updated whenever the CType object changes.
   * Therefore relying on the operator== of TypeItf is good enough because the name is reliable
   */
protected:
   /*!
   * \copydoc TypeItf::isEqual
   */
  bool isEqual(const TypeItf& p_other) const override;

private:
  void updateCType(easyMock_cTypes_t p_cType);
  easyMock_cTypes_t m_cType;
  bool m_initAsNakedChar;
};

#endif /* CTYPE_H */
