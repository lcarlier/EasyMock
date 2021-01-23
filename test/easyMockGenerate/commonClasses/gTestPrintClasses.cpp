#include <gtestPrintClasses.h>

#include <TypeItf.h>
#include <Function.h>
#include <ReturnValue.h>
#include <EasyMock_CType.h>
#include <ComposableField.h>
#include <StructType.h>
#include <UnionType.h>
#include <Pointer.h>
#include <FunctionType.h>
#include <FunctionDeclaration.h>
#include <Enum.h>
#include <IncompleteType.h>
#include <ComposableBitfield.h>
#include <ConstQualifiedType.h>

template<class T>
static void printComposableTypeToOstream(std::ostream& os, const T& composableType, std::string classname);

static std::string gs_indentation;

template <typename T>
std::ostream& printFunction(std::ostream& os, const T& fun)
{
  os << std::endl << "funPrototype: " << fun.getFunctionPrototype() << ", ";
  os << "isVariadic: " << (fun.isVariadic() ? "yes" : "no") << ", ";
  os << "isInline: " << (fun.isInlined() ? "yes" : "no") << std::endl;

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

std::ostream& operator<<(std::ostream& os, const Function& fun)
{
  return printFunction(os, fun);
}

std::ostream& operator<<(std::ostream& os, const FunctionType& fun)
{
  return printFunction(os, fun);
}

std::ostream& operator<<(std::ostream& os, const FunctionDeclaration& fun)
{
  return printFunction(os, fun);
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
  bool isConst = typeItf.isConst();
  os << "TypeItf:" << typeItf.getMostDefinedName() << ", ";
  os << "isTypeDef:" << (typeItf.isTypedDef() ? "yes" : "no") << ", ";
  os << "isAnonymous:" << (typeItf.isAnonymous() ? "yes" : "no") << ", ";
  os << "isPointer:" << (typeItf.isPointer() ? "yes" : "no") << ", ";
  os << "isCType:" << (typeItf.isCType() ? "yes" : "no") << ", ";
  os << "isStruct:" << (typeItf.isStruct() ? "yes" : "no") << ", ";
  os << "isUnion:" << (typeItf.isUnion() ? "yes" : "no") << ", ";
  os << "isImplicit:" << (typeItf.isImplicit() ? "yes" : "no") << ", ";
  os << "isEnum:" << (typeItf.isEnum() ? "yes" : "no") << ", ";
  os << "isIncomplete:" << (typeItf.isIncompleteType() ? "yes" : "no") << ", ";
  os << "isConst:" << (isConst ? "yes" : "no");
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
  else if(typeItf.isEnum())
  {
    os << dynamic_cast<const Enum &>(typeItf);
  }
  else if(typeItf.isIncompleteType())
  {
    os << dynamic_cast<const IncompleteType &>(typeItf);
  }
  else if(isConst)
  {
    os << dynamic_cast<const ConstQualifiedType &>(typeItf);
  }
  else
  {
    os << std::endl;
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
  os << "isIncomplete: " << (composableField.isIncompleteTypeField() ? "yes" : " no") << ", ";
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
  os << "isIncompletePointerType: " << (pointerType.m_isIncompletePointerType ? "yes" : "no");
  gs_indentation.push_back('\t');
  os << std::endl << gs_indentation;
  if(!pointerType.m_isIncompletePointerType)
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
  os << "DeclEmbedded: " << (composableType.isDeclarationEmbeddedInOtherType() ? "yes" : " no");
  os << ")" << std::endl;

  const ComposableFieldItf::Vector& structFields = composableType.getContainedFields();
  const ComposableFieldItf::Vector::size_type nbFields = structFields.size();
  ComposableFieldItf::Vector::size_type fieldIdx;
  for(fieldIdx = 0; fieldIdx < nbFields; fieldIdx++)
  {
    const ComposableFieldItf& curField = structFields[fieldIdx];
    gs_indentation.push_back('\t');
    os << gs_indentation << "Field: " << fieldIdx << ": " << curField << std::endl;
    gs_indentation.pop_back();
  }
}

std::ostream& operator<<(std::ostream& os, const Enum& etype)
{
  return os << "Enum: name:'" << etype.getName() << "' typedef:'" << etype.getTypedDefName() << "'" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const IncompleteType& incType)
{
  return os << "Incomplete Type: name:'" << incType.getName() << "' typedef:'" << incType.getTypedDefName() << "'" << std::endl;
}

void PrintTo(const __int128& int128Type, std::ostream* os)
{
  uint64_t lowDigit = int128Type & 0xffffffffffffffff;
  uint64_t highDigit = int128Type >> 64;
  *os << "0x" << std::hex << highDigit << lowDigit;
}

std::ostream& operator<<(std::ostream& os, const __int128& int128Type)
{
  PrintTo(int128Type, &os);
  return os;
}

void PrintTo(const unsigned __int128& uint128Type, std::ostream* os)
{
  uint64_t lowDigit = uint128Type & 0xffffffffffffffff;
  uint64_t highDigit = uint128Type >> 64;
  *os << "0x" << std::hex << highDigit << lowDigit;
}

std::ostream& operator<<(std::ostream& os, const unsigned __int128& uint128Type)
{
  PrintTo(uint128Type, &os);
  return os;
}

std::ostream& operator<<(std::ostream& os, const ComposableFieldItf& composableFieldItf)
{
  if(composableFieldItf.isComposableField())
  {
    return operator<<(os, dynamic_cast<const ComposableField&>(composableFieldItf));
  }
  if(composableFieldItf.isComposableBitfield())
  {
    return operator<<(os, dynamic_cast<const ComposableBitfield&>(composableFieldItf));
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const ComposableBitfield& composableBitfield)
{
  os << "ComposableBitfield(";
  os << "declString: '" << composableBitfield.getDeclareString() << "', ";
  os << "name: '" << composableBitfield.getName() << "', ";
  os << "size: '" << static_cast<unsigned>(composableBitfield.getSize()) << "', ";
  os << "type: " << std::endl;
  gs_indentation.push_back('\t');
  os << gs_indentation << *composableBitfield.getType();
  gs_indentation.pop_back();
  os << gs_indentation << ")END ComposableBitfield '" << composableBitfield.getName() << "'";
  return os;
}

std::ostream& operator<<(std::ostream& os, const ConstQualifiedType& constQualifiedType)
{
  os << "ConstQualifiedType(" << std::endl;
  gs_indentation.push_back('\t');
  os << gs_indentation << *constQualifiedType.getType();
  gs_indentation.pop_back();
  os << gs_indentation << ")END ConstQualifiedType '" << std::endl;
  return os;
}
