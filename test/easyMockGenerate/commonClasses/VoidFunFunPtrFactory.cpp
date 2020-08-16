#include "VoidFunFunPtrFactory.h"

#include <FunctionDeclaration.h>
#include <FunctionType.h>
#include <Pointer.h>
#include <CType.h>
#include <StructType.h>

ElementToMockList VoidFunFunPtrFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  ReturnValue ftRv(new CType(CTYPE_INT));
  FunctionType *ft = new FunctionType("", ftRv, Parameter::Vector({NamedParameter(CTYPE_INT, ""), NamedParameter(CTYPE_FLOAT, "")}));
  Pointer ptrToFun(ft);
  //first function
  {
    ReturnValue rv(new CType(CTYPE_VOID));
    Parameter *p = new Parameter(ptrToFun.clone(), "funPtr");
    FunctionDeclaration* fd = new FunctionDeclaration(functionGetFunctionName(), rv, Parameter::Vector({p}));
    returnedList.push_back(fd);
  }

  /*
   * Second function
   * cdecl> declare funPtrFunPtr as function(pointer to function(float, float) returning pointer to function(char, char) returning double) returning int
   * int funPtrFunPtr(double (*(*)(float, float ))(char, char ))
   */
  {
    FunctionType *ft1 = new FunctionType("", TypedReturnValue(CTYPE_DOUBLE), Parameter::Vector({NamedParameter(CTYPE_CHAR, ""), NamedParameter(CTYPE_CHAR, "")}));
    Pointer *ptf1 = new Pointer(ft1);
    ft1 = nullptr;
    ReturnValue rv(ptf1);
    ptf1 = nullptr;
    FunctionType* ft2 = new FunctionType("", rv, Parameter::Vector({NamedParameter(CTYPE_FLOAT, ""), NamedParameter(CTYPE_FLOAT, "")}));
    Pointer *ptf2 = new Pointer(ft2);

    FunctionDeclaration *fd = new FunctionDeclaration("funPtrFunPtr", TypedReturnValue(CTYPE_INT), Parameter::Vector({new Parameter(ptf2, "param")}));
    returnedList.push_back(fd);
  }

  //Third function
  {
    ReturnValue rv2(ptrToFun.clone());
    FunctionDeclaration* fd = new FunctionDeclaration("funPtrFunChar", rv2, Parameter::Vector({NamedParameter(CTYPE_CHAR, "")}));
    returnedList.push_back(fd);
  }

  /*
   * Fourth function
   * cdecl> declare foo as function(int) returning pointer to function(float) returning pointer to function(char) returning double
   * double (* (* funPtrFunToFun(int ))(float ))(char );
   */
  {
    FunctionType *ft1 = new FunctionType("", TypedReturnValue(CTYPE_DOUBLE), Parameter::Vector({NamedParameter(CTYPE_CHAR, ""),NamedParameter(CTYPE_CHAR, "")}));
    Pointer *ptf1 = new Pointer(ft1);
    ft1 = nullptr;
    FunctionType *ft2 = new FunctionType("", ReturnValue(ptf1), Parameter::Vector({NamedParameter(CTYPE_FLOAT, ""),NamedParameter(CTYPE_FLOAT, "")}));
    ptf1 = nullptr;
    Pointer *ptf2 = new Pointer(ft2);
    ft2 = nullptr;
    ReturnValue rv3(ptf2);
    FunctionDeclaration* fd = new FunctionDeclaration("ptrFunToFunFunInt", rv3, Parameter::Vector({NamedParameter(CTYPE_INT, "")}));
    returnedList.push_back(fd);
  }

  /*
   * Fifth function
   * intFunPtrToFunField
   */
  {
    StructType *s = new StructType("ptrFunField", false);
    s->addField(new ComposableField(ptrToFun.clone(), "funPtr"));
    FunctionDeclaration *fd = new FunctionDeclaration("intFunStrutPtrFunField", TypedReturnValue(CTYPE_INT), Parameter::Vector({new Parameter(s, "ptrToFunField")}));
    returnedList.push_back(fd);
  }

  /*
   * Sixth function
   * intFunPtrToFunField
   */
  {
    const unsigned int NB_ANONYMOUS_TYPE_IN_THIS_UT = 1;
    /*
     * with -fno-access-control we are able to set this static class variable to
     * decrement the number of anonymous composable type by the number of anonymous
     * type the UT contains.
     * Thanks to that, the following code will generate the same anonymous ID
     */
    ComposableType::m_number_of_anonymous_composable_type -= NB_ANONYMOUS_TYPE_IN_THIS_UT;
    bool isEmbeddedStruct = true;
    StructType* top = new StructType("topAnonymousStructPtrFunField", !isEmbeddedStruct); //NOT EMBEDDED
    top->addField(new ComposableField(CTYPE_INT, "a"));
    StructType* beingDefined = new StructType("", isEmbeddedStruct);
    beingDefined->addField(new ComposableField(ptrToFun.clone(), "funPtr"));
    top->addField(new ComposableField(beingDefined, ""));
    FunctionDeclaration *fd = new FunctionDeclaration("intFunStrutPtrAnonFunField", TypedReturnValue(CTYPE_INT), Parameter::Vector({new Parameter(top, "ptrToStructAnonFunField")}));
    returnedList.push_back(fd);
  }

  /*
   * TO BE ENABLED WHEN SUPPORT OF CONST POINTER IS ADDED
   */
#if 0
  /*
   * 7th function
   * cdecl> cdecl> declare foo as function(int) returning const pointer to function(float) returning int
   */
  {
    FunctionType *ft = new FunctionType("", TypedReturnValue(CTYPE_INT), Parameter::Vector({NamedParameter(CTYPE_FLOAT, "")}));
    Pointer *ptf = new Pointer(ft, true);
    ft = nullptr;
    ReturnValue rv(ptf);
    ptf = nullptr;
    FunctionDeclaration *fd = new FunctionDeclaration("constFunPtrFunInt", rv, Parameter::Vector({NamedParameter(CTYPE_INT, "")}));
    returnedList.push_back(fd);
  }
#endif
  return returnedList;
}

std::string VoidFunFunPtrFactory::functionGetFunctionName()
{
  return std::string("voidFunFunPtr");
}

std::string VoidFunFunPtrFactory::getFilename()
{
   return "voidFunFunPtr.h";
}