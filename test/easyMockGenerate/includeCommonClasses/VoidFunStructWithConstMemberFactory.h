#ifndef VOIDFUNSTRUCTWITHCONSTMEMBERFACTORY_H
#define VOIDFUNSTRUCTWITHCONSTMEMBERFACTORY_H

#include <FunctionFactory.h>
#include <easyMock.h>

#include <voidFunStructWithConstMember.h>

class VoidFunStructWithConstMemberFactory : public FunctionFactory<void, std::tuple<struct structWithConstMember>, std::tuple<EasyMock_Matcher>>
{
public:
  ElementToMockList functionFactoryArray() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;

};

class VoidFunStructWithConstMemberGenerateTypeFactory : public VoidFunStructWithConstMemberFactory
{
  VoidFunStructWithConstMemberGenerateTypeFactory() { m_generate_types = true; }
};

#endif /* VOIDFUNSTRUCTWITHCONSTMEMBERFACTORY_H */

