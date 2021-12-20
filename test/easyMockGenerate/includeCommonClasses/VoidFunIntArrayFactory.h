#ifndef VOIDFUNINTARRAYFACTORY_H
#define VOIDFUNINTARRAYFACTORY_H

#include <FunctionFactory.h>

class VoidFunIntArrayFactory: public FunctionFactory<int, std::tuple<int *>, std::tuple<EasyMock_Matcher>>
{
public:
  FunctionDeclaration functionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  //No setupTestCase. It is covered by PtrFunPtrGenericFactory

};

class VoidFunIntArrayGenerateTypeFactory : public VoidFunIntArrayFactory
{
public:
  VoidFunIntArrayGenerateTypeFactory() { m_generate_types = true; }
};

#endif /* VOIDFUNINTARRAYFACTORY_H */
