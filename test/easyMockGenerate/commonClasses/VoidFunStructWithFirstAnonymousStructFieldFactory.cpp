#include <VoidFunStructWithFirstAnonymousStructFieldFactory.h>

#include <StructType.h>
#include <ComposableField.h>

FunctionDeclaration VoidFunStructWithFirstAnonymousStructFieldFactory::functionFactory()
{
  bool isEmbeddedStruct = true;
  auto top = std::make_shared<StructType>("topAnonymousFirstStructField", !isEmbeddedStruct); //NOT EMBEDDED
  auto beingDefined = std::make_shared<StructType>("", isEmbeddedStruct);
  beingDefined->addField(ComposableField(CTYPE_INT, "s1"));
  beingDefined->addField(ComposableField(CTYPE_FLOAT, "s2"));
  top->addField(ComposableField(std::move(beingDefined), ""));
  top->addField(ComposableField(CTYPE_INT, "a"));

  Parameter::Vector pv{};
  pv.emplace_back(Parameter(std::move(top), "t"));
  FunctionDeclaration f(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), std::move(pv));

  return f;
}

std::string VoidFunStructWithFirstAnonymousStructFieldFactory::functionGetFunctionName()
{
  return std::string("voidFunStructWithFirstAnonymousStructField");
}

std::string VoidFunStructWithFirstAnonymousStructFieldFactory::getFilename()
{
   return "voidFunStructWithFirstAnonymousStructField.h";
}

std::string VoidFunStructWithFirstAnonymousStructFieldFactory::getMatcherFunctionName()
{
  return "cmp_struct_topAnonymousFirstStructField";
}

std::string VoidFunStructWithFirstAnonymousStructFieldFactory::getFieldWrongName()
{
  return "t";
}

std::string VoidFunStructWithFirstAnonymousStructFieldFactory::getSubFieldWrongName()
{
  return "s2";
}

std::string VoidFunStructWithFirstAnonymousStructFieldFactory::getSubFieldWrongTypeName()
{
  return "topAnonymousFirstStructField::<anonymous>";
}

std::string VoidFunStructWithFirstAnonymousStructFieldFactory::getSubComposableTypeType()
{
  return " struct";
}

void VoidFunStructWithFirstAnonymousStructFieldFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  struct topAnonymousFirstStructField aToExpect;

  aToExpect.a = 42;
  aToExpect.s1 = 42;
  aToExpect.s2 = 6.;
  switch(tc)
  {
    case EasyMockTestCase::OneExpect:
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(m_user_matcher));
      break;
    case EasyMockTestCase::OneExpectArgIsBad:
      m_expects.push_back(std::make_tuple(aToExpect));
      aToExpect.s2+=1;
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(m_user_matcher));
      break;
    case EasyMockTestCase::ThreeExpects:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_expects.push_back(std::make_tuple(aToExpect));
        m_params.push_back(std::make_tuple(aToExpect));
        m_compare.push_back(std::make_tuple(m_user_matcher));
      }
      break;
    case EasyMockTestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_expects.push_back(std::make_tuple(aToExpect));
        m_params.push_back(std::make_tuple(aToExpect));
        m_compare.push_back(std::make_tuple(m_user_matcher));
      }
      break;
    case EasyMockTestCase::SecondExpectArgIsBad:
    case EasyMockTestCase::NoExpect:
      break;
  }
}
