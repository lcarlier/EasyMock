#include <VoidFunStructWithOutsideDeclaredAnonymousTypeStructFieldFactory.h>

#include <FunctionDeclaration.h>
#include <StructType.h>
#include <ComposableField.h>
#include <TypedefType.h>
#include <EasyMock_CType.h>
#include <Pointer.h>

ElementToMockList VoidFunStructWithOutsideDeclaredAnonymousTypeStructFieldFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  {
    CType ul{CTYPE_ULONG};
    TypedefType sval_t{"sval_t", ul.clone()};
    StructType structAnonymous_val_t{"", false};
    structAnonymous_val_t.addField(new ComposableField{sval_t.clone(), "val"});
    TypedefType val_t{"val_t", structAnonymous_val_t.clone()};

    StructType innerAnonymousStruct{"", true};
    innerAnonymousStruct.addField(new ComposableField{new Pointer{val_t.clone()}, "o"});
    StructType swo{"structWithOutsideAnonymousDeclaredStruct", false};
    swo.addField(new ComposableField{innerAnonymousStruct.clone(), ""});
    {
      FunctionDeclaration *f = new FunctionDeclaration{functionGetFunctionName(), TypedReturnValue(CTYPE_VOID),
                                                       Parameter::Vector({new Parameter{swo.clone(), "s"}})};
      returnedList.push_back(f);
    }
    {
      FunctionDeclaration *f = new FunctionDeclaration{"structWithOutsideAnonymousDeclaredStructFunVoid", ReturnValue(swo.clone()),
                                                       Parameter::Vector({})};
      returnedList.push_back(f);
    }
  }
  return returnedList;
}

std::string VoidFunStructWithOutsideDeclaredAnonymousTypeStructFieldFactory::functionGetFunctionName()
{
  return std::string("voidFunStructWithOutsideDeclaredAnonymousTypeStructField");
}

std::string VoidFunStructWithOutsideDeclaredAnonymousTypeStructFieldFactory::getFilename()
{
  return "voidFunStructWithOutsideDeclaredAnonymousTypeStructField.h";
}

