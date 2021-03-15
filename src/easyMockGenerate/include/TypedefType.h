/*!
 * \file
 *
 * \brief Contains the implementation of ::TypedefType objects.
 */
#ifndef TYPEDEFTYPE_H
#define TYPEDEFTYPE_H

#include <TypeItf.h>

#include <string>

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
  TypedefType(const std::string& p_typedefName, TypeItf* p_typeeType);

  TypedefType(const TypedefType &other);
  TypedefType& operator=(TypedefType other);
  TypedefType(TypedefType &&other);
  //With elision pattern, no need for a move constructor

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
   * \copydoc ::TypeItf::clone()
   */
  virtual TypeItf* clone() const override;

  /*!
   * \copydoc ::EasyMock::Hashable::getHash
   */
  std::size_t getHash() const override;

  virtual ~TypedefType();

protected:
private:
  void swap(TypedefType &first, TypedefType &second);
  TypeItf* m_typeeType;
};

#endif /* TYPEDEFTYPE_H */
