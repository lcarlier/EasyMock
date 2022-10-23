#ifndef VOIDFUNSTRUCTRECUSNONTYPEDEFFACTORY_H
#define VOIDFUNSTRUCTRECUSNONTYPEDEFFACTORY_H

#include <FunctionFactory.h>
#include <voidFunStructRecursNonTypedef.h>

class VoidFunStructRecusNonTypedefFactory : public FunctionFactory<void, std::tuple<t_s1>, std::tuple<EasyMock_Matcher>>
{
public:
  std::shared_ptr<FunctionDeclaration> functionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;

};

class VoidFunStructRecusNonTypedefGenerateTypeFactory : public VoidFunStructRecusNonTypedefFactory
{
public:
  VoidFunStructRecusNonTypedefGenerateTypeFactory() { m_generate_types = true; }
};

#endif /* VOIDFUNSTRUCTRECUSNONTYPEDEFFACTORY_H */
