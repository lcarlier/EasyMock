/*! \file
 * \brief Contains the struct to represent a namespace.
 */
#ifndef EASYMOCK_NAMESPACE_H
#define EASYMOCK_NAMESPACE_H

#include <string>
#include <memory>

/*!
 * \brief Represents a namespace.
 *
 * Namespace hierarchy can be representing by using the ::Namespace::m_parent member.
 */
struct Namespace
{
  /*!
   * \brief Create a new namespace under the global namespace
   * \param p_name The name of the namespace
   */
  explicit Namespace(std::string p_name);

  /*!
   * \brief Create a new namespace under a specific parent namespace
   * \param p_name The name of the namespace
   * \param p_parent Pointer to the namespace containing this namespace
   */
  Namespace(std::string p_name, std::shared_ptr<const Namespace> p_parent);

  /*!
   * \brief Return whether a namespace is global
   *
   * \return True if the namespace is global. False instead.
   *
   * A namespace is said to be global if `::Namespace::m_parent == nullptr`
   */
  bool isGlobal() const;

  bool operator==(const Namespace& other) const;
  bool operator!=(const Namespace& other) const;

  /*!
   * \brief The name of the namespace
   */
  std::string m_name;

  /*!
   * \brief Pointer to the namespace containing this namespace.
   */
  std::shared_ptr<const Namespace> m_parent;
};

/*!
 * \brief Returns the object representing the shared global namespace
 */
std::shared_ptr<const Namespace> getGlobalNamespace();

#endif //EASYMOCK_NAMESPACE_H
