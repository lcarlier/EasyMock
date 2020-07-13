/*! \file
 *
 * \brief Contains the class to represent a struct.
 */
#ifndef STRUCTTYPE_H
#define STRUCTTYPE_H

#include "ComposableType.h"

/*!
 * This class represents a struct type.
 */
class StructType : public ComposableType
{
public:
  /*!
   * \brief Creates a new StructType.
   *
   * \param p_name The name of the struct.
   * \param p_is_embedded_in_other_type Specifies whether the type is embedded in another type or not. See ComposableType::isEmbeddedInOtherType().
   */
  StructType(const std::string p_name, bool p_is_embedded_in_other_type);
  /*!
   * \brief Creates a new StructType.
   *
   * \param p_name See StructType(const std::string p_name,bool p_is_embedded_in_other_type).
   * \param p_type_def_name The typedef that aliases this struct.
   * \param p_is_embedded_in_other_type See StructType(const std::string,bool).
   */
  StructType(const std::string p_name, const std::string p_type_def_name, bool p_is_embedded_in_other_type);
   /*!
   * \brief Creates a new StructType.
   *
   * \param p_name See StructType(const std::string p_name,bool p_is_embedded_in_other_type).
   * \param p_elem A ComposableField::Vector which contains all the fields of the struct.
   * \param p_is_embedded_in_other_type See StructType(const std::string p_name,bool p_is_embedded_in_other_type).
   */
  StructType(const std::string p_name, const ComposableField::Vector p_elem, bool p_is_embedded_in_other_type);
  /*!
   * \brief Creates a new StructType.
   *
   * \param p_name See StructType(const std::string p_name,bool p_is_embedded_in_other_type).
   * \param p_type_def_name See StructType(const std::string p_name, const std::string p_type_def_name, bool p_is_embedded_in_other_type).
   * \param p_elem See StructType(const std::string p_name, const ComposableField::Vector p_elem, bool p_is_embedded_in_other_type).
   * \param p_is_embedded_in_other_type See StructType(const std::string p_name,bool p_is_embedded_in_other_type).
   */
  StructType(const std::string p_name, const std::string p_type_def_name, const ComposableField::Vector p_elem, bool p_is_embedded_in_other_type);
  virtual ~StructType();

  /*!
   * \copydoc TypeItf::clone()
   */
  StructType* clone() const override;

  StructType(const StructType& other) = default;
  StructType& operator=(const StructType& other) = default;
  StructType(StructType &&other) = default;
};

#endif /* STRUCTTYPE_H */

