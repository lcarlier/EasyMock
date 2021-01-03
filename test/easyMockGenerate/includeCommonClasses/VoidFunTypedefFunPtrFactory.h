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

#endif /* VOIDFUNTYPEDEFFUNPTRFACTORY_H */

