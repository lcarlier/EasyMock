#include <VoidFunStructWithArrayFactory.h>

#include <EasyMockStructHelper.h>
#include <EasyMock_CType.h>
#include <voidFunStructWithArray.h>
#include <ComposableField.h>

FunctionDeclaration VoidFunStructWithArrayFactory::functionFactory()
{
  bool isEmbeddedInOtherType = false;
  StructType *st = new StructType("structWithArray", isEmbeddedInOtherType);
  st->addField(new ComposableField(new CType(CTYPE_INT), "a", { .arraySize = 10 }));
  st->addField(new ComposableField(new CType(CTYPE_INT), "c", { .arraySize = 4 }));
  st->addField(new ComposableField(new CType(CTYPE_INT), "d", { .arraySize = 4 }));
  st->addField(new ComposableField(new CType(CTYPE_INT), "e", { .arraySize = 4 }));
  st->addField(new ComposableField(new CType(CTYPE_INT), "g", { .arraySize = 4 }));
  st->addField(new ComposableField(CTYPE_FLOAT, "f"));

  StructType *fieldArray = new StructType{"fieldArray", isEmbeddedInOtherType};
  fieldArray->addField(new ComposableField{new CType{CTYPE_INT}, "a"});
  st->addField(new ComposableField(fieldArray, "fieldStructArray", { .arraySize = 2 }));

  st->addField(new ComposableField(new CType(CTYPE_INT), "b", { .arraySize = 0}));
  Parameter::Vector p({new Parameter(st, "param")});
  FunctionDeclaration f(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), p);
  return f;
}

FunctionDeclaration* VoidFunStructWithArrayFactory::newFunctionFactory()
{
  return functionFactory().clone();
}

std::string VoidFunStructWithArrayFactory::functionGetFunctionName()
{
  return std::string("voidFunStructWithArray");
}

std::string VoidFunStructWithArrayFactory::getFilename()
{
   return "voidFunStructWithArray.h";
}
