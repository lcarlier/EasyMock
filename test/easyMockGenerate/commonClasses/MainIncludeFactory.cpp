#include <MainIncludeFactory.h>
#include <FunctionFactory.h>
#include <ReturnValue.h>

ElementToMockList MainIncludeFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  {
    FunctionDeclaration f{ "mainIncludeToBeTaken", VoidReturnValue(), {}};

    returnedList.push_back(std::move(f));
  }
  return returnedList;
}

std::string MainIncludeFactory::functionGetFunctionName()
{
  return std::string("mainIncludeToBeTaken");
}

std::string MainIncludeFactory::getFilename()
{
  return "mainInclude.h";
}
