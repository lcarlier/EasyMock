/*! \file
 *
 * \brief Contains the class to represent an union.
 */
#ifndef UNIONTYPE_HPP
#define UNIONTYPE_HPP

#include <memory>

#include "ComposableType.h"

struct Namespace;

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
  UnionType(std::string p_name, bool p_is_embedded_in_other_type);

  /*!
   * \brief Creates a new UnionType.
   *
   * \param p_name The name of the union.
   * \param p_is_embedded_in_other_type Specifies whether the type is embedded in another type or not. See ComposableType::isDeclarationEmbeddedInOtherType().
   * \param p_namespace The namespace in which the struct belongs to.
   */
  UnionType(std::string p_name, bool p_is_embedded_in_other_type, std::shared_ptr<const Namespace> p_namespace);

  /*!
   * \brief Creates a new UnionType.
   *
   * \param p_name See ::UnionType::UnionType(std::string, bool).
   * \param p_elem A ::ComposableType::ComposableFieldTypeVector which contains all the fields of the union.
   * \param p_is_embedded_in_other_type See ::UnionType::UnionType(std::string, bool).
   */
  UnionType(std::string p_name, ComposableType::ComposableFieldTypeVector p_elem, bool p_is_embedded_in_other_type);

  /*!
   * \brief Creates a new UnionType.
   *
   * \param p_name See ::UnionType::UnionType(std::string, bool).
   * \param p_elem A ::ComposableType::ComposableFieldTypeVector which contains all the fields of the union.
   * \param p_is_embedded_in_other_type See ::UnionType::UnionType(std::string, bool).
   * \param p_namespace The namespace in which the struct belongs to.
   */
  UnionType(std::string p_name, ComposableType::ComposableFieldTypeVector p_elem, bool p_is_embedded_in_other_type, std::shared_ptr<const Namespace> p_namespace);

  /*!
   * \copydoc ComposableType::getComposableTypeKeyword
   */
  const char* getComposableTypeKeyword() const override;

  UnionType(const UnionType& other) = delete;
  UnionType& operator=(const UnionType& other) = delete;
  UnionType(UnionType &&other) = default;
  UnionType& operator=(UnionType &&other) = default;

  virtual ~UnionType();
};

#endif /* UNIONTYPE_HPP */
