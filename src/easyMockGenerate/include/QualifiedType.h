/*! \file
 *
 * \brief Contains the interface to define a qualified type.
 */
#ifndef QUALIFIEDTYPE_H
#define QUALIFIEDTYPE_H

#include <TypeItf.h>

/*!
 *
 * \brief Class defining the interface to define a qualified type.
 */
class QualifiedType : public TypeItf
{
public:
  QualifiedType(const QualifiedType& p_other);
  QualifiedType& operator=(QualifiedType p_other);

  bool operator==(const QualifiedType& p_other) const;
  bool operator!=(const QualifiedType& p_other) const;

  /*!
   * \copydoc ::QualifiedType::getType()
   */
  const TypeItf* getType() const;

  /*!
   * \brief Returns the type being qualified
   */
  TypeItf* getType();

  /*!
   * \brief Returns whether the qualified type is const.
   *
   * When this function returns true on a particular instance, it can be
   * safely downcasted to ::ConstQualifiedType
   */
  virtual bool isConst() const;

  /*!
   * \brief Returns the keyword of the qualified type.
   *
   * For const qualified type, this function returns "const"
   */
  virtual const char* getString() const;

  /*!
   * \copydoc ::TypeItf::clone()
   */
  virtual TypeItf* clone() const override;
  virtual ~QualifiedType();
protected:
  /*!
   * \brief Construct a new QualifiedType class.
   *
   * The constructor is protected because only the class inheriting from
   * this class can call it.
   */
  QualifiedType();

  /*!
   * \copydoc ::QualifiedType::QualifiedType()
   */
  QualifiedType(TypeItf* p_type);

  virtual bool isEqual(const TypeItf& p_other) const override;
  friend void swap(QualifiedType& first, QualifiedType& second);
private:
  TypeItf* m_type;
};

#endif /* QUALIFIEDTYPE_H */

