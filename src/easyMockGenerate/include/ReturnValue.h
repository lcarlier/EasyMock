/*! @file
 *
 * \brief Contains the class to represent a return value.
 */
#ifndef RETURNVALUE_H
#define RETURNVALUE_H

#include <string>
#include <EasyMockGenerateTypes.h>
#include "Declarator.h"

//Forward declare to avoid cycle dependencies
class TypeItf;
class StructType;

/*!
 * \brief Represents a function's return value.
 *
 * For instance, in the following code
 * \code{.c}
 * void foo();
 * int bar();
 * \endcode
 * The following elements are represented by the ReturnValue class
 * - <tt>void</tt>
 * - <tt>int</tt>
 */
class ReturnValue : public Declarator
{
public:
  /*!
   * \brief Creates a new ReturnValue object.
   *
   * \param p_type The type of the return value.
   * \see TypeItf
   */
  explicit ReturnValue(std::shared_ptr<TypeItf> p_type);

  ReturnValue(const ReturnValue &other) = delete;
  ReturnValue& operator=(const ReturnValue &other) = delete;
  ReturnValue(ReturnValue &&other) = default;
  ReturnValue& operator=(ReturnValue &&other) = default;

  /*!
   * \brief Compares 2 ReturnValue objects.
   *
   * \copydetails Declarator::operator==()
   */
  bool operator==(const ReturnValue &other) const;
  bool operator!=(const ReturnValue &other) const;

  virtual ~ReturnValue();
private:
  /*!
   * \copydoc ::Declarator::isEqual
   */
  bool isEqual(const Declarator& p_other) const override;
  friend void swap(ReturnValue &first, ReturnValue &second);
};

ReturnValue VoidReturnValue(bool p_isPointer = false);
ReturnValue TypedReturnValue(easyMock_cTypes_t p_type, bool p_isPointer = false);
ReturnValue StructReturnValue(std::shared_ptr<StructType> type, bool p_isPointer = false);

#endif /* RETURNVALUE_H */
