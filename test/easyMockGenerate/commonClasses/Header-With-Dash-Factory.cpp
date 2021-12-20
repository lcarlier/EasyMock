#include <Header-With-Dash-Factory.h>

#include <FunctionDeclaration.h>
#include <EasyMock_CType.h>
#include <ConstQualifiedType.h>
#include <Pointer.h>

ElementToMockList HeaderWithDashFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  {
    FunctionDeclaration f{ "header_with_dash", VoidReturnValue(), {}};

    returnedList.push_back(std::move(f));
  }
  return returnedList;
}

std::string HeaderWithDashFactory::functionGetFunctionName()
{
  return std::string("header_with_dash");
}

std::string HeaderWithDashFactory::getFilename()
{
  return "header-with-dash.h";
}
