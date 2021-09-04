#ifndef EASYMOCK_VOIDFUNDECLANDDEFFACTORY_H
#define EASYMOCK_VOIDFUNDECLANDDEFFACTORY_H

#include <FunctionFactory.h>
#include <voidFunDeclAndDef.h>

class VoidFunDeclAndDefFactory : public FunctionFactory<void, std::tuple<char, char>, std::tuple<EasyMock_Matcher, EasyMock_Matcher>>
{
public:
  /*
   * For this test, the function cannot be loaded because there are no function that can be mocked because
   * it is static.
   */
  VoidFunDeclAndDefFactory() { m_load_function = false; }
  ElementToMockList functionFactoryArray() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
};

class VoidFunDeclAndDefGenerateTypeFactory : public VoidFunDeclAndDefFactory
{
public:
  /*
   * For this test, the function can be loaded since the generated mock doesn't use the original header.
   */
  VoidFunDeclAndDefGenerateTypeFactory() { m_load_function = true; m_generate_types = true; }
};

#endif //EASYMOCK_VOIDFUNDECLANDDEFFACTORY_H
