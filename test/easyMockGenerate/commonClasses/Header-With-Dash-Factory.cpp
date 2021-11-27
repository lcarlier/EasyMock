#include <Header-With-Dash-Factory.h>

#include <FunctionDeclaration.h>
#include <EasyMock_CType.h>
#include <ConstQualifiedType.h>
#include <Pointer.h>

ElementToMockList HeaderWithDashFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  {
    FunctionDeclaration *f = new FunctionDeclaration{ "header_with_dash", VoidReturnValue(), Parameter::Vector ({})};

    returnedList.push_back(f);
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
