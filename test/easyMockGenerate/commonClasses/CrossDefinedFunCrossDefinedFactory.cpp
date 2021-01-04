#include "CrossDefinedFunCrossDefinedFactory.h"

#include <Declarator.h>
#include <EasyMock_CType.h>
#include <Parameter.h>
#include <FunctionDeclaration.h>

ElementToMockList CrossDefinedFunCrossDefinedFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  CType intType(CTYPE_INT, false);
  CType floatType(CTYPE_FLOAT, false);
  ReturnValue rv(floatType.clone());
  rv.setDeclareString("DEF2");

  Parameter* p = new Parameter(intType.clone(), "p");
  p->setDeclareString("DEF1");

  {
    FunctionDeclaration *fd = new FunctionDeclaration(functionGetFunctionName(), rv, Parameter::Vector({p}));
    returnedList.push_back(fd);
  }
  return returnedList;
}

std::string CrossDefinedFunCrossDefinedFactory::functionGetFunctionName()
{
  return std::string("crossDefinedFunCrossDefined");
}

DefinedMacroList CrossDefinedFunCrossDefinedFactory::getDefinedMacroList()
{
  DefinedMacroList ml;

  ml.insert({"DEF1", "int"});
  ml.insert({"DEF2", "float"});

  return ml;
}

std::string CrossDefinedFunCrossDefinedFactory::getFilename()
{
  return "crossDefinedFunCrossDefined.h";
}
