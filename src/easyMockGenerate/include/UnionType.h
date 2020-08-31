/*! \file
 *
 * \brief Contains the class to represent an union.
 */
#ifndef UNIONTYPE_HPP
#define UNIONTYPE_HPP

#include "ComposableType.h"

/*!
 * This class represents an union type.
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
   * \param p_type_def_name The typedef that aliases this union.
   * \param p_is_embedded_in_other_type See UnionType(const std::string,bool).
   */
  UnionType(const std::string p_name, const std::string p_type_def_name, bool p_is_embedded_in_other_type);
  /*!
   * \brief Creates a new UnionType.
   *
   * \param p_name See UnionType(const std::string p_name,bool p_is_embedded_in_other_type).
   * \param p_elem A ComposableField::Vector which contains all the fields of the union.
   * \param p_is_embedded_in_other_type See UnionType(const std::string p_name,bool p_is_embedded_in_other_type).
   */
  UnionType(const std::string p_name, const ComposableField::Vector p_elem, bool p_is_embedded_in_other_type);
  /*!
   * \brief Creates a new UnionType.
   *
   * \param p_name See UnionType(const std::string p_name,bool p_is_embedded_in_other_type).
   * \param p_type_def_name See UnionType(const std::string p_name, const std::string p_type_def_name, bool p_is_embedded_in_other_type).
   * \param p_elem See UnionType(const std::string p_name, const ComposableField::Vector p_elem, bool p_is_embedded_in_other_type).
   * \param p_is_embedded_in_other_type See UnionType(const std::string p_name,bool p_is_embedded_in_other_type).
   */
  UnionType(const std::string p_name, const std::string p_type_def_name, const ComposableField::Vector p_elem, bool p_is_embedded_in_other_type);

  /*!
   * \copydoc TypeItf::clone()
   */
  UnionType* clone() const override;

  virtual ~UnionType();
};

#endif /* UNIONTYPE_HPP */

