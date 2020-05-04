#ifndef FUNCTIONVAARGSFACTORY_H
#define FUNCTIONVAARGSFACTORY_H

#include <FunctionFactory.h>
#include <functionVaArgs.h>

class FunctionVaArgsFactory : public FunctionFactory<int, std::tuple<int, va_list>, std::tuple<EasyMock_Matcher, EasyMock_Matcher>>
{
public:
  ElementToMockList functionFactoryArray() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;

};

#endif /* FUNCTIONVAARGSFACTORY_H */

