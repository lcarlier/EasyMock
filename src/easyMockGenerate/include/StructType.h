/*! \file
 *
 * \brief Contains the class to represent a struct.
 */
#ifndef STRUCTTYPE_H
#define STRUCTTYPE_H

#include <memory>

#include "ComposableType.h"

struct Namespace;

/*!
 * \brief Represents a struct type.
 */
class StructType : public ComposableType
{
public:
  /*!
   * \brief Creates a new StructType.
   *
   * \param p_name The name of the struct.
   * \param p_is_embedded_in_other_type Specifies whether the type is embedded in another type or not. See ::ComposableType::isDeclarationEmbeddedInOtherType().
   */
  StructType(std::string p_name, bool p_is_embedded_in_other_type);

  /*!
   * \brief Creates a new StructType.
   *
   * \param p_name The name of the struct.
   * \param p_is_embedded_in_other_type Specifies whether the type is embedded in another type or not. See ::ComposableType::isDeclarationEmbeddedInOtherType().
   * \param p_namespace The namespace in which the struct belongs to.
   */
  StructType(std::string p_name, bool p_is_embedded_in_other_type, std::shared_ptr<const Namespace> p_namespace);

   /*!
   * \brief Creates a new StructType.
   *
   * \param p_name See ::StructType::StructType(const std::string p_name,bool p_is_embedded_in_other_type).
   * \param p_elem A ::ComposableType::ComposableFieldTypeVector which contains all the fields of the struct.
   * \param p_is_embedded_in_other_type See ::StructType::StructType(const std::string p_name,bool p_is_embedded_in_other_type).
   */
  StructType(std::string p_name, ComposableType::ComposableFieldTypeVector p_elem, bool p_is_embedded_in_other_type);

  /*!
   * \brief Creates a new StructType.
   *
   * \param p_name See ::StructType::StructType(const std::string p_name,bool p_is_embedded_in_other_type).
   * \param p_elem A ::ComposableType::ComposableFieldTypeVector which contains all the fields of the struct.
   * \param p_is_embedded_in_other_type See ::StructType::StructType(const std::string p_name,bool p_is_embedded_in_other_type).
   * \param p_namespace The namespace in which the struct belongs to.
   */
    StructType(std::string p_name, ComposableType::ComposableFieldTypeVector p_elem, bool p_is_embedded_in_other_type, std::shared_ptr<const Namespace> p_namespace);

  /*!
   * \copydoc ComposableType::getComposableTypeKeyword
   */
  const char* getComposableTypeKeyword() const override;
  ~StructType() = default;

  StructType(const StructType& other) = delete;
  StructType& operator=(const StructType& other) = delete;
  StructType(StructType &&other) = default;
  StructType& operator=(StructType &&other) = default;
};

#endif /* STRUCTTYPE_H */
