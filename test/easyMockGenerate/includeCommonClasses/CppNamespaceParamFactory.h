#pragma once

#include <ostream>
#include <string>

#include <CppFunctionFactory.h>
#include <cppNamespaceParam.h>

// For making google test work.
inline std::ostream& operator<<(std::ostream& os, ::L1::L2::NameSpaceStruct v)
{
  os << "a: " << v.a;
  return os;
}

// For making google test work.
namespace L1::L2
{
  inline bool operator==(const NameSpaceStruct& lhs, const NameSpaceStruct& rhs)
  {
    return lhs.a == rhs.a;
  }
}

class CppNamespaceParamFactory : public CppFunctionFactory<::L1::L2::NameSpaceStruct, std::tuple<::L1::L2::NameSpaceStruct>, std::tuple<EasyMock::EasyMock_Matcher_Cpp<::L1::L2::NameSpaceStruct>>>
{
public:
  std::shared_ptr<FunctionDeclaration> functionFactory() override;
  ElementToMockList functionFactoryArray() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  void setupTestCase(EasyMockTestCase::TestCase tc) override;

};

class CppNamespaceParamGenerateTypeFactory : public CppNamespaceParamFactory
{
public:
  CppNamespaceParamGenerateTypeFactory() { m_generate_types = true; }
};
