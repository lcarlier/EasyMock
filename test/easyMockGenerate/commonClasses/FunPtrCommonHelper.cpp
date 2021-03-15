#include <FunPtrCommonHelper.h>

#include <FunctionDeclaration.h>
#include <FunctionType.h>
#include <Pointer.h>
#include <EasyMock_CType.h>
#include <StructType.h>
#include <ComposableField.h>
#include <TypedefType.h>

#include <assert.h>

FunctionDeclaration* getFunPtrDeclaration(unsigned int n, const char *functionName, std::string&& structName, std::string&& typedefName)
{
  ReturnValue ftRv(new CType(CTYPE_INT));
  FunctionType *ft = new FunctionType(ftRv, Parameter::Vector({NamedParameter(CTYPE_INT, ""), NamedParameter(CTYPE_FLOAT, "")}));
  Pointer ptrToFun(ft);
  switch(n)
  {
    case 0:
    //First function
    {
      ReturnValue rv(new CType(CTYPE_VOID));
      TypeItf* paramType = ptrToFun.clone();
      if(!typedefName.empty())
      {
        paramType = new TypedefType(typedefName, paramType);
      }
      Parameter *p = new Parameter(paramType, "funPtr");
      FunctionDeclaration* fd = new FunctionDeclaration(functionName, rv, Parameter::Vector({p}));
      return fd;
    }

    case 1:
    /*
     * Second function
     * cdecl> declare funPtrFunPtr as function(pointer to function(float, float) returning pointer to function(char, char) returning double) returning int
     * int funPtrFunPtr(double (*(*)(float, float ))(char, char ))
     */
    {
      FunctionType *ft1 = new FunctionType(TypedReturnValue(CTYPE_DOUBLE), Parameter::Vector({NamedParameter(CTYPE_CHAR, ""), NamedParameter(CTYPE_CHAR, "")}));
      Pointer *ptf1 = new Pointer(ft1);
      ft1 = nullptr;
      ReturnValue rv(ptf1);
      ptf1 = nullptr;
      FunctionType* ft2 = new FunctionType(rv, Parameter::Vector({NamedParameter(CTYPE_FLOAT, ""), NamedParameter(CTYPE_FLOAT, "")}));
      Pointer *ptf2 = new Pointer(ft2);

      FunctionDeclaration *fd = new FunctionDeclaration(functionName, TypedReturnValue(CTYPE_INT), Parameter::Vector({new Parameter(ptf2, "")}));
      return fd;
    }

    case 2:
    //Third function
    {
      ReturnValue rv2(ptrToFun.clone());
      FunctionDeclaration* fd = new FunctionDeclaration(functionName, rv2, Parameter::Vector({NamedParameter(CTYPE_CHAR, "")}));
      return fd;
    }

    case 3:
    /*
     * Fourth function
     * cdecl> declare foo as function(int) returning pointer to function(float) returning pointer to function(char) returning double
     * double (* (* funPtrFunToFun(int ))(float ))(char );
     */
    {
      FunctionType *ft1 = new FunctionType(TypedReturnValue(CTYPE_DOUBLE), Parameter::Vector({NamedParameter(CTYPE_CHAR, ""),NamedParameter(CTYPE_CHAR, "")}));
      Pointer *ptf1 = new Pointer(ft1);
      ft1 = nullptr;
      FunctionType *ft2 = new FunctionType(ReturnValue(ptf1), Parameter::Vector({NamedParameter(CTYPE_FLOAT, ""),NamedParameter(CTYPE_FLOAT, "")}));
      ptf1 = nullptr;
      Pointer *ptf2 = new Pointer(ft2);
      ft2 = nullptr;
      ReturnValue rv3(ptf2);
      FunctionDeclaration* fd = new FunctionDeclaration(functionName, rv3, Parameter::Vector({NamedParameter(CTYPE_INT, "")}));
      return fd;
    }

    case 4:
    /*
     * Fifth function
     * intFunPtrToFunField
     */
    {
      StructType *s = new StructType(structName, false);
      TypeItf* fieldType = ptrToFun.clone();
      if(!typedefName.empty())
      {
        fieldType = new TypedefType(typedefName, fieldType);
      }
      s->addField(new ComposableField(fieldType, "funPtr"));
      FunctionDeclaration *fd = new FunctionDeclaration(functionName, TypedReturnValue(CTYPE_INT), Parameter::Vector({new Parameter(s, "ptrToFunField")}));
      return fd;
    }

    case 5:
    /*
     * Sixth function
     * intFunPtrToFunField
     */
    {
      bool isEmbeddedStruct = true;
      StructType* top = new StructType(structName, !isEmbeddedStruct); //NOT EMBEDDED
      top->addField(new ComposableField(CTYPE_INT, "a"));
      StructType* beingDefined = new StructType("", isEmbeddedStruct);
      TypeItf* fieldType = ptrToFun.clone();
      if(!typedefName.empty())
      {
        fieldType = new TypedefType(typedefName, fieldType);
      }
      beingDefined->addField(new ComposableField(fieldType, "funPtr"));
      top->addField(new ComposableField(beingDefined, ""));
      FunctionDeclaration *fd = new FunctionDeclaration(functionName, TypedReturnValue(CTYPE_INT), Parameter::Vector({new Parameter(top, "ptrToStructAnonFunField")}));

      return fd;
    }
  }
  assert(false);
}
