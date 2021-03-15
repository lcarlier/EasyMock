#include "VoidFunTypedefFunPtrFactory.h"
#include "ComposableType.h"
#include "StructType.h"
#include "ComposableField.h"
#include "TypedefType.h"

#include <FunPtrCommonHelper.h>

ElementToMockList VoidFunTypedefFunPtrFactory::functionFactoryArray()
{
  ElementToMockList returnedList;

  FunctionDeclaration *fd = getFunPtrDeclaration(0, functionGetFunctionName().c_str(), "", "funPtrType");
  Parameter &p = fd->getFunctionsParameters()[0];

  returnedList.push_back(fd);

  ReturnValue rv2(p.getType()->clone());
  FunctionDeclaration *fd2 = new FunctionDeclaration("TypedefFunPtrVoid", rv2, Parameter::Vector({}));
  returnedList.push_back(fd2);

  FunctionDeclaration *fd3 = getFunPtrDeclaration(4, "intFunStructTypeDefPtrFunField", "typeDefPtrFunField", "funPtrType");
  returnedList.push_back(fd3);

  FunctionDeclaration *fd4 = getFunPtrDeclaration(5, "intFunStructTypeDefPtrAnonFunField", "topAnonymousStructTypeDefPtrFunField", "funPtrType");
  returnedList.push_back(fd4);

  return returnedList;
}

std::string VoidFunTypedefFunPtrFactory::functionGetFunctionName()
{
  return std::string("voidFunTypedefFunPtr");
}

std::string VoidFunTypedefFunPtrFactory::getFilename()
{
  return "voidFunTypedefFunPtr.h";
}
