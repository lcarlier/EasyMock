#ifndef VOIDFUNINTARRAYFACTORY_H
#define VOIDFUNINTARRAYFACTORY_H

#include <FunctionFactory.h>

class VoidFunIntArrayFactory: public FunctionFactory<int, std::tuple<int *>, std::tuple<EasyMock_Matcher>>
{
public:
  FunctionDeclaration functionFactory() override;
  FunctionDeclaration* newFunctionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  //No setupTestCase. It is covered by PtrFunPtrGenericFactory

};

#endif /* VOIDFUNINTARRAYFACTORY_H */

