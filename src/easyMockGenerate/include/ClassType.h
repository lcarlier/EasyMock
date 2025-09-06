/*! \file
 *
 * \brief Contains the class to represent a class.
 */
#ifndef EASYMOCK_CLASSTYPE_H
#define EASYMOCK_CLASSTYPE_H

#include <memory>

#include "ComposableType.h"

struct Namespace;

class ClassType: public ComposableType
{
public:
  /*!
   * \brief Creates a new ClassType.
   *
   * \param p_name The name of the class.
   * \param p_is_embedded_in_other_type Specifies whether the type is embedded in another type or not. See ::ComposableType::isDeclarationEmbeddedInOtherType().
   */
  ClassType(std::string p_name, bool p_is_embedded_in_other_type);

  /*!
   * \brief Creates a new ClassType.
   *
   * \param p_name The name of the class.
   * \param p_is_embedded_in_other_type Specifies whether the type is embedded in another type or not. See ::ComposableType::isDeclarationEmbeddedInOtherType().
   * \param p_namespace The namespace in which the class belongs to
   */
  ClassType(std::string p_name, bool p_is_embedded_in_other_type, std::shared_ptr<const Namespace> p_namespace);

  /*!
  * \brief Creates a new ClassType.
  *
  * \param p_name See ::ClassType::ClassType(const std::string p_name,bool p_is_embedded_in_other_type).
  * \param p_elem A ::ComposableType::ComposableFieldTypeVector which contains all the fields of the class.
  * \param p_is_embedded_in_other_type See ::ClassType::ClassType(const std::string p_name,bool p_is_embedded_in_other_type).
  */
  ClassType(std::string p_name, ComposableType::ComposableFieldTypeVector p_elem, bool p_is_embedded_in_other_type);

  /*!
  * \brief Creates a new ClassType.
  *
  * \param p_name See ::ClassType::ClassType(const std::string p_name,bool p_is_embedded_in_other_type).
  * \param p_elem A ::ComposableType::ComposableFieldTypeVector which contains all the fields of the class.
  * \param p_is_embedded_in_other_type See ::ClassType::ClassType(const std::string p_name,bool p_is_embedded_in_other_type).
  * \param p_namespace The namespace in which the class belongs to
  */
  ClassType(std::string p_name, ComposableType::ComposableFieldTypeVector p_elem, bool p_is_embedded_in_other_type, std::shared_ptr<const Namespace> p_namespace);

  /*!
   * \copydoc ComposableType::getComposableTypeKeyword
   */
  const char* getComposableTypeKeyword() const override;

  ~ClassType() = default;

  ClassType(const ClassType& other) = delete;
  ClassType& operator=(const ClassType& other) = delete;
  ClassType(ClassType &&other) = default;
  ClassType& operator=(ClassType &&other) = default;
};

#endif //EASYMOCK_CLASSTYPE_H
