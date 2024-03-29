#include "CrossDefinedFunCrossDefinedFactory.h"

#include <Declarator.h>
#include <EasyMock_CType.h>
#include <Parameter.h>
#include <FunctionDeclaration.h>

ElementToMockList CrossDefinedFunCrossDefinedFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  auto intType = std::make_shared<CType>(CTYPE_INT);
  auto floatType = std::make_shared<CType>(CTYPE_FLOAT);
  ReturnValue rv(std::move(floatType));
  rv.setDeclareString("DEF2");

  {
    Parameter p{std::move(intType), "p"};
    p.setDeclareString("DEF1");
    Parameter::Vector pv{};
    pv.emplace_back(std::move(p));
    auto fd = std::make_shared<FunctionDeclaration>(functionGetFunctionName(), std::move(rv), std::move(pv));
    returnedList.push_back(std::move(fd));
  }
  return returnedList;
}

std::string CrossDefinedFunCrossDefinedFactory::functionGetFunctionName()
{
  return std::string("crossDefinedFunCrossDefined");
}

ElementToMockContext::MacroDefinitionList CrossDefinedFunCrossDefinedFactory::getDefinedMacroList()
{
  ElementToMockContext::MacroDefinitionList  ml;

  ml.try_emplace("DEF1","DEF1", "int");
  ml.try_emplace("DEF2","DEF2", "float");
  /*
   * When defining complex macros, spaces are added in between each token, for that reason
   * some extra space may appear in this definition (e.g. after a parenthesis), while it
   * is not in the original macro definition. However this is acceptable because it doesn't
   * change the semantic of the macro.
   */
  ml.try_emplace("FUN_TYPE_MACRO","FUN_TYPE_MACRO",std::vector<std::string>{"a", "b"},
                 "do { "
                 "printf ( \"foo %d\" , a ) ; "
                 "printf ( \"bar %d\" , b ) ; "
                 "}");
  ml.try_emplace("TM_PRINTF","TM_PRINTF",std::vector<std::string>{"f_","..."},"printf ( ( f_ ) , __VA_ARGS__ )");
  ml.try_emplace("BIGER_THAN_ZERO", "BIGER_THAN_ZERO", std::vector<std::string>{"x"},"( x > 0 )");

  return ml;
}

std::string CrossDefinedFunCrossDefinedFactory::getFilename()
{
  return "crossDefinedFunCrossDefined.h";
}
