#ifndef EASYMOCK_MAININCLUDEFACTORY_H
#define EASYMOCK_MAININCLUDEFACTORY_H

#include <FunctionFactory.h>
#include <MainIncludeFactory.h>

class MainIncludeFactory : public FunctionFactory<void, std::tuple<>, std::tuple<>>
{
public:
  ElementToMockList functionFactoryArray() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;

};

class MainIncludeGenerateTypeFactory : public MainIncludeFactory
{
public:
  MainIncludeGenerateTypeFactory() { m_generate_types = true; }
};

#endif //EASYMOCK_MAININCLUDEFACTORY_H
