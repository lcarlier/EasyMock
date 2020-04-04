#ifndef PARAMETER_H
#define PARAMETER_H

#include <string>

#include "EasyMockGenerateTypes.h"
#include "ComposableField.h"
#include "Declarator.h"

class Parameter : public Declarator
{
public:
  Parameter(TypeItf *p_type, std::string p_name);
  Parameter(TypeItf *p_type, std::string p_name, bool isPointer);

  typedef AutoCleanVectorPtr<Parameter> Vector;

  Parameter(const Parameter &other);
  Parameter& operator=(Parameter other);

  Parameter(Parameter &&other);
  //With elision pattern no need for move assignment

  bool operator==(const Parameter &other) const;
  bool operator!=(const Parameter &other) const;

  const std::string &getName() const;

  virtual ~Parameter();

  virtual Parameter* clone() const;

private:
  /* Do not make the member const otherwise they are not copyable anymore */
  std::string m_name;

  friend void swap(Parameter &first, Parameter &second);
};

Parameter *VoidParameter(std::string p_name);
Parameter *NamedParameter(easyMock_cTypes_t p_type, std::string p_name, bool p_isPointer = false);
Parameter *StructParameter(std::string type, std::string name, const ComposableField::Vector elem, bool p_is_embedded_in_other_type);


#endif /* PARAMETER_H */

