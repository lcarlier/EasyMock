#ifndef EASYMOCK_HEADER_WITH_DASH_FACTORY_H
#define EASYMOCK_HEADER_WITH_DASH_FACTORY_H

#include <FunctionFactory.h>
#include <header-with-dash.h>

class HeaderWithDashFactory : public FunctionFactory<void, std::tuple<>, std::tuple<>>
{
public:
  ElementToMockList functionFactoryArray() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;

};

class HeaderWithDashGenerateTypeFactory : public HeaderWithDashFactory
{
public:
  HeaderWithDashGenerateTypeFactory() { m_generate_types = true; }
};

#endif //EASYMOCK_HEADER_WITH_DASH_FACTORY_H
