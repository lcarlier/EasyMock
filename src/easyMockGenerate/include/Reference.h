/*! @file
 *
 * \brief Contains the class to represent a pointer.
 */
#ifndef EASYMOCK_REFERENCE_H
#define EASYMOCK_REFERENCE_H

#include "Pointer.h"

/*!
 * \brief Represents a Reference.
 *
 * For instance, the following declaration are to be represented by a Reference
 * object
 * @code{.cpp}
 * int& a;
 * const int& b;
 * @endcode
 *
 * This object behave the same as the ::Pointer object.
 *
 * \see ::Pointer
 */
class Reference: public Pointer
{
public:
  Reference(std::shared_ptr<TypeItf> p_type);

  Reference(const Reference &other) = delete;
  Reference& operator=(const Reference& other) = delete;
  Reference(Reference &&other) = default;
  Reference& operator=(Reference &&other) = default;

  virtual std::string getDeclarationPrefix(bool p_naked = false) const override;
protected:
  bool isEqual(const TypeItf& p_other) const override;
};

#endif //EASYMOCK_REFERENCE_H
