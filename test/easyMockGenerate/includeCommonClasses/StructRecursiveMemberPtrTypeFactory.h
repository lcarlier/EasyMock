#ifndef STRUCTRECURSIVEMEMBERPTRTYPEFACTORY_H
#define STRUCTRECURSIVEMEMBERPTRTYPEFACTORY_H

#include <FunctionFactory.h>
#include <easyMock.h>
#include <structRecursivePtrType.h>

class StructRecursiveMemberPtrTypeFactory : public FunctionFactory<unsigned short, std::tuple<struct recurs>, std::tuple<EasyMock_Matcher>>
{
public:
  std::shared_ptr<FunctionDeclaration> functionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
};

class StructRecursiveMemberPtrTypeGenerateTypeFactory : public StructRecursiveMemberPtrTypeFactory
{
public:
  StructRecursiveMemberPtrTypeGenerateTypeFactory() { m_generate_types = true; }
};

#endif /* STRUCTRECURSIVEMEMBERPTRTYPEFACTORY_H */

