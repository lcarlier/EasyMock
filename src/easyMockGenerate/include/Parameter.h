/*! @file
 *
 * \brief Contains the class to represents a function parameter.
 */
#ifndef PARAMETER_H
#define PARAMETER_H

#include <string>
#include <memory>
#include <vector>

#include "EasyMockGenerateTypes.h"
#include "ComposableType.h"
#include "Declarator.h"

/*!
 * \brief Represents a function parameter.
 *
 * For instance, in the following code
 * \code{.c}
 * void foo(int p1, float p2);
 * \endcode
 * The following elements are represented by the Parameter class
 * - <tt>int p1</tt>
 * - <tt>float p2</tt>
 */
class Parameter : public Declarator
{
public:
  /*!
   * \brief Creates a new Parameter object.
   *
   * \param p_type The type of the parameter
   * \param p_name The name of the parameter
   */
  Parameter(std::shared_ptr<TypeItf> p_type, std::string p_name);

  /*!
   * \brief An std::vector containing Parameter objects
   */
  typedef std::vector<Parameter> Vector;

  Parameter(const Parameter &other) = delete;
  Parameter& operator=(const Parameter &other) = delete;
  Parameter(Parameter &&other) = default;
  Parameter& operator=(Parameter &&other) = default;

  /*!
   * \brief Compare if 2 Parameter objects are equals.
   *
   * \copydetails Declarator::operator==()
   */
  bool operator==(const Parameter &other) const;
  bool operator!=(const Parameter &other) const;

  /*!
   * \return The name of the Parameter
   */
  const std::string &getName() const;

  virtual ~Parameter();

  /*!
   * \copydoc ::EasyMock::Hashable::getHash()
   */
  std::size_t getHash() const noexcept override;

private:
  /*!
   * \copydoc ::Declarator::isEqual
   */
  bool isEqual(const Declarator& p_other) const override;
  /* Do not make the member const otherwise they are not copyable anymore */
  std::string m_name;

  friend void swap(Parameter &first, Parameter &second);
};

Parameter VoidParameter(std::string p_name);
Parameter NamedParameter(easyMock_cTypes_t p_type, std::string p_name, bool p_isPointer = false);
Parameter StructParameter(std::string type, std::string name, ComposableType::ComposableFieldTypeVector elem, bool p_is_embedded_in_other_type);


#endif /* PARAMETER_H */
