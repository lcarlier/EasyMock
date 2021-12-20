#include <VoidFunStructWithArrayFactory.h>

#include <EasyMockStructHelper.h>
#include <EasyMock_CType.h>
#include <voidFunStructWithArray.h>
#include <ComposableField.h>

FunctionDeclaration VoidFunStructWithArrayFactory::functionFactory()
{
  bool isEmbeddedInOtherType = false;
  auto st = std::make_shared<StructType>("structWithArray", isEmbeddedInOtherType);
  st->addField(ComposableField(std::make_shared<CType>(CTYPE_INT), "a", { .arraySize = 10 }));
  st->addField(ComposableField(std::make_shared<CType>(CTYPE_INT), "c", { .arraySize = 4 }));
  st->addField(ComposableField(std::make_shared<CType>(CTYPE_INT), "d", { .arraySize = 4 }));
  st->addField(ComposableField(std::make_shared<CType>(CTYPE_INT), "e", { .arraySize = 4 }));
  st->addField(ComposableField(std::make_shared<CType>(CTYPE_INT), "g", { .arraySize = 4 }));
  st->addField(ComposableField(CTYPE_FLOAT, "f"));

  auto fieldArray = std::make_shared<StructType>("fieldArray", isEmbeddedInOtherType);
  fieldArray->addField(ComposableField{std::make_shared<CType>(CTYPE_INT), "a"});
  st->addField(ComposableField(fieldArray, "fieldStructArray", { .arraySize = 2 }));

  st->addField(ComposableField(std::make_shared<CType>(CTYPE_INT), "b", { .arraySize = 0}));
  Parameter::Vector p{};
  p.emplace_back(Parameter(st, "param"));
  FunctionDeclaration f(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), std::move(p));
  return f;
}

std::string VoidFunStructWithArrayFactory::functionGetFunctionName()
{
  return std::string("voidFunStructWithArray");
}

std::string VoidFunStructWithArrayFactory::getFilename()
{
   return "voidFunStructWithArray.h";
}
