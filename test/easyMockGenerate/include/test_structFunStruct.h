#ifndef TEST_STRUCTFUNSTRUCT_H
#define TEST_STRUCTFUNSTRUCT_H

#include <FunctionFactory.h>
#include <Parameter.h>
#include <ReturnValue.h>
#include <StructType.h>

class StructFunStructFactory
{
public:

  static std::string getFilename()
  {
    return "structFunStruct.h";
  }
private:
  StructFunStructFactory();
};

StructType* newStructFunStructS1Type()
{
  return new StructType("s1",{new StructField(CTYPE_INT, "a"), new StructField(CTYPE_FLOAT, "b")});
}

ReturnValue structFunStructReturnValue()
{
  ReturnValue rv(newStructFunStructS1Type());

  return rv;
}

Parameter::Vector structFunStructParameters()
{
  StructType* s1StructType = newStructFunStructS1Type();
  StructField *s1 = new StructField(s1StructType, "s");
  s1StructType = nullptr; //Invalidate
  Parameter* p = StructParameter("s2", "a",{new StructField(CTYPE_INT, "c"), new StructField(CTYPE_FLOAT, "d"), s1});
  s1 = nullptr; //Invalidate
  Parameter::Vector funParameter = {p};

  return funParameter;
}

template<>
Function functionFactory<StructFunStructFactory>()
{
  Function f("structFunStruct", structFunStructReturnValue(), structFunStructParameters());
  return f;
}

template<>
Function* newFunctionFactory<StructFunStructFactory>()
{
  return new Function("structFunStruct", structFunStructReturnValue(), structFunStructParameters());
}

#endif /* TEST_STRUCTFUNSTRUCT_H */

