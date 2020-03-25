#ifndef VOIDFUNUNIONWITHEMBEDDEDANONYMOUSUNIONFACTORY_H
#define VOIDFUNUNIONWITHEMBEDDEDANONYMOUSUNIONFACTORY_H

#include <FunctionFactory.h>
#include <voidFunUnionWithEmbeddedAnonymousUnion.h>

class VoidFunUnionWithEmbeddedAnonymousUnionFactory : public FunctionFactory<int, std::tuple<union topEmbeddedAnonymousUnion>, std::tuple<EasyMock_Matcher>>
{
public:
  Function functionFactory() override;
  Function* newFunctionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;

};

#endif /* VOIDFUNUNIONWITHEMBEDDEDANONYMOUSUNIONFACTORY_H */

