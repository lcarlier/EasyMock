#ifndef FUNPTRCOMMONHELPER_H
#define FUNPTRCOMMONHELPER_H

#include <string>

class FunctionDeclaration;

FunctionDeclaration* getFunPtrDeclaration(unsigned int n, const char* functionName, std::string&& structName = "", std::string&& typedefName = "");

#endif /* FUNPTRCOMMONHELPER_H */

