/*! \file
 * \brief Contains the class to represent a function declaration.
 */
#ifndef FUNCTIONDECLARATION_H
#define FUNCTIONDECLARATION_H

#include "ElementToMock.h"
#include "Function.h"

/*!
 * \brief Represents a function declaration.
 *
 * This class represents a declaration as opposed to a type which is
 * represented by the FunctionType class.
 */
class FunctionDeclaration : public Function, public ElementToMock {
public:
  /*!
   * \brief Creates a new function declaration object.
   * \copydetails Function
   */
  FunctionDeclaration(std::string p_functionName, ReturnValue p_functionReturnType, Parameter::Vector p_functionParameters);

  /*!
   * \copybrief Function
   *
   * This implementation returns ::ETS_function from the ::ElementToMock_Type enum.
   */
  ElementToMock_Type getMockType() const override;

  FunctionDeclaration(const FunctionDeclaration &other) = delete;
  FunctionDeclaration& operator=(const FunctionDeclaration &other) = delete;
  FunctionDeclaration(FunctionDeclaration &&other) = default;
  FunctionDeclaration& operator=(FunctionDeclaration &&other) = default;

  bool operator==(const FunctionDeclaration &other) const;
  bool operator!=(const FunctionDeclaration &other) const;

  /*!
   * \brief Returns whether the function is declared with its body.
   */
  bool doesThisDeclarationHasABody() const noexcept;

  /*!
   * \brief Sets whether the function is declared with its body.
   */
  void setDoesThisDeclarationHasABody(bool val) noexcept;

  /*!
   * \copydoc ::EasyMock::Hashable::getHash()
   */
  std::size_t getHash() const noexcept override;

  /*!
   * \copydoc ::EasyMock::Hashable::cacheHash()
   */
  void cacheHash() noexcept override;

  virtual ~FunctionDeclaration();
  static const FunctionDeclaration& toFunctionDeclaration(const ElementToMock& elem)
  {
    return dynamic_cast<const FunctionDeclaration&>(elem);
  }
private:
  bool m_doesThisDeclarationHasBody;
  std::size_t m_cachedHash;
};

#endif /* FUNCTIONDECLARATION_H */
