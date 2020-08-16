#ifndef VOIDFUNFUNPTRFACTORY_H
#define VOIDFUNFUNPTRFACTORY_H

#include <FunctionFactory.h>
#include <easyMock.h>

#include <voidFunFunPtr.h>

class VoidFunFunPtrFactory : public FunctionFactory<int, std::tuple<void*>, std::tuple<EasyMock_Matcher>>
{
public:
  ElementToMockList functionFactoryArray() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;

};

#endif /* VOIDFUNFUNPTRFACTORY_H */

