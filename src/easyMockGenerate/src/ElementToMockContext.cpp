#include <ElementToMockContext.h>

void ElementToMockContext::addMacroDefine(const std::string& p_id, const std::string& p_definition)
{
  m_macroDefinition[p_id] = p_definition;
}

void ElementToMockContext::deleteMacroDefine(const std::string &p_id)
{
  m_macroDefinition.erase(p_id);
}

bool ElementToMockContext::hasMacroDefine(const std::string& p_id) const
{
  return m_macroDefinition.find(p_id) != m_macroDefinition.end();
}

const std::string& ElementToMockContext::getMacroDefinition(const std::string& p_id)
{
  static std::string emptyString("");
  if(m_macroDefinition.find(p_id) != m_macroDefinition.end())
  {
    return m_macroDefinition[p_id];
  }
  return emptyString;
}

const std::unordered_map<std::string, std::string>& ElementToMockContext::getCrossDefinedMap() const
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
