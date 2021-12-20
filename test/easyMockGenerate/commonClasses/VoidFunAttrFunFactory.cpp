#include <VoidFunAttrFunFactory.h>

#include <FunctionDeclaration.h>
#include <EasyMock_CType.h>
#include <ConstQualifiedType.h>
#include <Pointer.h>

ElementToMockList VoidFunAttrFunFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  {
    Parameter::Vector pv{};
    pv.emplace_back(Parameter{std::make_shared<Pointer>(std::make_shared<ConstQualifiedType>(std::make_shared<CType>(CTYPE_CHAR))), "fmt"});
    FunctionDeclaration f{functionGetFunctionName(), VoidReturnValue(), std::move(pv)};
    f.setVariadic(true);
    FunctionAttribute fa{"format", FunctionAttribute::ParametersList{"printf", "1", "2"}};
    f.addAttribute(std::move(fa));
    returnedList.push_back(std::move(f));
  }
  {
    Parameter::Vector pv{};
    pv.emplace_back(Parameter{std::make_shared<CType>(CTYPE_INT), "a"});
    pv.emplace_back(Parameter{std::make_shared<Pointer>(std::make_shared<ConstQualifiedType>(std::make_shared<CType>(CTYPE_CHAR))), "fmt"});
    FunctionDeclaration f{"voidFunAttrFunMacro", VoidReturnValue(), std::move(pv)};
    f.setVariadic(true);
    FunctionAttribute fa{"format", FunctionAttribute::ParametersList{"printf", "2", "3"}};
    f.addAttribute(std::move(fa));
    returnedList.push_back(std::move(f));
  }
  {
    Parameter::Vector pv{};
    pv.emplace_back(Parameter{std::make_shared<Pointer>(std::make_shared<ConstQualifiedType>(std::make_shared<CType>(CTYPE_CHAR))), "fmt"});
    FunctionDeclaration f{"voidFunAttrFunAlwaysInline", VoidReturnValue(), std::move(pv)};
    f.setVariadic(true);
    FunctionAttribute fa1{"format", FunctionAttribute::ParametersList{"printf", "1", "2"}};
    FunctionAttribute fa2{"noinline"};
    f.addAttribute(std::move(fa1));
    f.addAttribute(std::move(fa2));
    returnedList.push_back(std::move(f));
  }
  {
    FunctionDeclaration f{"voidFunAttrMultiAttr", VoidReturnValue(),
                                                     {}};
    FunctionAttribute fa1{"section", FunctionAttribute::ParametersList{"__DATA__,.multiAttr.text"}};
    FunctionAttribute fa2{"cold"};
    f.addAttribute(std::move(fa1));
    f.addAttribute(std::move(fa2));
    returnedList.push_back(std::move(f));
  }
  {
    FunctionDeclaration f{"voidFunNoReturn", VoidReturnValue(), {}};
    f.addAttribute(FunctionAttribute{"noreturn"});

    returnedList.push_back(std::move(f));
  }
  {
    FunctionDeclaration f{ "__bad_copy_from", VoidReturnValue(), {}};

    returnedList.push_back(std::move(f));
  }
  return returnedList;
}

std::string VoidFunAttrFunFactory::functionGetFunctionName()
{
  return std::string("voidFunAttrFun");
}

std::string VoidFunAttrFunFactory::getFilename()
{
  return "voidFunAttrFun.h";
}
