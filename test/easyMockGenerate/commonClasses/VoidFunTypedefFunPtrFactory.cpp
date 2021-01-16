#include "VoidFunTypedefFunPtrFactory.h"
#include "ComposableType.h"
#include "StructType.h"
#include "ComposableField.h"

#include <FunPtrCommonHelper.h>

/*
 * I'm cheating in UT to be able to change private members.
 * The rest of the code is not suppose to be able to do that to make
 * sure sanity checks are done properly
 */

ElementToMockList VoidFunTypedefFunPtrFactory::functionFactoryArray()
{
  ElementToMockList returnedList;

  FunctionDeclaration *fd = getFunPtrDeclaration(0, functionGetFunctionName().c_str());
  Parameter &p = fd->getFunctionsParameters()[0];
  p.setDeclareString("funPtrType");

  p.getType()->m_typedDefName = "funPtrType";
  returnedList.push_back(fd);

  ReturnValue rv2(p.getType()->clone());
  rv2.setDeclareString("funPtrType");
  FunctionDeclaration *fd2 = new FunctionDeclaration("TypedefFunPtrVoid", rv2, Parameter::Vector({}));
  returnedList.push_back(fd2);

  FunctionDeclaration *fd3 = getFunPtrDeclaration(4, "intFunStructTypeDefPtrFunField");
  {
    Parameter &p = fd3->getFunctionsParameters()[0];
    p.setDeclareString("struct typeDefPtrFunField");
    StructType *st = reinterpret_cast<StructType *>(p.getType());
    st->m_name = "typeDefPtrFunField";
    ComposableField &f = dynamic_cast<ComposableField&>(st->getContainedFields()[0]);
    f.setDeclareString("funPtrType");
    f.getType()->m_typedDefName = "funPtrType";
  }
  returnedList.push_back(fd3);

  FunctionDeclaration *fd4 = getFunPtrDeclaration(5, "intFunStructTypeDefPtrAnonFunField");
  {
    Parameter &p = fd4->getFunctionsParameters()[0];
    p.setDeclareString("struct topAnonymousStructTypeDefPtrFunField");
    StructType *st = reinterpret_cast<StructType *>(p.getType());
    st->m_name = "topAnonymousStructTypeDefPtrFunField";
    ComposableField &f = dynamic_cast<ComposableField&>(st->getContainedFields()[1]);
    StructType *sst = reinterpret_cast<StructType *>(f.getType());
    ComposableField &sf = dynamic_cast<ComposableField&>(sst->getContainedFields()[0]);
    sf.setDeclareString("funPtrType");
    sf.getType()->m_typedDefName = "funPtrType";
  }
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
