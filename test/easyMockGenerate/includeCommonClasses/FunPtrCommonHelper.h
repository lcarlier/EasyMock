#ifndef FUNPTRCOMMONHELPER_H
#define FUNPTRCOMMONHELPER_H

#include <string>
#include <FunctionDeclaration.h>
#include <Pointer.h>

std::shared_ptr<TypeItf> getPointerToFunToTest();

FunctionDeclaration getFunPtrDeclaration(unsigned int n, const char* functionName, std::string&& structName = "", std::string&& typedefName = "");

#endif /* FUNPTRCOMMONHELPER_H */
