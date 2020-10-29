/*! \file
 * \brief Contains the class to represent an incomplete type
 */
#include "TypeItf.h"

#include <string>

#ifndef INCOMPLETETYPE_H
#define INCOMPLETETYPE_H

/*!
 * \brief Represents an incomplete type
 *
 * An incomplete type is a type which is either
 * - forward declared
 * - used recursively as a struct or union member type;
 */
class IncompleteType : public TypeItf {
public:
  /*!
   * \brief Creates a new ::IncompleteType instance

   *
   * To represent the following structure
   * \code{.c}
   * struct s
   * {
   *   struct s* s1;
   * };
   * void foo(struct s param);
   * \endcode
   * The following code can be used
   * \code{.cpp}
   * //Create the StructType object;
   * StructType *sStructType = new StructType("s");
   *
   * sStructType->addField(new ComposableField(new IncompleteType(*sStructType)));
   *
   * //Add the StructType object to a parameter.
   * Parameter *p = new Parameter(sStructType, "param");
   *
   * //Create the function on the stack. When the variable goes out of scope,
   * //all the memory is cleaned up
   * Function f("foo", new ReturnValue(new CType(CTYPE_VOID)), Parameter::Vector({p}));
   * \endcode
   *
   * Similar code can be used to represent forward declared types.
   */
  IncompleteType(const TypeItf& p_type);

  /*!
   * \copydoc TypeItf::clone
   */
  IncompleteType *clone() const override;
  ~IncompleteType();
};

#endif /* INCOMPLETETYPE_H */

