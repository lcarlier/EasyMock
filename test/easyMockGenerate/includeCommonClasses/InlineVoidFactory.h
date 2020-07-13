#ifndef INLINEVOIDFACTORY_H
#define INLINEVOIDFACTORY_H

#include <FunctionFactory.h>
#include <inlineVoid.h>

class InlineVoidFactory : public FunctionFactory<int, std::tuple<>, std::tuple<>>
{
public:
  ElementToMockList functionFactoryArray() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;

};

#endif /* INLINEVOIDFACTORY_H */

