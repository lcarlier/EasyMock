#include <gtestPrintClasses.h>

#include <TypeItf.h>
#include <Function.h>
#include <ReturnValue.h>
#include <CType.h>
#include <ComposableField.h>
#include <StructType.h>
#include <UnionType.h>
#include <Pointer.h>

template<class T>
static void printComposableTypeToOstream(std::ostream& os, const T& composableType, std::string classname);

static std::string gs_indentation;

std::ostream& operator<<(std::ostream& os, const Function& fun) {
  os << std::endl << "funPrototype: " << fun.getFunctionPrototype() << std::endl;

  const ReturnValue *rv = fun.getReturnType();
  os << "Return value:";
  gs_indentation.push_back('\t');
  os << std::endl << gs_indentation;
  os << *rv << std::endl;
  gs_indentation.pop_back();

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
  os << "ReturnValue " << " declString: '" << rv.getDeclareString() << "'";
  gs_indentation.push_back('\t');
  os << std::endl << gs_indentation;
  os << *typeItf;
  gs_indentation.pop_back();
  return os;
}

std::ostream& operator<<(std::ostream& os, const TypeItf& typeItf)
{
  os << "TypeItf:" << typeItf.getMostDefinedName() << ", ";
  os << "isTypeDef:" << (typeItf.isTypedDef() ? "yes" : "no") << ", ";
  os << "isAnonymous:" << (typeItf.isAnonymous() ? "yes" : "no") << ", ";
  os << "isPointer:" << (typeItf.isPointer() ? "yes" : "no") << ", ";
  os << "isConst:" << (typeItf.isConst() ? "yes" : "no") << ", ";
  os << "isStruct:" << (typeItf.isStruct() ? "yes" : "no") << ", ";
  os << "isUnion:" << (typeItf.isUnion() ? "yes" : "no") << ", ";
  os << "isImplicit:" << (typeItf.isImplicit() ? "yes" : "no") << ", ";
  os << std::endl << gs_indentation;

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
  else if(typeItf.isPointer())
  {
    os << dynamic_cast<const Pointer &>(typeItf);
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const CType& ctype)
{
  return os << "Ctype: " << ctype.getName() << std::endl;
}

std::ostream& operator<<(std::ostream& os, const StructType& structType)
{
  printComposableTypeToOstream(os, structType, "StructType");
  return os;
}

std::ostream& operator<<(std::ostream& os, const Parameter& param)
{
  const TypeItf *type = param.getType();
  os << "Parameter declString: '" << param.getDeclareString() << "', ";
  os << "name: '" << param.getName() << "'";
  os << std::endl;
  gs_indentation.push_back('\t');
  os << gs_indentation << *type;
  gs_indentation.pop_back();

  return os;
}

std::ostream& operator<<(std::ostream& os, const ComposableField& composableField)
{
  os << "ComposableField(";
  os << "declString: '" << composableField.getDeclareString() << "', ";
  os << "name: '" << composableField.getName() << "', ";
  os << "isRecursive: " << (composableField.isRecursiveTypeField() ? "yes" : " no") << ", ";
  os << "type: " << std::endl;
  gs_indentation.push_back('\t');
  os << gs_indentation << *composableField.getType();
  gs_indentation.pop_back();
  os << gs_indentation << ")END ComposableField '" << composableField.getName() << "'";
  return os;
}

std::ostream& operator<<(std::ostream& os, const UnionType& unionType)
{
  printComposableTypeToOstream(os, unionType, "UnionType");
  return os;
}

std::ostream& operator<<(std::ostream& os, const Pointer& pointerType)
{
  os << "Pointer: ";
  os << "recursivePointer: " << (pointerType.m_isRecursivePointer ? "yes" : "no");
  gs_indentation.push_back('\t');
  os << std::endl << gs_indentation;
  if(!pointerType.m_isRecursivePointer)
  {
    os << *pointerType.getPointedType();
  }
  else
  {
    os << "pointedType pointer: " << pointerType.getPointedType();
  }
  gs_indentation.pop_back();
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
    gs_indentation.push_back('\t');
    os << gs_indentation << "Field: " << fieldIdx << ": " << curField << std::endl;
    gs_indentation.pop_back();
  }
}
