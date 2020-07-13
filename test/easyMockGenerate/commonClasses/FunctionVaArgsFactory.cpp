#include <FunctionVaArgsFactory.h>

#include <CType.h>
#include <ComposableType.h>
#include <Pointer.h>
#include <StructType.h>

ElementToMockList FunctionVaArgsFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  ReturnValue rv((new CType(CTYPE_VOID)));
  rv.setDeclareString(rv.getType()->getFullDeclarationName());

  Parameter *param1 = new Parameter(new CType(CTYPE_UINT), "a");
  param1->setDeclareString(param1->getType()->getFullDeclarationName());

  StructType* vaListArg = new StructType("__va_list_tag", false);
  vaListArg->addField(new ComposableField(new CType(CTYPE_UINT), "gp_offset"));
  vaListArg->addField(new ComposableField(new CType(CTYPE_UINT), "fp_offset"));
  vaListArg->addField(new ComposableField(new Pointer(new CType(CTYPE_VOID)), "overflow_arg_area"));
  vaListArg->addField(new ComposableField(new Pointer(new CType(CTYPE_VOID)), "reg_save_area"));
  vaListArg->setImplicit(true);

  Parameter* param2 = new Parameter(new Pointer(vaListArg), "args");
  param2->setDeclareString("va_list");
  vaListArg = nullptr;

  Function* f1 = new Function(functionGetFunctionName(), rv, Parameter::Vector({param1, param2}));
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
