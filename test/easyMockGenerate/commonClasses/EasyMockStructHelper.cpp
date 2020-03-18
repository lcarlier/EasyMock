#include <EasyMockStructHelper.h>

#include <CType.h>
#include <StructType.h>

StructType* newStructS1Type()
{
  return new StructType("s1",ComposableField::Vector({new ComposableField(CTYPE_INT, "a"), new ComposableField(CTYPE_FLOAT, "b")}));
}

Parameter::Vector structS2Parameter()
{
  StructType* s1StructType = newStructS1Type();
  ComposableField *s1 = new ComposableField(s1StructType, "s"); //Transfering the ownership of the StructType pointer to StructField object
  s1StructType = nullptr; //Invalidate because not usable anymore.
  ComposableField* floatStructField = new ComposableField(CTYPE_FLOAT, "d");
  floatStructField->setPointer(true);
  Parameter* p = StructParameter("s2", "s",{new ComposableField(CTYPE_INT, "c"), floatStructField, s1}); //Transfering the ownership of the s1 pointer to the StructParameter class
  floatStructField = nullptr; //Invalidate because not usable anymore.
  s1 = nullptr; //Invalidate because not usable anymore.
  Parameter::Vector funParameter = {p};

  return funParameter;
}
