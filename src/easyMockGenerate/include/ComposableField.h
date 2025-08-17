/*! \file
 *
 * \brief Contains the class to represent fields of composed type such as struct and union.
 */
#ifndef COMPOSABLEFIELD_H
#define COMPOSABLEFIELD_H

#include <string>
#include <cstdint>

#include "EasyMockGenerateTypes.h"
#include "ComposableFieldItf.h"

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
 * \see ::ComposableField::ComposableField(std::shared_ptr<TypeItf>,std::string,attributes)
 */
class ComposableField : public ComposableFieldItf
{
public:

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
  ComposableField(std::shared_ptr<TypeItf> p_type, std::string p_name);
  /*!
   * \brief Creates a new ComposableField
   *
   * It is possible to represent forward declared type or recursively used
   * type by using the ::IncompleteType class
   */
  ComposableField(std::shared_ptr<TypeItf> p_type, std::string p_name, attributes p_attrib);

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

  ComposableField(const ComposableField &other) = delete;
  ComposableField &operator=(const ComposableField& other) = delete;
  ComposableField(ComposableField &&other) = default;
  ComposableField& operator=(ComposableField &&other) = default;
  /*!
   * \brief Compares 2 ComposableField objects.
   *
   * \copydetails ::Declarator::operator==()
   */
  bool operator==(const ComposableField &other) const;
  bool operator!=(const ComposableField &other) const;

  bool isComposableField() const override;

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
   * \copydoc ::EasyMock::Hashable::getHash()
   */
  std::size_t getHash() const noexcept override;

  /*!
   * \copydoc ::EasyMock::Hashable::cacheHash()
   */
  void cacheHash() noexcept override;

  virtual ~ComposableField() override;

private:
  /*!
   * \copydoc ::Declarator::isEqual
   */
  bool isEqual(const Declarator& p_other) const override;

  int64_t m_arraySize;
  std::size_t m_cachedHash;
};

#endif /* STRUCTFIELD_H */
