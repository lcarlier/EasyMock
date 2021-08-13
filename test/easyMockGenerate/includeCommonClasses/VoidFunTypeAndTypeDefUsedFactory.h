#ifndef EASYMOCK_VOIDFUNTYPEANDTYPEDEFUSEDFACTORY_H
#define EASYMOCK_VOIDFUNTYPEANDTYPEDEFUSEDFACTORY_H

#include <FunctionFactory.h>
#include <easyMock.h>

#include <voidFunTypeAndTypeDefUsed.h>

class VoidFunTypeAndTypeDefUsedFactory : public FunctionFactory<void, std::tuple<struct notTypedefUsed>, std::tuple<EasyMock_Matcher>>
{
public:
  VoidFunTypeAndTypeDefUsedFactory() { m_rm_dir = false; }
  ElementToMockList functionFactoryArray() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;

};

class VoidFunTypeAndTypeDefUsedGenerateTypeFactory : public VoidFunTypeAndTypeDefUsedFactory
{
public:
  VoidFunTypeAndTypeDefUsedGenerateTypeFactory() { m_rm_dir = false, m_generate_types = true; }
};

#endif //EASYMOCK_VOIDFUNTYPEANDTYPEDEFUSEDFACTORY_H
