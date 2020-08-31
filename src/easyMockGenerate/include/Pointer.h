/*! @file
 *
 * \brief Contains the class to represent a pointer.
 */
#include "TypeItf.h"

#ifndef POINTER_H
#define POINTER_H

/*!
 * \brief This class represent pointers.
 *
 * For instance, the following declaration are to be represented by a Pointer
 * object
 * @code{.c}
 * int *a;
 * const int *b;
 * @endcode
 */
class Pointer : public TypeItf
{
public:
  Pointer(TypeItf *p_type, bool p_isConst = false);

  /*!
   * \brief Creates a new Pointer
   *
   * \param p_type The TypeItf to which the pointer is pointing to.
   * \param p_type_def_name The typedef alias associated with this pointer type
   * \param p_isConst Specifies whether the value of the pointer (i.e. the address
   * it stores) is constant or not.
   *
   * Attention needs to be taken when dealing with constant pointed values.
   * For representing constant pointed values such as
   * \code{.c}
   * const int * ptr;
   * \endcode
   * the following code can be used
   * \code{.cpp}
   * bool typeIsConst = true;
   * // Note that the typeIsConst parameter is given to the CType constructor,
   * // not to the Pointer constructor
   * Pointer eMockP(new CType(CTYPE_INT, typeIsConst));
   *
   * // The following asserts will not fail
   * assert(eMockP.isConst() == false);
   * assert(eMockP.getPointedType()->isConst() == true);
   * \endcode
   * I.E. the <tt>iscConst</tt> parameter must be given to the pointed
   * type and not to the pointer type itself.
   *
   * A pointer can be typedef when having such c code
   * \code{.c}
   * typedef ptrInt int*;
   * \endcode
   *
   * \heapPointer
   */
  Pointer(TypeItf *p_type, const std::string p_type_def_name, bool p_isConst = false);
  Pointer(const Pointer &other);
  Pointer& operator=(Pointer other);

  bool operator==(const Pointer &other) const;
  bool operator!=(const Pointer &other) const;

  Pointer(Pointer &&other);
  //With elision pattern no need for move assignment

  /*!
   * \copydoc TypeItf::~TypeItf()
   * \warning See also setRecursivePointer()
   */
  virtual ~Pointer();

  /*! \copydoc getPointedType() */
  const TypeItf* getPointedType() const;

  /*!
   * \brief Returns the TypeItf which represent the type on which this pointer points
   */
  TypeItf* getPointedType();

  /*!
   * \brief Set the new pointed type for this pointer.
   *
   * \warning If the pointer was already pointing to a TypeItf object. It will be
   * deleted first.
   *
   * \warning If the pointer is set as recursive pointer (with setRecursivePointer())
   * <b>before</b> calling setPointedType(), the TypeItf object to which this pointer is
   * pointing <b>will not be deleted</b>. This is to be able to support recursive
   * type.
   *
   * \see ComposableField::ComposableField(TypeItf*,std::string,attributes)
   */
  bool setPointedType(TypeItf* newPointedType);

  /*!
   * \brief Sets whether the pointed is is a recursive type or not.
   *
   * An example of pointer pointing to a recursive type is as following
   * \code{.c}
   * struct s
   * {
   *    struct s * f;
   * };
   * \endcode
   * The field @c is of the <tt>struct s</tt> is recursive pointer type.
   *
   * Setting a Pointer object to be recursive is important when comparing Pointer
   * objects. When a Pointer object is set to be recursive, the
   * operator==(const Pointer&) will compare the name returned by
   * TypeItf::getMostDefinedName() of the pointed type instead of comparing
   * the full pointed type object via their own operator==. This is to avoid
   * infinite call loop to operator==(const Pointer&).
   *
   * \note union can also hold recursive pointer type.
   */
  void setRecursivePointer(bool value);

  /*! @copydoc TypeItf::clone() */
  Pointer* clone() const override;

protected:
  /*!
   * \copydoc TypeItf::isEqual
   */
  bool isEqual(const TypeItf& p_other) const override;
private:
  void swap(Pointer &first, Pointer &second);
  TypeItf* m_pointedType;
  bool m_isRecursivePointer;
};

#endif /* POINTER_H */

