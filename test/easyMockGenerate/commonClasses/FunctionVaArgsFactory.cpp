#include <FunctionVaArgsFactory.h>

#include <EasyMock_CType.h>
#include <ComposableType.h>
#include <Pointer.h>
#include <StructType.h>
#include <ComposableField.h>
#include <TypedefType.h>

ElementToMockList FunctionVaArgsFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  ReturnValue rv{std::make_shared<CType>(CTYPE_VOID)};

  Parameter param1{std::make_shared<CType>(CTYPE_UINT), "a"};

#if defined(__APPLE__)
#if defined(__aarch64__)
  auto va_list_pointer = std::make_shared<TypedefType>("va_list", std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_CHAR)));
  Parameter param2{std::move(va_list_pointer), "args"};
#elif defined(__x86_64__)
  auto vaListArg = std::make_shared<StructType>("__va_list_tag", false);
  vaListArg->addField(ComposableField(std::make_shared<CType>(CTYPE_UINT), "gp_offset"));
  vaListArg->addField(ComposableField(std::make_shared<CType>(CTYPE_UINT), "fp_offset"));
  vaListArg->addField(ComposableField(std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_VOID)), "overflow_arg_area"));
  vaListArg->addField(ComposableField(std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_VOID)), "reg_save_area"));
  vaListArg->setImplicit(true);

  Parameter param2{std::make_shared<Pointer>(std::move(vaListArg)), "args"};
  param2.setDeclareString("va_list");
#else
  #error "Architecture not supported on MacOS"
#endif
#elif defined(__linux__)

#if defined(__aarch64__)
  auto tvaListArg = std::make_shared<TypedefType>("va_list", std::make_shared<StructType>("__va_list", false));
  ComposableType *vaListArg = tvaListArg->getTypee()->asComposableType();
  vaListArg->addField(ComposableField(std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_VOID)), "__stack"));
  vaListArg->addField(ComposableField(std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_VOID)), "__gr_top"));
  vaListArg->addField(ComposableField(std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_VOID)), "__vr_top"));
  vaListArg->addField(ComposableField(std::make_shared<CType>(CTYPE_INT), "__gr_offs"));
  vaListArg->addField(ComposableField(std::make_shared<CType>(CTYPE_INT), "__vr_offs"));

  tvaListArg->setImplicit(true);

  Parameter param2{std::move(tvaListArg), "args"};
#elif defined(__x86_64__)
  auto vaListArg = std::make_shared<StructType>("__va_list_tag", false);
  vaListArg->addField(ComposableField(std::make_shared<CType>(CTYPE_UINT), "gp_offset"));
  vaListArg->addField(ComposableField(std::make_shared<CType>(CTYPE_UINT), "fp_offset"));
  vaListArg->addField(ComposableField(std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_VOID)), "overflow_arg_area"));
  vaListArg->addField(ComposableField(std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_VOID)), "reg_save_area"));
  vaListArg->setImplicit(true);

  Parameter param2{std::make_shared<Pointer>(std::move(vaListArg)), "args"};
  param2.setDeclareString("va_list");
#else //defined(__arch64__)
#error "Architecture not supported on Linux"
#endif //defined(__APPLE__)

#else
#error "OS not supported"
#endif //define(__APPLE+__)

  Parameter::Vector pv{};
  pv.emplace_back(std::move(param1));
  pv.emplace_back(std::move(param2));
  FunctionDeclaration f1(functionGetFunctionName(), std::move(rv), std::move(pv));
  returnedList.push_back(std::move(f1));

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
