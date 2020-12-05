#ifndef CROSSDEFINEDFUNCROSSDEFINEDFACTORY_H
#define CROSSDEFINEDFUNCROSSDEFINEDFACTORY_H

#include <FunctionFactory.h>
#include <crossDefinedFunCrossDefined.h>

class CrossDefinedFunCrossDefinedFactory: public FunctionFactory<DEF2, std::tuple<DEF1>, std::tuple<EasyMock_Matcher>>
{
public:
  ElementToMockList functionFactoryArray() override;
  std::string functionGetFunctionName() override;
  DefinedMacroList getDefinedMacroList() override;
  std::string getFilename() override;

};

class CrossDefinedFunCrossDefinedGenTypeFactory : public CrossDefinedFunCrossDefinedFactory
{
public:
    CrossDefinedFunCrossDefinedGenTypeFactory() : CrossDefinedFunCrossDefinedFactory()
    {
      m_generate_types = true;
    }
};

#endif /* CROSSDEFINEDFUNCROSSDEFINEDFACTORY_H */

