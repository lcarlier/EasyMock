/*! \file
 * \brief Contains the base class of all the Declarator elements.
 */
#ifndef DECLARATOR_H
#define DECLARATOR_H

#include "EasyMock_Hashable.h"

#include <string>

class TypeItf;

/*!
 *
 * \brief Represents any declarator.
 *
 * This class represents a declaration of:
 * - a type parameter
 * - a return value
 * - a struct/union field.
 *
 * For instance in the following code
 * \code{.c}
 * struct s
 * {
 *   int f;
 * };
 *
 * float foo(int param);
 * \endcode
 *
 * The following code structure can be represented by a Declarator:
 * - The field declaration: <tt>int f;</tt>
 * - The parameter declaration: <tt>int param</tt>
 * - The return value: <tt>float</tt>
 *
 * \note Even though this class is not pure virtual, it is not very useful to be
 * used as is and it is recommended to use a subclass instead. To make sure of that
 * the constructors of the Declarator class are protected.
 */
class Declarator : public virtual EasyMock::Hashable
{
public:
  Declarator(const Declarator& other);
  Declarator &operator=(Declarator other);

  Declarator(Declarator &&other);

  /*!
   * \brief Returns the type of the Declarator
   *
   * \sa TypeItf
   */
  TypeItf* getType();

  /*!
   * \copydoc getType()
   */
  const TypeItf* getType() const;

  /*!
   * \brief Sets the type of the declarator
   *
   * \sa TypeItf
   */
  void setType(TypeItf* type);

  /*!
   * \brief Returns the actual line of code which was use to declare the Declarator.
   *
   * \sa setDeclareString
   */
  std::string getDeclareString() const;

  /*!
   * \brief Sets the string which is used to declare the Declarator
   *
   * It is possible to use macro to declare to represent types. However,
   * they are not recognised as type by the compiler. In some circumstance
   * (e.g. for va_args from stdargs.h), it is mandatory to use the macro definition
   * because it will translate to the correct implicit type (__builtin_va_arg in GCC)
   * which is compiler dependent.
   *
   * A simple example of using setDeclareString would be to represent this
   * piece of C code
   * \code{.c}
   * #define int myInt
   *
   * void foo(myInt var);
   * \endcode
   *
   * In order to represent the parameter of the foo function, the following code
   * needs to be used
   * \code{.cpp}
   * ReturnValue rv(new CType(CTYPE_INT));
   * rv.setDeclareString("myInt var");
   * \endcode
   *
   * In this case, the macro <tt>myType</tt> doesn't represent a type so it is
   * not correct to use the TypeItf interface to represent it. Instead, it is
   * considered as a string of code which is exactly the purpose of
   * setDeclareString
   */
  Declarator& setDeclareString(const std::string& newString);

  /*!
   * \brief Compares 2 ::Declarator objects.
   *
   * Unlike the TypeItf object, this function doesn't call a virtual
   * protected isEqual() method. This is because the purpose of this object
   * is not be to used via it's main parent class (i.e. ::Declarator).
   */
  bool operator==(const Declarator &other) const;
  bool operator!=(const Declarator &other) const;

  /*!
   * \copydoc ::TypeItf::clone
   */
  virtual Declarator* clone() const;

  /*!
   * \copydoc ::EasyMock::Hashable::getHash()
   */
  std::size_t getHash() const override;

  virtual ~Declarator();

protected:

  /*!
   * \brief Returns if this instance is equal to another.
   *
   * \param p_other A reference to the other object to be compared with
   *
   * For the objects having pointers members, the pointer is dereferenced
   * and the operator==() function is called.
   *
   * This function is not intended to be called directly by the users of the class
   * and is called from the operator==() function.
   *
   * This function is virtual and is meant to be overwritten by the subclasses.
   * The purpose of this is to compare the full object when base pointers are
   * used.
   *
   * \return True if the objects are equal.
   * \return False if the objects are not equal.
   */
  virtual bool isEqual(const Declarator& p_other) const;

  /*!
   * \brief Creates a new declarator.
   *
   * \param p_typeItf The TypeItf object which is hold by this declarator.
   */
  explicit Declarator(TypeItf* p_typeItf);

  friend void swap(Declarator &first, Declarator &second);
private:
  TypeItf* m_type;
  std::string m_declaredString;

  void updateDeclareString();
};

#endif /* DECLARATOR_H */
