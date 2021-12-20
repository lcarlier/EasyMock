#include <VoidFunStructWithTypedefStructFactory.h>

#include <StructType.h>
#include <ComposableField.h>
#include <EasyMock_CType.h>
#include <TypedefType.h>

FunctionDeclaration VoidFunStructWithTypedefStructFactory::functionFactory()
{
  auto tt_subStructVar = std::make_shared<TypedefType>("t_subStruct", std::make_shared<StructType>("", false));
  ComposableType *t_subStructVar = tt_subStructVar->getTypee()->asComposableType();
  t_subStructVar->addField(ComposableField(std::make_shared<CType>(CTYPE_INT), "a"));

  auto tt_structVar = std::make_shared<TypedefType>("t_struct", std::make_shared<StructType>("", false));
  ComposableType *t_structVar = tt_structVar->getTypee()->asComposableType();
  t_structVar->addField(ComposableField(std::move(tt_subStructVar), "sub"));

  Parameter p{std::move(tt_structVar), "s"};
  Parameter::Vector pv{};
  pv.emplace_back(std::move(p));
  FunctionDeclaration f(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), std::move(pv));

  return f;
}

std::string VoidFunStructWithTypedefStructFactory::functionGetFunctionName()
{
  return std::string("voidFunStructWithTypedefStruct");
}

std::string VoidFunStructWithTypedefStructFactory::getFilename()
{
   return "voidFunStructWithTypedefStruct.h";
}

std::string VoidFunStructWithTypedefStructFactory::getMatcherFunctionName()
{
  return "cmp_t_struct";
}

std::string VoidFunStructWithTypedefStructFactory::getFieldWrongName()
{
  return "s.sub";
}

std::string VoidFunStructWithTypedefStructFactory::getSubFieldWrongName()
{
  return "a";
}

std::string VoidFunStructWithTypedefStructFactory::getSubFieldWrongTypeName()
{
  return "t_subStruct";
}

std::string VoidFunStructWithTypedefStructFactory::getSubComposableTypeType()
{
  return " struct";
}

void VoidFunStructWithTypedefStructFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  t_struct aToExpect;
  aToExpect.sub.a = 42;

  switch(tc)
  {
    case EasyMockTestCase::OneExpect:
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(m_user_matcher));
      break;
    case EasyMockTestCase::ThreeExpects:
    {
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        aToExpect.sub.a++;
        m_expects.push_back(std::make_tuple(aToExpect));
        m_params.push_back(std::make_tuple(aToExpect));
        m_compare.push_back(std::make_tuple(m_user_matcher));
      }
      break;
    }
    case EasyMockTestCase::OneExpectArgIsBad:
      m_expects.push_back(std::make_tuple(aToExpect));
      aToExpect.sub.a++;
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(m_user_matcher));
      break;
    case EasyMockTestCase::SecondExpectArgIsBad:
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(m_user_matcher));

      m_expects.push_back(std::make_tuple(aToExpect));
      aToExpect.sub.a++;
      m_params.push_back(std::make_tuple(aToExpect)); //second call fails
      m_compare.push_back(std::make_tuple(m_user_matcher));
      break;
    case EasyMockTestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        aToExpect.sub.a++;
        m_expects.push_back(std::make_tuple(aToExpect));
        m_params.push_back(std::make_tuple(aToExpect));
        m_compare.push_back(std::make_tuple(m_user_matcher));
      }
      break;
    case EasyMockTestCase::NoExpect:
      break;
  }
}
