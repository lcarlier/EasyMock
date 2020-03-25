#ifndef VOIDFUNUNIONWITHEMBEDDEDUNIONFACTORY_H
#define VOIDFUNUNIONWITHEMBEDDEDUNIONFACTORY_H

#include <FunctionFactory.h>
#include <voidFunUnionWithEmbeddedUnion.h>

class VoidFunUnionWithEmbeddedUnionFactory : public FunctionFactory<int, std::tuple<union topEmbeddedUnion>, std::tuple<EasyMock_Matcher>>
{
public:
  Function functionFactory() override;
  Function* newFunctionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;

};

#endif /* VOIDFUNUNIONWITHEMBEDDEDUNIONFACTORY_H */

