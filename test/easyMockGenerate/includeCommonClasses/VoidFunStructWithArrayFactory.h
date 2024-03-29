#ifndef VOIDFUNSTRUCTWITHARRAYFACTORY_H
#define VOIDFUNSTRUCTWITHARRAYFACTORY_H

#include <FunctionFactory.h>
#include <easyMock.h>
#include <voidFunStructWithArray.h>

class VoidFunStructWithArrayFactory : public FunctionFactory<void, std::tuple<struct structWithArray>, std::tuple<EasyMock_Matcher>>
{
public:
  std::shared_ptr<FunctionDeclaration> functionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;

};

class VoidFunStructWithArrayGenerateTypeFactory : public VoidFunStructWithArrayFactory
{
public:
  VoidFunStructWithArrayGenerateTypeFactory() { m_generate_types = true; }
};

#endif /* VOIDFUNSTRUCTWITHARRAYFACTORY_H */
