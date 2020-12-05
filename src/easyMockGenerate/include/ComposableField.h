/*! \file
 *
 * \brief Contains the class to represent fields of composed type such as struct and union.
 */
#ifndef COMPOSABLEFIELD_H
#define COMPOSABLEFIELD_H

#include "AutoCleanVectorPtr.h"
#include "EasyMockGenerateTypes.h"

#include "Declarator.h"

#include <string>

//Forward declare TypeItf to avoid circular include dependencies
class TypeItf;
class ComposableType;
class Pointer;

/*!
 * \brief Represents a field of composed type such as struct and union.
 *
 * For instance, in the following code
 * \code{.c}
 * struct s
 * {
 *   int fs1;
 * };
 *
 * union u
 * {
 *   char us1;
 * };
 * \endcode
 * The following elements are represented by the ComposableField class
 * - <tt>int fs1</tt>
 * - <tt>char us1</tt>
 *
 * If a struct contains another struct, its StructType will be stored
 * inside the ComposableType class.
 *
 * A ComposableField can also have incomplete type fields.
 * \see ::ComposableField::ComposableField(TypeItf*,std::string,attributes)
 */
class ComposableField : public Declarator
{
public:

  /*!
   * \brief A ::AutoCleanVectorPtr containing ::ComposableField objects.
   *
   * \heapPointer
   */
  typedef AutoCleanVectorPtr<ComposableField> Vector;

  /*!
   * \brief The ComposableField's attributes
   */
  typedef struct
  {
    /*!
     * \brief Sets the array size of the field.
     *
     * The following cases exists:
     * - <tt>arraySize < 0 </tt>: means that this field is not an array
     * - <tt>arraySize == 0</tt>: means that this fields is an unbounded array. I.e isUnboundSpecifiedArray() returns <tt>true</tt>
     * - <tt>arraySize > 0 </tt>: means that this fields is a bounded array. I.e isBoundSpecifiedArray() returns <tt>true</tt>
     */
    int64_t arraySize;
  } attributes;
  ComposableField(const easyMock_cTypes_t p_ctype, std::string p_name);
  ComposableField(TypeItf *p_type, std::string p_name);
  /*!
   * \brief Creates a new ComposableField
   *
   * It is possible to represent forward declared type or recursively used
   * type by using the ::IncompleteType class
   *
   * \heapPointer
   *
   */
  ComposableField(TypeItf *p_type, std::string p_name, attributes p_attrib);

  /*!
   * \brief Returns if the type of the field is an incomplete type
   *
   * In the following code
   * \code{.c}
   * struct s
   * {
   *   struct s* s1;
   * };
   * \endcode
   * The type of the field <tt>s1</tt> is incomplete.
   *
   * In the following code
   * \code{.c}
   * struct incomplete; //forward declaration
   * struct s
   * {
   *   struct incomplete* i;
   * };
   * \endcode
   * The type of the field <tt>i</tt> is incomplete.
   */
  bool isIncompleteTypeField() const;

  ComposableField(const ComposableField &other);
  ComposableField &operator=(ComposableField other);

  ComposableField(ComposableField &&other);
  // No move assignment operator whenever using the copy-and-swap idiom.

  /*!
   * \brief Compares 2 ComposableField objects.
   *
   * \copydetails ::Declarator::operator==()
   */
  bool operator==(const ComposableField &other) const;
  bool operator!=(const ComposableField &other) const;

  /*!
   * \brief Returns the name of the field.
   *
   * The string returned is empty if the field is anonymous.
   * \see isAnonymous()
   */
  const std::string& getName() const;

  /*!
   * \brief Returns if the field is an array.
   *
   * If this function returns true, then either isBoundSpecifiedArray() or
   * isUnboundSpecifiedArray() must also return true.
   */
  bool isArray() const;
  /*!
   * \brief Returns if the array size is bounded.
   *
   * \see bool setArraySize(uint64_t size)
   */
  bool isBoundSpecifiedArray() const;
  /*!
   * \brief Returns if the array size is unbounded.
   *
   * \see bool setArraySize(uint64_t size)
   */
  bool isUnboundSpecifiedArray() const;
  /*!
   * \brief Sets the size of the field's array.
   *
   * The following cases exists:
   * - <tt>arraySize < 0 </tt>: means that this field is not an array.
   * - <tt>arraySize == 0</tt>: means that this fields is an unbounded array. I.e isUnboundSpecifiedArray() returns <tt>true</tt>.
   * - <tt>arraySize > 0 </tt>: means that this fields is a bounded array. I.e isBoundSpecifiedArray() returns <tt>true</tt>.
   *
   * In the following code
   * \code{.c}
   * struct s
   * {
   *   int f1;
   *   int f2[10];
   *   int f3[];
   * };
   * \endcode
   * The array size goes as follow:
   * - for field <tt>f1</tt>: the array size must be set to a negative value (e.g. -1)
   * - for field <tt>f2</tt>: the array size must be set to 10
   * - for field <tt>f3</tt>: the array size must be set to 0
   */
  bool setArraySize(uint64_t size);
  /*!
   * \brief Returns the size of the field's array.
   *
   * The array size is negative if the field is not an array.
   *
   * The array size is 0 if the field is an unbounded array.
   *
   * The array size is positive if the field is a bounded array.
   *
   * \see isUnboundSpecifiedArray()
   */
  int64_t getArraySize() const;
  /*!
   * \brief Returns if the field is anonymous.
   *
   * A field is said to be anonymous whenever it has no name.
   *
   * For instance in the following code
   * \code{.c}
   * union u
   * {
   *   uint32_t val;
   *   struct
   *   {
   *     uint8_t b1;
   *     uint8_t b2;
   *     uint8_t b3;
   *     uint8_t b4;
   *   };
   * };
   * \endcode
   * the anonymously typed struct is an anonymous field of union u
   */
  bool isAnonymous() const;

  /*!
   * \copydoc TypeItf::clone
   */
  virtual ComposableField* clone() const;

  virtual ~ComposableField();

private:
  /* Do not make this constant otherwise the object is not copyable anymore */
  std::string m_name;
  int64_t m_arraySize;

  friend void swap(ComposableField &first, ComposableField &second);

  /*
   * I wish I could friend only
   * ComposableType::correctIncompleteType(ComposableType *newPtr, const ComposableType* toReplace);
   * but ComposableType is not complete here. And we can't make it complete
   * because otherwise it would create circular include dependency
   */
  friend class ComposableType; //for updateIncompleteTypePtr
};

#endif /* STRUCTFIELD_H */

