#include <VoidFunStructWithEmbeddedAnonymousStructFactory.h>

#include <StructType.h>
#include <ComposableField.h>

std::shared_ptr<FunctionDeclaration> VoidFunStructWithEmbeddedAnonymousStructFactory::functionFactory()
{
  bool isEmbeddedStruct = true;
  auto top = std::make_shared<StructType>("topEmbeddedAnonymous", !isEmbeddedStruct); //NOT EMBEDDED
  auto beingDefined = std::make_shared<StructType>("", isEmbeddedStruct);
  beingDefined->addField(ComposableField(CTYPE_INT, "a"));
  top->addField(ComposableField(std::move(beingDefined), "af"));

  Parameter::Vector pv{};
  pv.emplace_back(Parameter(std::move(top), "s"));
  auto f = std::make_shared<FunctionDeclaration>(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), std::move(pv));

  return f;
}

std::string VoidFunStructWithEmbeddedAnonymousStructFactory::functionGetFunctionName()
{
  return std::string("voidFunStructWithEmbeddedAnonymousStruct");
}

std::string VoidFunStructWithEmbeddedAnonymousStructFactory::getFilename()
{
   return "voidFunStructWithEmbeddedAnonymousStruct.h";
}

std::string VoidFunStructWithEmbeddedAnonymousStructFactory::getMatcherFunctionName()
{
  return "cmp_struct_topEmbeddedAnonymous";
}

std::string VoidFunStructWithEmbeddedAnonymousStructFactory::getFieldWrongName()
{
  return "s.af";
}

std::string VoidFunStructWithEmbeddedAnonymousStructFactory::getSubFieldWrongName()
{
  return "a";
}

std::string VoidFunStructWithEmbeddedAnonymousStructFactory::getSubFieldWrongTypeName()
{
  return "topEmbeddedAnonymous::<anonymous>";
}

std::string VoidFunStructWithEmbeddedAnonymousStructFactory::getSubComposableTypeType()
{
  return " struct";
}

void VoidFunStructWithEmbeddedAnonymousStructFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  struct topEmbeddedAnonymous aToExpect;

  aToExpect.af.a = 42;
  switch(tc)
  {
    case EasyMockTestCase::TestCase::OneExpect:
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(m_user_matcher));
      break;
    case EasyMockTestCase::TestCase::OneExpectArgIsBad:
      m_expects.push_back(std::make_tuple(aToExpect));
      aToExpect.af.a++;
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(m_user_matcher));
      break;
    case EasyMockTestCase::TestCase::ThreeExpects:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_expects.push_back(std::make_tuple(aToExpect));
        m_params.push_back(std::make_tuple(aToExpect));
        m_compare.push_back(std::make_tuple(m_user_matcher));
      }
      break;
    case EasyMockTestCase::TestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_expects.push_back(std::make_tuple(aToExpect));
        m_params.push_back(std::make_tuple(aToExpect));
        m_compare.push_back(std::make_tuple(m_user_matcher));
      }
      break;
    case EasyMockTestCase::TestCase::SecondExpectArgIsBad:
    case EasyMockTestCase::TestCase::NoExpect:
      break;
  }
}
