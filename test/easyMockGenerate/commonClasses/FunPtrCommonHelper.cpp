#include <FunPtrCommonHelper.h>

#include <FunctionDeclaration.h>
#include <FunctionType.h>
#include <Pointer.h>
#include <EasyMock_CType.h>
#include <StructType.h>
#include <ComposableField.h>
#include <TypedefType.h>
#include <ConstQualifiedType.h>

#include <cassert>

#include <memory>

std::shared_ptr<TypeItf> getPointerToFunToTest()
{
  ReturnValue ftRv(std::make_shared<CType>(CTYPE_INT));
  Parameter::Vector pv{};
  pv.emplace_back(NamedParameter(CTYPE_INT, ""));
  pv.emplace_back(NamedParameter(CTYPE_FLOAT, ""));
  auto ft = std::make_shared<FunctionType>(std::move(ftRv), std::move(pv));
  return std::make_shared<Pointer>(std::move(ft));
};

std::shared_ptr<FunctionDeclaration> getFunPtrDeclaration(unsigned int n, const char *functionName, std::string&& structName, std::string&& typedefName)
{
  switch(n)
  {
    case 0:
    //First function
    {
      ReturnValue rv(std::make_shared<CType>(CTYPE_VOID));
      auto paramType = getPointerToFunToTest();
      if(!typedefName.empty())
      {
        paramType = std::make_shared<TypedefType>(typedefName, paramType);
      }
      Parameter::Vector pv{};
      pv.emplace_back(Parameter(std::move(paramType), "funPtr"));
      auto fd = std::make_shared<FunctionDeclaration>(functionName, std::move(rv), std::move(pv));
      return fd;
    }

    case 1:
    /*
     * Second function
     * cdecl> declare funPtrFunPtr as function(pointer to function(float, float) returning pointer to function(char, char) returning double) returning int
     * int funPtrFunPtr(double (*(*)(float, float ))(char, char ))
     */
    {
      Parameter::Vector pvft1{};
      pvft1.emplace_back(NamedParameter(CTYPE_CHAR, ""));
      pvft1.emplace_back(NamedParameter(CTYPE_CHAR, ""));
      auto ft1 = std::make_shared<FunctionType>(TypedReturnValue(CTYPE_DOUBLE), std::move(pvft1));
      auto ptf1 = std::make_shared<Pointer>(std::move(ft1));
      ReturnValue rv(std::move(ptf1));

      Parameter::Vector pvft2{};
      pvft2.emplace_back(NamedParameter(CTYPE_FLOAT, ""));
      pvft2.emplace_back(NamedParameter(CTYPE_FLOAT, ""));
      auto ft2 = std::make_shared<FunctionType>(std::move(rv), std::move(pvft2));
      auto ptf2 = std::make_shared<Pointer>(std::move(ft2));

      Parameter::Vector pv{};
      pv.emplace_back(Parameter(std::move(ptf2), ""));
      auto fd = std::make_shared<FunctionDeclaration>(functionName, TypedReturnValue(CTYPE_INT), std::move(pv));
      return fd;
    }

    case 2:
    //Third function
    {
      ReturnValue rv(getPointerToFunToTest());
      Parameter::Vector pv{};
      pv.emplace_back(NamedParameter(CTYPE_CHAR, ""));
      auto fd = std::make_shared<FunctionDeclaration>(functionName, std::move(rv), std::move(pv));
      return fd;
    }

    case 3:
    /*
     * Fourth function
     * cdecl> declare foo as function(int) returning pointer to function(float) returning pointer to function(char) returning double
     * double (* (* funPtrFunToFun(int ))(float ))(char );
     */
    {
      Parameter::Vector pvft1{};
      pvft1.emplace_back(NamedParameter(CTYPE_CHAR, ""));
      pvft1.emplace_back(NamedParameter(CTYPE_CHAR, ""));
      auto ft1 = std::make_shared<FunctionType>(TypedReturnValue(CTYPE_DOUBLE), std::move(pvft1));
      auto ptf1 = std::make_shared<Pointer>(std::move(ft1));

      Parameter::Vector pvft2{};
      pvft2.emplace_back(NamedParameter(CTYPE_FLOAT, ""));
      pvft2.emplace_back(NamedParameter(CTYPE_FLOAT, ""));
      auto ft2 = std::make_shared<FunctionType>(ReturnValue(std::move(ptf1)), std::move(pvft2));

      auto ptf2 = std::make_shared<Pointer>(std::move(ft2));
      ReturnValue rv(std::move(ptf2));

      Parameter::Vector pv{};
      pv.emplace_back(NamedParameter(CTYPE_INT, ""));
      auto fd = std::make_shared<FunctionDeclaration>(functionName, std::move(rv), std::move(pv));
      return fd;
    }

    case 4:
    /*
     * Fifth function
     * intFunPtrToFunField
     */
    {
      auto s = std::make_shared<StructType>(structName, false);
      auto fieldType = getPointerToFunToTest();
      if(!typedefName.empty())
      {
        fieldType = std::make_shared<TypedefType>(typedefName, fieldType);
      }
      s->addField(ComposableField{fieldType, "funPtr"});

      Parameter::Vector pv{};
      pv.emplace_back(Parameter(std::move(s), "ptrToFunField"));
      auto fd = std::make_shared<FunctionDeclaration>(functionName, TypedReturnValue(CTYPE_INT), std::move(pv));
      return fd;
    }

    case 5:
    /*
     * Sixth function
     * intFunPtrToFunField
     */
    {
      bool isEmbeddedStruct = true;
      auto top = std::make_shared<StructType>(structName, !isEmbeddedStruct); //NOT EMBEDDED
      top->addField(ComposableField(CTYPE_INT, "a"));
      auto beingDefined = std::make_shared<StructType>("", isEmbeddedStruct);
      auto fieldType = getPointerToFunToTest();
      if(!typedefName.empty())
      {
        fieldType = std::make_shared<TypedefType>(typedefName, fieldType);
      }
      beingDefined->addField(ComposableField(fieldType, "funPtr"));
      top->addField(ComposableField(std::move(beingDefined), ""));

      Parameter::Vector pv{};
      pv.emplace_back(Parameter(std::move(top), "ptrToStructAnonFunField"));
      auto fd = std::make_shared<FunctionDeclaration>(functionName, TypedReturnValue(CTYPE_INT), std::move(pv));

      return fd;
    }
    case 6:
    /*
    * cdecl> declare constFunPtrFunInt as function(int) returning const pointer to function(float) returning int
    */
    {
      auto constQualifiedFunPtrTypeType = std::make_shared<ConstQualifiedType> (getPointerToFunToTest() );
      ReturnValue rv { std::move(constQualifiedFunPtrTypeType) };

      Parameter::Vector pv{};
      pv.emplace_back(Parameter{std::make_shared<CType>(CTYPE_INT), ""});
      auto fd = std::make_shared<FunctionDeclaration>(functionName, std::move(rv), std::move(pv));

      return fd;
    }
    case 7:
    {
      auto constPtrFunFieldStruct = std::make_shared<StructType>("constPtrFunFieldStruct", false);

      Parameter::Vector pvFt{};
      pvFt.emplace_back(NamedParameter(CTYPE_INT, ""));
      pvFt.emplace_back(NamedParameter(CTYPE_FLOAT, ""));
      auto functionType = std::make_shared<FunctionType>(TypedReturnValue(CTYPE_INT), std::move(pvFt));
      auto pft = std::make_shared<Pointer>(std::move(functionType));
      auto cpft = std::make_shared<ConstQualifiedType>(std::move(pft));
      constPtrFunFieldStruct->addField(ComposableField{std::move(cpft), "constFunPtr"});

      Parameter::Vector pv{};
      pv.emplace_back(Parameter{std::move(constPtrFunFieldStruct), "p"});
      auto fd = std::make_shared<FunctionDeclaration>(functionName, TypedReturnValue(CTYPE_INT), std::move(pv));

      return fd;
    }
  }
  assert(false);
}
