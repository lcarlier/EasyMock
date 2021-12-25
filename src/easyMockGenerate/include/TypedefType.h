/*!
 * \file
 *
 * \brief Contains the implementation of ::TypedefType objects.
 */
#ifndef TYPEDEFTYPE_H
#define TYPEDEFTYPE_H

#include <TypeItf.h>

#include <string>
#include <memory>

/*!
 * \brief Represents a typedef type.
 *
 * A typedef type is declared in C using the typedef keyword.
 */
class TypedefType : public TypeItf {
public:
  /*!
   * \brief Declares a new typedef type.
   * \param p_typedefName The name of the typedef
   * \param p_typeeType The type that the typedef defines.
   *
   * E.g. The following typedef
   * \code{.c}
   * typedef int t_int;
   * \endcode
   * can be declared like so
   * \code{.cpp}
   * TypedefType t("t_int", new CType(CTYPE_INT));
   * \endcode
   */
  TypedefType(std::string p_typedefName, std::shared_ptr<TypeItf> p_typeeType);

  TypedefType(const TypedefType &other) = delete;
  TypedefType& operator=(const TypedefType& other) = delete;
  TypedefType(TypedefType &&other) = default;
  TypedefType& operator=(TypedefType &&other) = default;

  bool operator==(const TypeItf &other) const;
  bool operator!=(const TypeItf &other) const;

  /*!
   * \copydoc ::TypeItf::isEqual
   */
  bool isEqual(const TypeItf &p_other) const override;

  /*!
   * \copydoc ::TypeItf::getDeclarationPrefix
   */
  virtual std::string getDeclarationPrefix(bool p_naked = false) const override;

  /*!
   * \brief Returns the typee type.
   *
   * \note The actual typedef string name can be retrieved via ::TypeItf::getName
   *
   * \return The typee type.
   */
  const TypeItf* getTypee() const;

  /*!
   * \copydoc ::TypedefType::getTypee() const
   */
  TypeItf* getTypee();

  /*!
   * \brief Returns the actual type alised by the typedef
   *
   * \return The actual type alised by the typedef
   */
  const TypeItf* getMostDefinedTypee() const;

  /*!
   * \copydoc ::TypedefType::getMostDefinedTypee() const
   */
  TypeItf* getMostDefinedTypee();

  /*!
   * \copydoc ::EasyMock::Hashable::getHash
   */
  std::size_t getHash() const noexcept override;

  /*!
   * \copydoc ::EasyMock::Hashable::cacheHash()
   */
  void cacheHash() noexcept override;

  /*!
   * \copydoc ::TypeItf::getRawHash()
   */
  std::size_t getRawHash() const noexcept override;

  virtual ~TypedefType();

protected:
private:
  std::shared_ptr<TypeItf> m_typeeType;
  std::size_t m_cachedHash;
  std::size_t m_cachedRawHash;
};

#endif /* TYPEDEFTYPE_H */
