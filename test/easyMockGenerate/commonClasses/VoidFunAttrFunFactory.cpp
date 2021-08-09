#include <VoidFunAttrFunFactory.h>

#include <FunctionDeclaration.h>
#include <EasyMock_CType.h>
#include <ConstQualifiedType.h>
#include <Pointer.h>

ElementToMockList VoidFunAttrFunFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  {
    Parameter *p = new Parameter{new Pointer{new ConstQualifiedType{new CType{CTYPE_CHAR}}}, "fmt"};
    p->setDeclareString("const char *");
    FunctionDeclaration *f = new FunctionDeclaration{functionGetFunctionName(), TypedReturnValue(CTYPE_VOID),
                                                     Parameter::Vector({p})};
    p = nullptr; //We lost the ownership
    f->setVariadic(true);
    FunctionAttribute fa{"format", FunctionAttribute::ParametersList{"printf", "1", "2"}};
    f->addAttribute(std::move(fa));
    returnedList.push_back(f);
  }
  {
    Parameter *p2 = new Parameter{new Pointer{new ConstQualifiedType{new CType{CTYPE_CHAR}}}, "fmt"};
    p2->setDeclareString("const char *");
    Parameter *p1 = new Parameter{ new CType {CTYPE_INT}, "a"};
    FunctionDeclaration *f = new FunctionDeclaration{"voidFunAttrFunMacro", TypedReturnValue(CTYPE_VOID),
                                                     Parameter::Vector({p1, p2})};
    p2 = nullptr; //We lost the ownership
    f->setVariadic(true);
    FunctionAttribute fa{"format", FunctionAttribute::ParametersList{"printf", "2", "3"}};
    f->addAttribute(std::move(fa));
    returnedList.push_back(f);
  }
  {
    Parameter *p = new Parameter{new Pointer{new ConstQualifiedType{new CType{CTYPE_CHAR}}}, "fmt"};
    p->setDeclareString("const char *");
    FunctionDeclaration *f = new FunctionDeclaration{"voidFunAttrFunAlwaysInline", TypedReturnValue(CTYPE_VOID),
                                                     Parameter::Vector({p})};
    p = nullptr; //We lost the ownership
    f->setVariadic(true);
    FunctionAttribute fa1{"format", FunctionAttribute::ParametersList{"printf", "1", "2"}};
    FunctionAttribute fa2{"noinline"};
    f->addAttribute(std::move(fa1));
    f->addAttribute(std::move(fa2));
    returnedList.push_back(f);
  }
  {
    FunctionDeclaration *f = new FunctionDeclaration{"voidFunAttrMultiAttr", TypedReturnValue(CTYPE_VOID),
                                                     Parameter::Vector({})};
    FunctionAttribute fa1{"section", FunctionAttribute::ParametersList{".multiAttr.text"}};
    FunctionAttribute fa2{"cold"};
    f->addAttribute(std::move(fa1));
    f->addAttribute(std::move(fa2));
    returnedList.push_back(f);
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
