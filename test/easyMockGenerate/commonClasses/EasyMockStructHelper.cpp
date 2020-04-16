#include <EasyMockStructHelper.h>

#include <CType.h>
#include <StructType.h>
#include <Pointer.h>

StructType* newStructS1Type()
{
  bool isEmbeddedInOtherType = false;
  return new StructType("s1", ComposableField::Vector({new ComposableField(CTYPE_INT, "a"), new ComposableField(CTYPE_FLOAT, "b")}), isEmbeddedInOtherType);
}

StructType* newStructS2Type()
{
  bool isEmbeddedInOtherType = false;
  StructType* s1StructType = newStructS1Type();
  ComposableField *s1 = new ComposableField(s1StructType, "s"); //Transfering the ownership of the StructType pointer to StructField object
  s1StructType = nullptr; //Invalidate because not usable anymore.
  ComposableField* floatStructField = new ComposableField(new Pointer(new CType(CTYPE_FLOAT)), "d");
  StructType *s2 = new StructType("s2", ComposableField::Vector({new ComposableField(CTYPE_INT, "c"), floatStructField, s1}), isEmbeddedInOtherType);
  floatStructField = nullptr; //Invalidate because not usable anymore.
  s1 = nullptr; //Invalidate because not usable anymore.

  return s2;
}

Parameter::Vector structS2Parameter()
{
  StructType* s2 = newStructS2Type();
  Parameter* p = new Parameter(s2, "s");
  s2 = nullptr; //Invalidate because not usable anymore

  Parameter::Vector funParameter({p});

  return funParameter;
}
