#include <VoidFunEnumFactory.h>

#include <FunctionDeclaration.h>
#include <Enum.h>
#include <StructType.h>
#include <Pointer.h>

#include "EasyMock_CType.h"

ElementToMockList VoidFunEnumFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  Enum e("enumTest", "");
  {
    FunctionDeclaration *fd = new FunctionDeclaration("voidFunEnum", VoidReturnValue(false), Parameter::Vector({new Parameter(e.clone(), "e")}));
    returnedList.push_back(fd);
  }
  {
    FunctionDeclaration *fd = new FunctionDeclaration("voidFunPtrEnum", VoidReturnValue(false), Parameter::Vector({new Parameter(new Pointer(e.clone()), "e")}));
    returnedList.push_back(fd);
  }
  {
    FunctionDeclaration *fd = new FunctionDeclaration("enumFunVoid", ReturnValue(e.clone()), Parameter::Vector({}));
    returnedList.push_back(fd);
  }
  {
    StructType *s = new StructType("structTestEnum", false);
    s->addField(new ComposableField(e.clone(), "e"));
    FunctionDeclaration *fd = new FunctionDeclaration("voidFunStructEnum", VoidReturnValue(false), Parameter::Vector({new Parameter(s, "s")}));
    returnedList.push_back(fd);
  }
  {
    const unsigned int NB_ANONYMOUS_TYPE_IN_THIS_UT = 1;
    /*
     * with -fno-access-control we are able to set this static class variable to
     * decrement the number of anonymous composable type by the number of anonymous
     * type the UT contains.
     * Thanks to that, the following code will generate the same anonymous ID
     */
    ComposableType::m_number_of_anonymous_composable_type -= NB_ANONYMOUS_TYPE_IN_THIS_UT;
    StructType *s = new StructType("structTestAnonyStructEnum", false);
    s->addField(new ComposableField(new CType(CTYPE_INT), "a"));
    StructType *as = new StructType("", true);
    as->addField(new ComposableField(e.clone(), "e"));
    s->addField(new ComposableField(as, ""));
    FunctionDeclaration *fd = new FunctionDeclaration("voidFunStructAnonStructEnum", VoidReturnValue(false), Parameter::Vector({new Parameter(s, "s")}));
    returnedList.push_back(fd);
  }
  return returnedList;
}

std::string VoidFunEnumFactory::functionGetFunctionName()
{
  return std::string("voidFunEnum");
}

std::string VoidFunEnumFactory::getFilename()
{
  return "voidFunEnum.h";
}
