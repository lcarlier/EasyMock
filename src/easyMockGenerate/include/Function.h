/*! \file
 * \brief Contains the class to represent a function.
 */
#ifndef FUNCTION_H
#define FUNCTION_H

#include "TypeItf.h"
#include "ElementToMock.h"
#include "ReturnValue.h"
#include "EasyMock_Hashable.h"
#include "FunctionAttribute.h"

#include <string>

/*!
 * \brief Represents a function.
 *
 * The goal of this class is to provide a common interface to the
 * ::FunctionDeclaration and ::FunctionType classes.
 */
class Function : virtual public EasyMock::Hashable
{
public:
  using Vector = AutoCleanVectorPtr<Function>;
  using AttributesList = std::vector<FunctionAttribute>;

  /*!
   * \brief Creates a new Function object
   * \param p_functionName The name of the function
   * \param p_functionReturnType The return value of the function
   * \param p_functionParameters A Parameter::Vector containing the parameters
   */
  Function(std::string p_functionName, ReturnValue p_functionReturnType, Parameter::Vector p_functionParameters);

  Function(const Function &other) = default;
  Function& operator=(const Function &other) = default;
  Function(Function &&other) = default;
  Function& operator=(Function &&other) = default;

  /*!
   * \brief Returns the name of the function.
   */
  const std::string *getName() const;

  /*!
   * \brief Returns a ReturnValue object describing the return value of the
   * function.
   */
  const ReturnValue *getReturnType() const;

  /*!
   * \brief Returns the string which represents the prototype of the function.
   *
   * The function prototype specifies the function's name, parameters and
   * return type. It doesn't contain function's body.
   */
  std::string getFunctionPrototype() const;

  /*!
   * \copydoc ::Function::getFunctionsParameters()
   */
  const Parameter::Vector& getFunctionsParameters() const;

  /*!
   * \brief Returns a Parameter::Vector containing the list of all the parameters
   * that can be given to the function.
   */
  Parameter::Vector& getFunctionsParameters();

  /*!
   * \brief Returns whether the function is variadic
   *
   * A variadic function takes a variable number of parameters.
   */
  bool isVariadic() const;

  /*!
   * \brief Set whether a function is variadic or not.
   *
   * \see ::Function::isVariadic() const
   */
  void setVariadic(bool value);

  /*!
   * \brief Returns whether the function is inlined.
   *
   * An inline function is a function on which the compiler can perform
   * inline substitution. In this case, the function returns whether the
   * function has been declared with the inline keyword or not.
   */
  bool isInlined() const;

  /*!
   * \brief Sets whether a function is inlined.
   *
   * \see ::Function::isInlined() const
   */
  void setInlined(bool value);

  /*!
   * \brief Returns whether a function is static.
   */
  bool isStatic() const noexcept;

  /*!
   * \brief Sets whether a function is static.
   *
   * \see ::Function::isStatic() const
   */
  void setIsStatic(bool value) noexcept;

  /*!
   * \brief Returns the place where the function has been declared.
   *
   * If nothing has been set by ::Function:setOriginFile(std::string), this function returns an empty string.
   */
  const std::string& getOriginFile() const noexcept;

  /*!
   * \brief Sets the place where the function has been declared.
   *
   * \see ::Function::getOriginFile() const
   */
  void setOriginFile(std::string originFile) noexcept;

  bool operator==(const Function &other) const;
  bool operator!=(const Function &other) const;

  /*!
   * \copydoc ::TypeItf::clone
   */
  virtual Function* clone() const;

  /*!
   * \copydoc ::EasyMock::Hashable::getHash()
   */
  std::size_t getHash() const override;

  /*!
   * \brief Returns the hash of the function where all typedefs of the return value and parameter have been removed.
   *
   * In the following example
   *
   * \code{.cpp}
   *
   * typedef int int_t;
   *
   * void foo(int_t a);
   * void foo(int a);
   * \endcode
   *
   * both version of foo returns the same raw hash while the ::Function::getHash() returns different values
   */
  std::size_t getRawHash() const noexcept;

  /*!
   * \brief Adds a function attribute to the function.
   * \param p_attribute The ::FunctionAttribute object to add.
   */
  void addAttribute(FunctionAttribute p_attribute);

  /*!
   * \brief Gets the function attributes the function has.
   * \return The function attributes the function has.
   */
  const AttributesList& getAttributes() const;

protected:
  std::string m_name;
  Parameter::Vector m_parameters;
  ReturnValue m_returnType;
  AttributesList  m_attributes;
  bool m_isVariadic;
  bool m_isInlined;
  bool m_isStatic;
  std::string m_originFile;
};

#endif /* FUNCTION_H */
