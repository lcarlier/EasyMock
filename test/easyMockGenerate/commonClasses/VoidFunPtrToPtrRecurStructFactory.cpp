#include "VoidFunPtrToPtrRecurStructFactory.h"

#include <StructType.h>
#include <FunctionDeclaration.h>
#include <Pointer.h>
#include <CType.h>

ElementToMockList VoidFunPtrToPtrRecurStructFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  StructType t("ptrToPtrStructRecur", false);
  Pointer *pField = new Pointer(&t);
  Pointer *p2pField = new Pointer(pField);
  ComposableField::attributes fieldAttr =
  {
    .arraySize = -1,
    .isIncompleteTypeField = true
  };
  t.addField(new ComposableField(p2pField, "r", fieldAttr));

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
    /*
     * with -fno-access-control we are able to set this static class variable to
     * decrement the number of anonymous composable type by the number of anonymous
     * type the UT contains.
     * Thanks to that, the following code will generate the same anonymous ID
     */
    constexpr int NB_ANONYMOUS_TYPE_IN_THIS_UT = 1;
    ComposableType::m_number_of_anonymous_composable_type -= NB_ANONYMOUS_TYPE_IN_THIS_UT;
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
