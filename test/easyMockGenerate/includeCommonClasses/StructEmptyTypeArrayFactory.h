#ifndef EASYMOCK_STRUCTEMPTYTYPEARRAYFACTORY_H
#define EASYMOCK_STRUCTEMPTYTYPEARRAYFACTORY_H

#include <FunctionFactory.h>
#include <structEmptyTypeArray.h>

class StructEmptyTypeArrayFactory : public FunctionFactory<void, std::tuple<struct emptyTypeArray>, std::tuple<EasyMock_Matcher>>
{
public:
  ElementToMockList functionFactoryArray() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;

};

class StructEmptyTypeArrayGenerateTypeFactory : public StructEmptyTypeArrayFactory
{
public:
  StructEmptyTypeArrayGenerateTypeFactory() { m_generate_types = true; }
};

#endif //EASYMOCK_STRUCTEMPTYTYPEARRAYFACTORY_H
