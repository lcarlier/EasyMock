#ifndef VOIDFUNSTRUCTPTRFACTORY_H
#define VOIDFUNSTRUCTPTRFACTORY_H

#include <FunctionFactory.h>
#include <voidFunStructPtr.h>

class VoidFunStructPtrFactory : public FunctionFactory<void, std::tuple<struct s2*>, std::tuple<EasyMock_Matcher>>
{
public:
  FunctionDeclaration functionFactory() override;
  FunctionDeclaration* newFunctionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;

};

class VoidFunStructPtrGenerateTypeFactory : public VoidFunStructPtrFactory
{
public:
  VoidFunStructPtrGenerateTypeFactory() { m_generate_types = true; }
};

#endif /* VOIDFUNSTRUCTPTRFACTORY_H */

