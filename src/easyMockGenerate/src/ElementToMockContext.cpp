#include <ElementToMockContext.h>

void ElementToMockContext::addMacroDefine(std::string p_id, std::string p_definition)
{
  addMacroDefine(std::move(p_id), std::vector{std::string{}}, std::move(p_definition));
}

void ElementToMockContext::addMacroDefine(std::string p_id, std::vector<std::string> p_parameters, std::string p_definition)
{
  std::string copy_id = p_id;
  m_macroDefinition.try_emplace(std::move(p_id), std::move(copy_id), std::move(p_parameters), std::move(p_definition));
}

void ElementToMockContext::deleteMacroDefine(const std::string &p_id)
{
  m_macroDefinition.erase(p_id);
}

bool ElementToMockContext::hasMacroDefine(const std::string& p_id) const
{
  return m_macroDefinition.find(p_id) != m_macroDefinition.end();
}

const MacroDefinition& ElementToMockContext::getMacroDefinition(const std::string& p_id)
{
  static MacroDefinition emptyString{"", {}, ""};
  if(m_macroDefinition.find(p_id) != m_macroDefinition.end())
  {
    return m_macroDefinition.at(p_id);
  }
  return emptyString;
}

const std::unordered_map<std::string, MacroDefinition>& ElementToMockContext::getCrossDefinedMap() const
{
  return m_macroDefinition;
}

const ElementToMock::Vector& ElementToMockContext::getElementToMock() const
{
  return m_elementToMock;
}

void ElementToMockContext::addElementToMock(ElementToMock* p_elementToMock)
{
  m_elementToMock.push_back(p_elementToMock);
}
