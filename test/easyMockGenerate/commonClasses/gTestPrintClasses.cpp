#include <gtestPrintClasses.h>

#include <TypeItf.h>
#include <Function.h>
#include <ReturnValue.h>
#include <CType.h>
#include <ComposableField.h>
#include <StructType.h>
#include <UnionType.h>

template<class T>
static void printComposableTypeToOstream(std::ostream& os, const T& composableType, std::string classname);

std::ostream& operator<<(std::ostream& os, const Function& fun) {
  os << std::endl << "funPrototype: " << fun.getFunctionPrototype() << std::endl;

  const ReturnValue *rv = fun.getReturnType();
  os << "Return value:" << std::endl << "\t" << *rv << std::endl;

  const Parameter::Vector& params = fun.getFunctionsParameters();
  const Parameter::Vector::size_type nbParams = params.size();
  Parameter::Vector::size_type curParamIdx;
  for(curParamIdx =  0; curParamIdx < nbParams; curParamIdx++)
  {
    const Parameter &curParamObj = params[curParamIdx];
    os << "Parameter " << curParamIdx << ": " << curParamObj;
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const ReturnValue& rv) {
  const TypeItf *typeItf = rv.getType();
  return os << *typeItf;
}

std::ostream& operator<<(std::ostream& os, const TypeItf& typeItf)
{
  if(typeItf.isCType())
  {
    os << dynamic_cast<const CType &>(typeItf);
  }
  else if(typeItf.isStruct())
  {
    os << dynamic_cast<const StructType &>(typeItf);
  }
  else if(typeItf.isUnion())
  {
    os << dynamic_cast<const UnionType &>(typeItf);
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const CType& ctype)
{
  return os << "Ctype: " << ctype.getName();
}

std::ostream& operator<<(std::ostream& os, const StructType& structType)
{
  printComposableTypeToOstream(os, structType, "StructType");
  return os;
}

std::ostream& operator<<(std::ostream& os, const Parameter& param)
{
  os << "Parameter name: " << param.getName() << std::endl;
  os << "\t" << *param.getType();

  return os;
}

std::ostream& operator<<(std::ostream& os, const ComposableField& composableField)
{
  os << "ComposableField(";
  os << "name: '" << composableField.getName() << "', ";
  os << "isRecursive: " << (composableField.isRecursiveTypeField() ? "yes" : " no") << ", ";
  os << "isPointer: " << (composableField.isPointer() ? "yes" : " no") << ", ";
  os << "type: " << std::endl;
  os << "\t\t\t" << *composableField.getType() << ")END ComposableField " << composableField.getName();
  return os;
}

std::ostream& operator<<(std::ostream& os, const UnionType& unionType)
{
  printComposableTypeToOstream(os, unionType, "UnionType");
  return os;
}

template<class T>
static void printComposableTypeToOstream(std::ostream& os, const T& composableType, std::string classname)
{
  os << classname << "(";
  os << "name: '" << composableType.getName() << "'" << ", ";
  os << "typeDefName: '" << composableType.getTypedDefName() << "'" << ", ";
  os << "anonymous: " << (composableType.isAnonymous() ? "yes" : " no") << ", ";
  os << "m_anonymous_number: " << composableType.m_anonymous_number << ", ";
  os << "embedded: " << (composableType.isEmbeddedInOtherType() ? "yes" : " no");
  os << ")" << std::endl;

  const ComposableField::Vector& structFields = composableType.getContainedFields();
  const ComposableField::Vector::size_type nbFields = structFields.size();
  ComposableField::Vector::size_type fieldIdx;
  for(fieldIdx = 0; fieldIdx < nbFields; fieldIdx++)
  {
    const ComposableField& curField = structFields[fieldIdx];
    os << "\t\tField: " << fieldIdx << ": " << curField << std::endl;
  }
}
