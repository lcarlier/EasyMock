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
#include <memory>
#include <vector>

class ComposableType;

/*!
 * \brief Represents a function.
 *
 * The goal of this class is to provide a common interface to the
 * ::FunctionDeclaration and ::FunctionType classes.
 */
enum class FunctionAccessSpecifier
{
  NA, // e.g. for C function
  PUBLIC,
  PRIVATE,
  PROTECTED
};

class Function : virtual public EasyMock::Hashable
{
public:
  using AttributesList = std::vector<FunctionAttribute>;

  /*!
   * \brief Creates a new Function object
   * \param p_functionName The name of the function
   * \param p_functionReturnType The return value of the function
   * \param p_functionParameters A Parameter::Vector containing the parameters
   * \param p_parentData A weak_ptr to the composable type (i.e the struct or class) containing this function. If the reference counter goes to 0, the function will not belong to the class anymore.
   */
  Function(std::string p_functionName, ReturnValue p_functionReturnType, Parameter::Vector p_functionParameters, std::weak_ptr<const ComposableType> p_parentData = {});

  Function(const Function &other) = delete;
  Function& operator=(const Function &other) = delete;
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
  const ReturnValue *getReturnValue() const;

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

  /*!
   * \brief Get the access specifier of the function (i.e. public, protected, private)
   *
   * \return The enum representing the access specifier
   */
  FunctionAccessSpecifier getAccessSpecifier() const noexcept;

  /*!
   * \copydoc getAccessSpecifier() const
   */
  const std::string& getAccessSpecifierStr() const noexcept;

  /*!
   * \brief Set the access specifier of the function within its class
   * @param p_accessSpecifier The enum representing the access specifier
   */
  void setAccessSpecifier(FunctionAccessSpecifier p_accessSpecifier) noexcept;

  /*!
   * \brief Set whether a function is const qualified in a class
   * \param p_value True if the class is cons qualified, false instead
   */
  void setClassConst(bool p_value) noexcept;

  /*!
   * \brief Get whether a function is const qualified in a class
   * \return True if the class is cons qualified, false instead
   */
  bool isClassConst() const noexcept;

  bool operator==(const Function &other) const;
  bool operator!=(const Function &other) const;

  /*!
   * \copydoc ::EasyMock::Hashable::getHash()
   */
  std::size_t getHash() const noexcept override;

  /*!
   * \copydoc ::EasyMock::Hashable::cacheHash()
   *
   * The same rules applies for the hash returned by getRawHash()
   */
  void cacheHash() noexcept override;

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

  /*!
   * \brief Returns the "parent data" i.e. the struct or class in which this function belongs to
   */
  std::shared_ptr<const ComposableType> getParentData() const;

  bool isMemberClass() const;


protected:
  std::string m_name;
  Parameter::Vector m_parameters;
  ReturnValue m_returnType;
  AttributesList  m_attributes;
  bool m_isVariadic;
  bool m_isInlined;
  bool m_isStatic;
  std::string m_originFile;
  /*!
   * \brief Contains the "parent data" i.e. the struct or class in which this function belongs to
   */
  std::weak_ptr<const ComposableType> m_parentData;
  FunctionAccessSpecifier m_accessSpecifier;
  bool m_isClassConst;
private:
  std::size_t m_cachedHash;
  std::size_t m_cachedRawHash;
};

#endif /* FUNCTION_H */
