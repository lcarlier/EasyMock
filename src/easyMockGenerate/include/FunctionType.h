/*! \file
 * \brief Contains the class to represent a function type.
 */
#ifndef FUNCTIONTYPE_H
#define FUNCTIONTYPE_H

#include "Function.h"
#include "TypeItf.h"

/*!
 * \brief Represents a function type.
 *
 * This class can be used to represent a pointer to a function with the
 * usage combination of the Pointer class.
 *
 * This pointer to a function can then be used to represents function's
 * parameters, or structure/union fields.
 */
class FunctionType : public Function, public TypeItf {
public:
  /*!
   * \brief Creates a new FunctionType object

   * \param p_functionReturnType The return value of the function
   * \param p_functionParameters A Parameter::Vector containing the parameters
   */
  FunctionType(ReturnValue p_functionReturnType, Parameter::Vector p_functionParameters);

  FunctionType(const FunctionType &other) = delete;
  FunctionType& operator=(const FunctionType &other) = delete;
  FunctionType(FunctionType &&other) = default;
  FunctionType& operator=(FunctionType &&other) = default;

  /*!
   * \copydoc ::TypeItf::getDeclarationPrefix
   */
  virtual std::string getDeclarationPrefix(bool p_naked = false) const override;

  /*!
   * \copydoc ::TypeItf::getDeclarationPostfix
   */
  virtual std::string getDeclarationPostfix(bool p_naked = false) const override;

  bool operator==(const FunctionType &p_other) const;
  bool operator!=(const FunctionType &p_other) const;

  /*!
   * \copydoc ::EasyMock::Hashable::getHash()
   */
  std::size_t getHash() const noexcept override;

  /*!
   * \copydoc ::EasyMock::Hashable::cacheHash()
   */
  void cacheHash() noexcept override;

  virtual ~FunctionType();

protected:
  bool isEqual(const TypeItf &p_other) const override;

private:
  std::size_t m_cachedHash;
};

#endif /* FUNCTIONTYPE_H */
