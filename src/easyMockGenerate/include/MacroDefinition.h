/*! \file
 * \brief Contains the class to represent a macro definition.
 */
#ifndef EASYMOCK_MACRODEFINITION_H
#define EASYMOCK_MACRODEFINITION_H

#include <vector>
#include <string>

/*!
 * \brief Represents a macro definition.
 */
class MacroDefinition
{
public:
  using ParameterList = std::vector<std::string>;

  /*!
   * \copydoc ElementToMockContext::addMacroDefine(std::string, std::string)
   */
  MacroDefinition(std::string name, std::string definition);

  /*!
   * \copydoc ElementToMockContext::addMacroDefine(std::string, std::vector<std::string>, std::string)
   */
  MacroDefinition(std::string name, std::vector<std::string> parameters, std::string definition);

  /*!
   * \brief Returns the ID of the macro
   */
  const std::string& getId() const noexcept;

  /*!
   * \brief Returns the parameters list of the macro.
   *
   * The list will be empty if the macro doesn't have any parameter.
   */
  const ParameterList& getParameters() const noexcept;

  /*!
   * \brief Returns the string definition of the macro.
   */
  const std::string& getDefinition() const noexcept;
private:
  std::string m_name;
  ParameterList m_parameters;
  std::string m_definition;
};

#endif //EASYMOCK_MACRODEFINITION_H
