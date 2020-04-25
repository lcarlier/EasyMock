#ifndef MULTIPLEDEFINITIONSFACTORY_H
#define MULTIPLEDEFINITIONSFACTORY_H

#include <FunctionFactory.h>
#include <multipleDefinitions.h>

class MultipleDefinitionsFactory : public FunctionFactory<int, std::tuple<int>, std::tuple<EasyMock_Matcher>>
{
public:
  ElementToMockList functionFactoryArray() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;

};

#endif /* MULTIPLEDEFINITIONSFACTORY_H */

