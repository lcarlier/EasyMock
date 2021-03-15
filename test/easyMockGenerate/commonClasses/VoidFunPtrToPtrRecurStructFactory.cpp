#include "VoidFunPtrToPtrRecurStructFactory.h"

#include <StructType.h>
#include <FunctionDeclaration.h>
#include <Pointer.h>
#include <EasyMock_CType.h>
#include <IncompleteType.h>
#include <ComposableField.h>

ElementToMockList VoidFunPtrToPtrRecurStructFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  StructType t("ptrToPtrStructRecur", false);
  Pointer *pField = new Pointer(new IncompleteType(t, IncompleteType::Type::STRUCT));
  Pointer *p2pField = new Pointer(pField);
  t.addField(new ComposableField(p2pField, "r"));

  Pointer *pType = new Pointer(t.clone());
  Pointer p2pType(pType);

  {
    FunctionDeclaration *fd = new FunctionDeclaration("voidFunPtrToPtrRecurStruct", VoidReturnValue(), Parameter::Vector({new Parameter(p2pType.clone(), "s")}));
    returnedList.push_back(fd);
  }

  {
    FunctionDeclaration *fd = new FunctionDeclaration("ptrToPtrRecurStructFunVoid", ReturnValue(p2pType.clone()), Parameter::Vector({}));
    returnedList.push_back(fd);
  }
  {
    StructType *topS = new StructType("structFieldptrToPtrStructRecur", false);
    topS->addField(new ComposableField(p2pType.clone(), "f"));

    FunctionDeclaration *fd = new FunctionDeclaration("voidFunStructFieldptrToPtrStructRecur", VoidReturnValue(), Parameter::Vector({new Parameter(topS, "s")}));
    returnedList.push_back(fd);
  }
  {
    StructType *topS = new StructType("structAnonStructFieldptrToPtrStructRecur", false);
    topS->addField(new ComposableField(new CType(CTYPE_INT), "a"));
    StructType *anonS = new StructType("", true);
    anonS->addField(new ComposableField(p2pType.clone(), "r"));
    topS->addField(new ComposableField(anonS, ""));

    FunctionDeclaration *fd = new FunctionDeclaration("voidFunStructAnonStructFieldptrToPtrStructRecur", VoidReturnValue(), Parameter::Vector({new Parameter(topS, "s")}));

    returnedList.push_back(fd);
  }
  return returnedList;
}

std::string VoidFunPtrToPtrRecurStructFactory::functionGetFunctionName()
{
  return std::string("voidFunPtrToPtrRecurStruct");
}

std::string VoidFunPtrToPtrRecurStructFactory::getFilename()
{
  return "voidFunPtrToPtrRecurStruct.h";
}
