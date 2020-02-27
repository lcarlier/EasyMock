#include <EasyMockStructHelper.h>

#include <CType.h>

StructType* newStructS1Type()
{
  return new StructType("s1",StructField::Vector({new StructField(CTYPE_INT, "a"), new StructField(CTYPE_FLOAT, "b")}));
}

Parameter::Vector structS2Parameter()
{
  StructType* s1StructType = newStructS1Type();
  StructField *s1 = new StructField(s1StructType, "s"); //Transfering the ownership of the StructType pointer to StructField object
  s1StructType = nullptr; //Invalidate because not usable anymore.
  StructField* floatStructField = new StructField(CTYPE_FLOAT, "d");
  floatStructField->setPointer(true);
  Parameter* p = StructParameter("s2", "s",{new StructField(CTYPE_INT, "c"), floatStructField, s1}); //Transfering the ownership of the s1 pointer to the StructParameter class
  floatStructField = nullptr; //Invalidate because not usable anymore.
  s1 = nullptr; //Invalidate because not usable anymore.
  Parameter::Vector funParameter = {p};

  return funParameter;
}
