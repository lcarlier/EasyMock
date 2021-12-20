#include <VoidFunStructWithEmbeddedStructFactory.h>

#include <StructType.h>
#include <ComposableField.h>

FunctionDeclaration VoidFunStructWithEmbeddedStructFactory::functionFactory()
{
  bool isEmbeddedStruct = true;
  auto top = std::make_shared<StructType>("topEmbedded", !isEmbeddedStruct); //NOT EMBEDDED
  auto beingDefined = std::make_shared<StructType>("embeddedStruct", isEmbeddedStruct);
  beingDefined->addField(ComposableField(CTYPE_INT, "a"));
  top->addField(ComposableField(std::move(beingDefined), "b"));

  Parameter::Vector pv{};
  pv.emplace_back(Parameter(std::move(top), "t"));
  FunctionDeclaration f(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), std::move(pv));
  return f;
}

std::string VoidFunStructWithEmbeddedStructFactory::functionGetFunctionName()
{
  return std::string("voidFunStructWithEmbeddedStruct");
}

std::string VoidFunStructWithEmbeddedStructFactory::getFilename()
{
   return "voidFunStructWithEmbeddedStruct.h";
}

std::string VoidFunStructWithEmbeddedStructFactory::getMatcherFunctionName()
{
  return "cmp_struct_topEmbedded";
}

std::string VoidFunStructWithEmbeddedStructFactory::getFieldWrongName()
{
  return "t.b";
}

std::string VoidFunStructWithEmbeddedStructFactory::getSubFieldWrongName()
{
  return "a";
}

std::string VoidFunStructWithEmbeddedStructFactory::getSubFieldWrongTypeName()
{
  return "topEmbedded::embeddedStruct";
}

std::string VoidFunStructWithEmbeddedStructFactory::getSubComposableTypeType()
{
  return " struct";
}

void VoidFunStructWithEmbeddedStructFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  struct topEmbedded aToExpect;

  aToExpect.b.a = 42;
  switch(tc)
  {
    case EasyMockTestCase::OneExpect:
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(m_user_matcher));
      break;
    case EasyMockTestCase::OneExpectArgIsBad:
      m_expects.push_back(std::make_tuple(aToExpect));
      aToExpect.b.a++;
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(m_user_matcher));
      break;
    case EasyMockTestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_expects.push_back(std::make_tuple(aToExpect));
        m_params.push_back(std::make_tuple(aToExpect));
        m_compare.push_back(std::make_tuple(m_user_matcher));
      }
      break;
    case EasyMockTestCase::ThreeExpects:
    case EasyMockTestCase::SecondExpectArgIsBad:
    case EasyMockTestCase::NoExpect:
      break;
  }
}
