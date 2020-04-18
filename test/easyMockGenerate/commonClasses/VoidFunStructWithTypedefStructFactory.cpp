#include <VoidFunStructWithTypedefStructFactory.h>

#include <StructType.h>
#include <ComposableField.h>
#include <CType.h>

Function VoidFunStructWithTypedefStructFactory::functionFactory()
{
  StructType *t_subStructVar = new StructType("", "t_subStruct", false);
  t_subStructVar->addStructField(new ComposableField(new CType(CTYPE_INT), "a"));

  StructType *t_structVar = new StructType("", "t_struct", false);
  t_structVar->addStructField(new ComposableField(t_subStructVar, "sub"));
  t_subStructVar = nullptr; //We lost the ownership

  Parameter *p = new Parameter(t_structVar, "s");
  t_structVar = nullptr; //We lost the ownership
  Function f(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), Parameter::Vector({p}));
  p = nullptr; //We lost the ownership

  return f;
}

Function* VoidFunStructWithTypedefStructFactory::newFunctionFactory()
{
  return functionFactory().clone();
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
