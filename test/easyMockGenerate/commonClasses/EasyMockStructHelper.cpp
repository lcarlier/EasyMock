#include <EasyMockStructHelper.h>

#include <CType.h>

StructType* newStructS1Type()
{
  return new StructType("s1",{new StructField(CTYPE_INT, "a"), new StructField(CTYPE_FLOAT, "b")});
}

Parameter::Vector structS2Parameter()
{
  StructType* s1StructType = newStructS1Type();
  StructField *s1 = new StructField(s1StructType, "s"); //Transfering the ownership of the StructType pointer to StructField object
  s1StructType = nullptr; //Invalidate because not usable anymore.
  Parameter* p = StructParameter("s2", "s",{new StructField(CTYPE_INT, "c"), new StructField(CTYPE_FLOAT, "d"), s1}); //Transfering the ownership of the s1 pointer to the StructParameter class
  s1 = nullptr; //Invalidate because not usable anymore.
  Parameter::Vector funParameter = {p};

  return funParameter;
}