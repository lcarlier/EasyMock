#include "VoidFunFunPtrFactory.h"

#include <FunctionDeclaration.h>
#include <FunPtrCommonHelper.h>

ElementToMockList VoidFunFunPtrFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  returnedList.push_back(getFunPtrDeclaration(0, functionGetFunctionName().c_str()));
  returnedList.push_back(getFunPtrDeclaration(1, "funPtrFunPtr"));
  returnedList.push_back(getFunPtrDeclaration(2, "funPtrFunChar"));
  returnedList.push_back(getFunPtrDeclaration(3, "ptrFunToFunFunInt"));
  returnedList.push_back(getFunPtrDeclaration(4, "intFunStructPtrFunField", "ptrFunField"));
  returnedList.push_back(getFunPtrDeclaration(5, "intFunStructPtrAnonFunField", "topAnonymousStructPtrFunField"));
  /*
   * TO BE ENABLED WHEN SUPPORT OF CONST POINTER IS ADDED
   */
#if 0
  returnedList.push_back(getFunPtrDeclaration(6, "constFunPtrFunInt"));
#endif
  return returnedList;
}

std::string VoidFunFunPtrFactory::functionGetFunctionName()
{
  return std::string("voidFunFunPtr");
}

std::string VoidFunFunPtrFactory::getFilename()
{
  return "voidFunFunPtr.h";
}