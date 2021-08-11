#ifndef EASYMOCK_VOIDFUNEMBEDDEDCOMMENTSFACTORY_H
#define EASYMOCK_VOIDFUNEMBEDDEDCOMMENTSFACTORY_H

#include <FunctionFactory.h>
#include <voidFunEmbeddedComments.h>

class VoidFunEmbeddedCommentsFactory : public FunctionFactory<void, std::tuple<int, const char *, int>, std::tuple<EasyMock_Matcher, EasyMock_Matcher, EasyMock_Matcher>>
{
public:
  ElementToMockList functionFactoryArray() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  ElementToMockContext::MacroDefinitionList getDefinedMacroList() override;

};

class VoidFunEmbeddedCommentsGenerateTypeFactory : public VoidFunEmbeddedCommentsFactory
{
public:
  VoidFunEmbeddedCommentsGenerateTypeFactory() { m_generate_types = true; }
};

#endif //EASYMOCK_VOIDFUNEMBEDDEDCOMMENTSFACTORY_H
