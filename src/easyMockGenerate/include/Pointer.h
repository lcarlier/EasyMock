/*! @file
 *
 * \brief Contains the class to represent a pointer.
 */
#include "TypeItf.h"

#ifndef POINTER_H
#define POINTER_H

/*!
 * \brief Represents a pointer.
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
  /*!
   * \brief Creates a new Pointer
   *
   * \param p_type The TypeItf to which the pointer is pointing to.
   *
   * A pointer can be typedef when having such c code
   * \code{.c}
   * typedef ptrInt int*;
   * \endcode
   *
   * \heapPointer
   */
  Pointer(TypeItf *p_type);
  Pointer(const Pointer &other);
  Pointer& operator=(Pointer other);

  /*!
   * \brief Compare ::Pointer object
   */
  bool operator==(const TypeItf &other) const;
  bool operator!=(const TypeItf &other) const;

  Pointer(Pointer &&other);
  //With elision pattern no need for move assignment

  /*!
   * \copydoc TypeItf::~TypeItf()
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
   * \see ComposableField::ComposableField(TypeItf*,std::string,attributes)
   */
  bool setPointedType(TypeItf* newPointedType);

  /*!
   * \copydoc ::TypeItf::getDeclarationPrefix
   */
  virtual std::string getDeclarationPrefix(bool p_naked = false) const override;

  /*!
   * \brief Helper function that returned the actual type pointed by this pointer
   *
   * \return The ::TypeItf object corresponding to the actual type pointed by this pointer
   */
  TypeItf* getMostPointedType() const;

  /*!
   * \copydoc TypeItf::clone()
   */
  Pointer* clone() const override;

  /*!
   * \copydoc ::EasyMock::Hashable::getHash()
   */
  std::size_t getHash() const override;

protected:
  /*!
   * \copydoc TypeItf::isEqual
   */
  bool isEqual(const TypeItf& p_other) const override;
private:
  void swap(Pointer &first, Pointer &second);
  TypeItf* m_pointedType;
};

#endif /* POINTER_H */
