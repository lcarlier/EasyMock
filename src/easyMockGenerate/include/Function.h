/*! \file
 * \brief Contains the class to represent a function.
 */
#ifndef FUNCTION_H
#define FUNCTION_H

#include "TypeItf.h"
#include "ElementToMock.h"
#include "ReturnValue.h"

#include <string>

/*!
 * \brief Represents a function.
 *
 * The goal of this class is to provide a common interface to the
 * FunctionDeclaration and FunctionType classes.
 */
class Function
{
public:
  typedef AutoCleanVectorPtr<ElementToMock> Vector;

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
   * \brief Returns whether a function is inlined.
   *
   * \see ::Function::isInlined() const
   */
  void setInlined(bool value);

  bool operator==(const Function &other) const;
  bool operator!=(const Function &other) const;

  virtual Function* clone() const;

private:
  std::string m_name;
  Parameter::Vector m_parameters;
  ReturnValue m_returnType;
  bool m_isVariadic;
  bool m_isInlined;
};

#endif /* FUNCTION_H */

