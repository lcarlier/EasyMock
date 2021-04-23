#ifndef EASYMOCK_VOIDFUNMULTILINEFACTORY_H
#define EASYMOCK_VOIDFUNMULTILINEFACTORY_H

#include <FunctionFactory.h>
#include <easyMock.h>
#include <voidFunMultiline.h>

class VoidFunMultilineFactory : public FunctionFactory<void, std::tuple<int, int>, std::tuple<EasyMock_Matcher, EasyMock_Matcher>>
{
public:
FunctionDeclaration functionFactory() override;
std::string functionGetFunctionName() override;
std::string getFilename() override;

};

class VoidFunMultilineGenerateTypeFactory : public VoidFunMultilineFactory
{
public:
  VoidFunMultilineGenerateTypeFactory() { m_generate_types = true; }
};

#endif //EASYMOCK_VOIDFUNMULTILINEFACTORY_H
