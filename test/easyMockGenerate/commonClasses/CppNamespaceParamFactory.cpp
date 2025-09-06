#include <CppNamespaceParamFactory.h>
#include <FunctionFactory.h>
#include <Namespace.h>
#include <StructType.h>
#include <EasyMock_CType.h>

// Copy and paste from the mock
static bool cmp_struct_NameSpaceStruct(const ::L1::L2::NameSpaceStruct& currentCall_val, const ::L1::L2::NameSpaceStruct& expectedCall_val, const std::string paramName, std::ostringstream& errorMessage )
{
  if(currentCall_val.a != expectedCall_val.a)
  {
    errorMessage << "Parameter '" << paramName << "' which is a struct of type 'NameSpaceStruct' has field 'a' with value '" << currentCall_val.a << "', was expecting '" << expectedCall_val.a << "'";
    return true;
  }
  return false;
}

std::shared_ptr<FunctionDeclaration> CppNamespaceParamFactory::functionFactory()
{
  auto funNamespace = std::make_shared<const Namespace>("L2", std::make_shared<const Namespace>("L1"));
  ComposableType::ComposableFieldTypeVector fieldVector{};
  fieldVector.emplace_back(ComposableField(CTYPE_INT, "a"));
  static constexpr bool isEmbeddedInOtherType = false;
  auto structType = std::make_shared<StructType>("NameSpaceStruct", std::move(fieldVector), isEmbeddedInOtherType, funNamespace);
  Parameter::Vector params;
  Parameter param {structType, "param"};
  param.setDeclareString("::L1::L2::NameSpaceStruct");
  params.push_back(std::move(param));
  ReturnValue rv{structType};
  rv.setDeclareString("::L1::L2::NameSpaceStruct");
  return std::make_shared<FunctionDeclaration>("funParamNamespace", std::move(rv), std::move(params));
}

ElementToMockList CppNamespaceParamFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  returnedList.push_back(functionFactory());
  return returnedList;
}

std::string CppNamespaceParamFactory::functionGetFunctionName()
{
  return std::string("funParamNamespace");
}

std::string CppNamespaceParamFactory::getFilename()
{
  return "cppNamespaceParam.h";
}

void CppNamespaceParamFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  switch(tc)
  {
    case EasyMockTestCase::TestCase::OneExpect:
      m_rvContext.m_rv.push_back(::L1::L2::NameSpaceStruct{5});
      m_expects.push_back(std::make_tuple(::L1::L2::NameSpaceStruct{6}));
      m_params.push_back(::L1::L2::NameSpaceStruct{6});
      m_compare.push_back(std::make_tuple(cmp_struct_NameSpaceStruct));
      break;
    case EasyMockTestCase::TestCase::ThreeExpects:
    {
      const auto aOneToExpect = ::L1::L2::NameSpaceStruct{5};
      const auto rvToExpect = ::L1::L2::NameSpaceStruct{7};
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        auto finalRvToExpect = rvToExpect;
        finalRvToExpect.a += expectIdx;
        auto finalParamToExpect = aOneToExpect;
        finalParamToExpect.a += expectIdx;
        m_rvContext.m_rv.push_back(finalRvToExpect);
        m_expects.push_back(std::make_tuple(finalParamToExpect));
        m_params.push_back(std::make_tuple(finalParamToExpect));
        m_compare.push_back(std::make_tuple(cmp_struct_NameSpaceStruct));
      }
      break;
    }
    case EasyMockTestCase::TestCase::OneExpectArgIsBad:
      m_rvContext.m_rv.push_back(::L1::L2::NameSpaceStruct{5});
      m_expects.push_back(std::make_tuple(::L1::L2::NameSpaceStruct{6}));
      m_params.push_back(std::make_tuple(::L1::L2::NameSpaceStruct{7}));
      m_compare.push_back(std::make_tuple(cmp_struct_NameSpaceStruct));
      break;
    case EasyMockTestCase::TestCase::SecondExpectArgIsBad:
      m_rvContext.m_rv.push_back(::L1::L2::NameSpaceStruct{5});
      m_expects.push_back(std::make_tuple(::L1::L2::NameSpaceStruct{6}));
      m_params.push_back(std::make_tuple(::L1::L2::NameSpaceStruct{6}));
      m_compare.push_back(std::make_tuple(cmp_struct_NameSpaceStruct));

      m_rvContext.m_rv.push_back(::L1::L2::NameSpaceStruct{6});
      m_expects.push_back(::L1::L2::NameSpaceStruct{7});
      m_params.push_back(::L1::L2::NameSpaceStruct{8}); //Second call fails
      m_compare.push_back(std::make_tuple(cmp_struct_NameSpaceStruct));
      break;
    case EasyMockTestCase::TestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(::L1::L2::NameSpaceStruct{5});
        m_expects.push_back(::L1::L2::NameSpaceStruct{6});
        m_params.push_back(::L1::L2::NameSpaceStruct{6});
        m_compare.push_back(std::make_tuple(cmp_struct_NameSpaceStruct));
      }
      break;
    case EasyMockTestCase::TestCase::NoExpect:
      break;
  }
}
