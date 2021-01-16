#include <FunctionVaArgsFactory.h>

#include <EasyMock_CType.h>
#include <ComposableType.h>
#include <Pointer.h>
#include <StructType.h>
#include <ComposableField.h>

ElementToMockList FunctionVaArgsFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  ReturnValue rv((new CType(CTYPE_VOID)));
  rv.setDeclareString(rv.getType()->getFullDeclarationName());

  Parameter *param1 = new Parameter(new CType(CTYPE_UINT), "a");
  param1->setDeclareString(param1->getType()->getFullDeclarationName());

#if defined(__APPLE__)
  Pointer *va_list_pointer = new Pointer(new CType(CTYPE_CHAR), "va_list", false);
  Parameter* param2 = new Parameter(va_list_pointer, "args");
  param2->setDeclareString("va_list");
#elif defined(__linux__)
#if defined(__aarch64__)
  StructType* vaListArg = new StructType("__va_list", "va_list", false);
  vaListArg->addField(new ComposableField(new Pointer(new CType(CTYPE_VOID)), "__stack"));
  vaListArg->addField(new ComposableField(new Pointer(new CType(CTYPE_VOID)), "__gr_top"));
  vaListArg->addField(new ComposableField(new Pointer(new CType(CTYPE_VOID)), "__vr_top"));
  vaListArg->addField(new ComposableField(new CType(CTYPE_INT), "__gr_offs"));
  vaListArg->addField(new ComposableField(new CType(CTYPE_INT), "__vr_offs"));

  vaListArg->setImplicit(true);

  Parameter* param2 = new Parameter(vaListArg, "args");
  param2->setDeclareString("va_list");
  vaListArg = nullptr;
#elif defined(__x86_64__)
  StructType* vaListArg = new StructType("__va_list_tag", false);
  vaListArg->addField(new ComposableField(new CType(CTYPE_UINT), "gp_offset"));
  vaListArg->addField(new ComposableField(new CType(CTYPE_UINT), "fp_offset"));
  vaListArg->addField(new ComposableField(new Pointer(new CType(CTYPE_VOID)), "overflow_arg_area"));
  vaListArg->addField(new ComposableField(new Pointer(new CType(CTYPE_VOID)), "reg_save_area"));
  vaListArg->setImplicit(true);

  Parameter* param2 = new Parameter(new Pointer(vaListArg), "args");
  param2->setDeclareString("va_list");
  vaListArg = nullptr;
#else
#error "Architecture not supported"
#endif
#else
#error "OS not supported"
#endif

  FunctionDeclaration* f1 = new FunctionDeclaration(functionGetFunctionName(), rv, Parameter::Vector({param1, param2}));
  param1 = nullptr;
  returnedList.push_back(f1);

  return returnedList;
}

std::string FunctionVaArgsFactory::functionGetFunctionName()
{
  return std::string("functionVaArgs");
}

std::string FunctionVaArgsFactory::getFilename()
{
   return "functionVaArgs.h";
}
