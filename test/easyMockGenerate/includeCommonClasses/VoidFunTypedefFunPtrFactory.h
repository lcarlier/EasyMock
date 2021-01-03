#ifndef VOIDFUNTYPEDEFFUNPTRFACTORY_H
#define VOIDFUNTYPEDEFFUNPTRFACTORY_H

#include <FunctionFactory.h>
#include <voidFunTypedefFunPtr.h>

class VoidFunTypedefFunPtrFactory : public FunctionFactory<void, std::tuple<struct s2*>, std::tuple<EasyMock_Matcher>>
{
public:
  ElementToMockList functionFactoryArray() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;

};

class VoidFunTypedefFunPtrGenerateTypeFactory : public VoidFunTypedefFunPtrFactory
{
public:
  VoidFunTypedefFunPtrGenerateTypeFactory()
  {
    m_generate_types=true;
  }
};

#endif /* VOIDFUNTYPEDEFFUNPTRFACTORY_H */

