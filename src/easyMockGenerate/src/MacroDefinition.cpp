#include <MacroDefinition.h>

MacroDefinition::MacroDefinition(std::string name, std::string definition):
MacroDefinition(std::move(name), std::vector<std::string>{}, std::move(definition))
{}

MacroDefinition::MacroDefinition(std::string name, ParameterList parameters, std::string definition):
MacroDefinition{std::move(name), std::move(parameters), std::move(definition), std::string{}}
{}

MacroDefinition::MacroDefinition(std::string name, ParameterList parameters, std::string definition, std::string fromFile):
m_name(std::move(name)), m_parameters(std::move(parameters)), m_definition(std::move(definition)), m_originFile{std::move(fromFile)}
{}

const std::string& MacroDefinition::getId() const noexcept
{
  return m_name;
}

const MacroDefinition::ParameterList& MacroDefinition::getParameters() const noexcept
{
  return m_parameters;
}

const bool MacroDefinition::hasParameters() const noexcept
{
  return !m_parameters.empty();
}

const std::string& MacroDefinition::getDefinition() const noexcept
{
  return m_definition;
}

const ::std::string& MacroDefinition::getOriginFile() const noexcept
{
  return m_originFile;
}
