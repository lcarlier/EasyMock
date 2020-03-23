#include <EasyMockStructHelper.h>

#include <CType.h>
#include <StructType.h>

StructType* newStructS1Type()
{
  bool isEmbeddedInOtherType = false;
  return new StructType("s1", ComposableField::Vector({new ComposableField(CTYPE_INT, "a"), new ComposableField(CTYPE_FLOAT, "b")}), isEmbeddedInOtherType);
}

Parameter::Vector structS2Parameter()
{
  bool isEmbeddedInOtherType = false;
  StructType* s1StructType = newStructS1Type();
  ComposableField *s1 = new ComposableField(s1StructType, "s"); //Transfering the ownership of the StructType pointer to StructField object
  s1StructType = nullptr; //Invalidate because not usable anymore.
  ComposableField* floatStructField = new ComposableField(CTYPE_FLOAT, "d");
  floatStructField->setPointer(true);
  Parameter* p = StructParameter("s2", "s", ComposableField::Vector({new ComposableField(CTYPE_INT, "c"), floatStructField, s1}), isEmbeddedInOtherType); //Transfering the ownership of the s1 pointer to the StructParameter class
  floatStructField = nullptr; //Invalidate because not usable anymore.
  s1 = nullptr; //Invalidate because not usable anymore.
  Parameter::Vector funParameter({p});

  return funParameter;
}
