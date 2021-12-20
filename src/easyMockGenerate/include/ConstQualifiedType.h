/*! \file
 *
 * \brief Contains the class to define a const qualified type
 */
#ifndef CONSTQUALIFIEDTYPE_H
#define CONSTQUALIFIEDTYPE_H

#include <QualifiedType.h>

/*!
 * \brief Class defining a type that is declared using the \c const keyword.
 *
 * An example of const variable is
 * \code{.c}
 * const unsigned int FOO = 42;
 * \endcode
 *
 * Attention needs to be taken when dealing with constant pointed values.
 * For representing constant pointed values such as
 * \code{.c}
 * const int * ptr;
 * \endcode
 * the following code can be used
 * \code{.cpp}
 * // Note that the typeIsConst parameter is given to the CType constructor,
 * // not to the Pointer constructor
 * Pointer eMockP { new ConstQualifiedType(new CType(CTYPE_INT)) };
 *
 * // The following asserts will not fail
 * assert(eMockP.isConst() == false);
 * assert(eMockP.getPointedType()->isConst() == true);
 * \endcode
 */
class ConstQualifiedType : public QualifiedType
{
public:
  /*!
   * \brief Instantiate a new const qualified type.
   *
   * \param p_type The type to be const qualified
   */
  ConstQualifiedType(std::shared_ptr<TypeItf> p_type);

  ConstQualifiedType(const ConstQualifiedType& orig) = delete;
  ConstQualifiedType& operator=(const ConstQualifiedType& p_other) = delete;
  ConstQualifiedType(ConstQualifiedType&& p_other) = default;
  ConstQualifiedType& operator=(ConstQualifiedType &&other) = default;

  bool operator==(const TypeItf& p_other) const;
  bool operator!=(const TypeItf& p_other) const;

  /*!
   * \copydoc ::QualifiedType::isConst()
   */
  bool isConst() const override;

  /*!
   * \copydoc ::QualifiedType::getQualifierString()
   */
  const char* getQualifierString() const override;

  /*!
   * \copydoc ::EasyMock::Hashable::getHash()
   */
  std::size_t getHash() const noexcept override;

  ~ConstQualifiedType() = default;
protected:
  bool isEqual(const TypeItf& p_other) const override;
  friend void swap(ConstQualifiedType& first, ConstQualifiedType& second);
private:

};

#endif /* CONSTQUALIFIEDTYPE_H */
