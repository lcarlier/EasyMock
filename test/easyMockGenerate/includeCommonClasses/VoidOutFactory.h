#ifndef VOIDOUTFACTORY_H
#define VOIDOUTFACTORY_H

#include <FunctionFactory.h>
#include <voidOut.h>

class VoidOutFactory : public FunctionFactory<void, std::tuple<void *>, std::tuple<EasyMock_Matcher>>
{
public:
  ElementToMockList functionFactoryArray() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;

};

#endif /* VOIDOUTFACTORY_H */

