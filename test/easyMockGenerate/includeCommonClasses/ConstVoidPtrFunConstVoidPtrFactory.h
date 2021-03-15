#ifndef EASYMOCK_CONSTVOIDPTRFUNCONSTVOIDPTRFACTORY_H
#define EASYMOCK_CONSTVOIDPTRFUNCONSTVOIDPTRFACTORY_H

#include <FunctionFactory.h>
#include <easyMock.h>

class ConstVoidPtrFunConstVoidPtrFactory : public FunctionFactory<const void*, std::tuple<const void *>, std::tuple<EasyMock_Matcher>>
{
public:
  FunctionDeclaration functionFactory() override;
  FunctionDeclaration* newFunctionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
};

class ConstVoidPtrFunConstVoidPtrGenerateTypeFactory : public ConstVoidPtrFunConstVoidPtrFactory
{
  ConstVoidPtrFunConstVoidPtrGenerateTypeFactory() : ConstVoidPtrFunConstVoidPtrFactory()
  {
    m_generate_types = true;
  }
};

#endif //EASYMOCK_CONSTVOIDPTRFUNCONSTVOIDPTRFACTORY_H
