#include <MacroDefinition.h>

MacroDefinition::MacroDefinition(std::string name, std::string definition):
MacroDefinition(std::move(name), std::vector<std::string>{}, std::move(definition))
{}

MacroDefinition::MacroDefinition(std::string name, ParameterList parameters, std::string definition):
m_name(std::move(name)), m_parameters(std::move(parameters)), m_definition(std::move(definition))
{}

const std::string& MacroDefinition::getId() const noexcept
{
  return m_name;
}

const MacroDefinition::ParameterList& MacroDefinition::getParameters() const noexcept
{
  return m_parameters;
}

const std::string& MacroDefinition::getDefinition() const noexcept
{
  return m_definition;
}
