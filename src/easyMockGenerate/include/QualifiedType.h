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
  QualifiedType(const QualifiedType& p_other) = delete;
  QualifiedType& operator=(QualifiedType &p_other) = delete;
  QualifiedType(QualifiedType &&other) = default;
  QualifiedType& operator=(QualifiedType &&other) = default;

  bool operator==(const QualifiedType& p_other) const;
  bool operator!=(const QualifiedType& p_other) const;

  /*!
   * \copydoc ::QualifiedType::getUnqualifiedType()
   */
  const TypeItf* getUnqualifiedType() const;

  /*!
   * \brief Sets the unqualified type of this qualified type.
   *
   * This function is meant to replace an existing unqualified type of an existing qualified one.
   * For instance by replacing the typedef type with its non typedef equivalent.
   */
  void setUnqualifiedType(std::shared_ptr<TypeItf> p_newUnqualifiedType);

  /*!
   * \brief Returns the type being qualified
   */
  TypeItf* getUnqualifiedType();

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
  virtual const char* getQualifierString() const;

  /*!
   * \copydoc ::TypeItf::getDeclarationPrefix
   */
  virtual std::string getDeclarationPrefix(bool p_naked = false) const override;

  /*!
   * \copydoc ::EasyMock::Hashable::getHash()
   */
  std::size_t getHash() const noexcept override;

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
  QualifiedType(std::shared_ptr<TypeItf> p_type);

  virtual bool isEqual(const TypeItf& p_other) const override;

  friend void swap(QualifiedType& first, QualifiedType& second);
private:
  std::shared_ptr<TypeItf> m_type;
};

#endif /* QUALIFIEDTYPE_H */
