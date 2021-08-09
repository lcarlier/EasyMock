/*! \file
 * \brief Contains the class to represent a function attribute.
 */
#ifndef EASYMOCK_FUNCTIONATTRIBUTE_H
#define EASYMOCK_FUNCTIONATTRIBUTE_H

#include <EasyMock_Hashable.h>

#include <string>
#include <vector>

/*!
 * \brief Class representing a function attribute.
 *
 * An example of a function attribute is
 *
 * \code{.c}
 * __attribute__((format(printf, 1, 2)))
 * \endcode
 */
class FunctionAttribute: public EasyMock::Hashable
{
public:
  /*!
   * \brief Type holding a list of parameters of function attribute.
   *
   * In the following function attribute
   *
   * \code{.c}
   * __attribute__((format(printf, 1, 2)))
   * \endcode
   *
   * The parameters are `printf`, `1` and `2`.
   */
  using ParametersList = std::vector<std::string>;

  /*!
   * \brief Creates a function attribute that doesn't have any parameter.
   * \param p_name The name of the function attribute.
   */
  FunctionAttribute(std::string p_name);

  /*!
   * \brief Creates a function attribute with parameters.
   * \param p_name The name of the function attribute.
   * \param p_parameters The list of parameters' value that the attribute has.
   */
  FunctionAttribute(std::string p_name, ParametersList p_parameters);

  /*!
   * \brief Get the name of the function attribute.
   * \return The name of the function attribute.
   */
  const std::string& getName() const;

  /*!
   * \brief Get the parameters' value of the function attribute.
   * \return The parameters' value of the function attribute.
   */
  const ParametersList& getParameters() const;

  bool operator==(const FunctionAttribute& other) const;
  bool operator!=(const FunctionAttribute& other) const;

  /*!
   * \copydoc ::EasyMock::Hashable::getHash()
   */
  std::size_t getHash() const override;

private:
  std::string m_name;
  ParametersList m_parameters;
};

#endif //EASYMOCK_FUNCTIONATTRIBUTE_H
