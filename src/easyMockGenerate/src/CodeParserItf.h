#ifndef CODEPARSERITF_H
#define CODEPARSERITF_H

#include <vector>
#include <string>

struct Parameter
{

  Parameter(std::string type, std::string name) :
  type(type), name(name) { }
  std::string type;
  std::string name;
};

typedef std::vector<Parameter> ParameterVector;

enum CodeParser_errCode
{
  cp_OK
};

enum ElementToStub_Type
{
  ETS_function
};

class ElementToStub
{
public:
  ElementToStub(ElementToStub_Type stubType, std::string name, ParameterVector functionParameters)
: m_stubType(stubType), m_name(name) { }
  const std::string *getName() const { return &m_name; }
  const ElementToStub_Type *getStubType() const { return &m_stubType; }
  const ParameterVector *getFunctionsParameters() const { return &m_parameters; }
  virtual const std::string *getReturnType() const { return NULL; }

private:
  ElementToStub_Type m_stubType;
  std::string m_name;
  ParameterVector m_parameters;
};

class Function : public ElementToStub
{
public:
  Function(std::string functionName, std::string functionReturnType, ParameterVector functionParameters) :
  ElementToStub(ETS_function, functionName, functionParameters), m_returnTypeStr(functionReturnType) { }
  const std::string *getReturnType() const { return &m_returnTypeStr; };
private:
  std::string m_returnTypeStr;
};

typedef std::vector<ElementToStub*> ElementToStubVector;
class CodeParserItf {
public:
  CodeParserItf() {}
  void setFilename(const std::string filename) { m_filename = filename; }
  virtual CodeParser_errCode getElementToStub(ElementToStubVector &elem) const = 0;
protected:
  std::string m_filename;
};

#endif /* CODEPARSERITF_H */

