/*! \file
 *
 * \brief Contains the class to represent an union.
 */
#ifndef UNIONTYPE_HPP
#define UNIONTYPE_HPP

#include "ComposableType.h"

/*!
 * \brief Represents an union type.
 */
class UnionType : public ComposableType {
public:
  /*!
   * \brief Creates a new UnionType.
   *
   * \param p_name The name of the union.
   * \param p_is_embedded_in_other_type Specifies whether the type is embedded in another type or not. See ComposableType::isDeclarationEmbeddedInOtherType().
   */
  UnionType(const std::string p_name, bool p_is_embedded_in_other_type);

  /*!
   * \brief Creates a new UnionType.
   *
   * \param p_name See UnionType(const std::string p_name,bool p_is_embedded_in_other_type).
   * \param p_elem A ComposableFieldItf::Vector which contains all the fields of the union.
   * \param p_is_embedded_in_other_type See UnionType(const std::string p_name,bool p_is_embedded_in_other_type).
   */
  UnionType(const std::string p_name, const ComposableFieldItf::Vector p_elem, bool p_is_embedded_in_other_type);

  /*!
   * \copydoc ComposableType::getComposableTypeKeyword
   */
  const char* getComposableTypeKeyword() const override;

  /*!
   * \copydoc TypeItf::clone()
   */
  UnionType* clone() const override;

  virtual ~UnionType();
};

#endif /* UNIONTYPE_HPP */

