#include <VoidFunStructWithEmbeddedAnonymousStructFactory.h>

#include <StructType.h>

FunctionDeclaration VoidFunStructWithEmbeddedAnonymousStructFactory::functionFactory()
{
  const unsigned int NB_ANONYMOUS_TYPE_IN_THIS_UT = 1;
  /*
   * with -fno-access-control we are able to set this static class variable to
   * decrement the number of anonymous composable type by the number of anonymous
   * type the UT contains.
   * Thanks to that, the following code will generate the same anonymous ID
   */
  ComposableType::m_number_of_anonymous_composable_type -= NB_ANONYMOUS_TYPE_IN_THIS_UT;
  bool isEmbeddedStruct = true;
  StructType* top = new StructType("topEmbeddedAnonymous", !isEmbeddedStruct); //NOT EMBEDDED
  StructType* beingDefined = new StructType("", isEmbeddedStruct);
  beingDefined->addField(new ComposableField(CTYPE_INT, "a"));
  top->addField(new ComposableField(beingDefined, "af"));
  FunctionDeclaration f(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), Parameter::Vector({new Parameter(top, "s")}));

  return f;
}

FunctionDeclaration* VoidFunStructWithEmbeddedAnonymousStructFactory::newFunctionFactory()
{
  return functionFactory().clone();
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
    case EasyMockTestCase::OneExpect:
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(m_user_matcher));
      break;
    case EasyMockTestCase::OneExpectArgIsBad:
      m_expects.push_back(std::make_tuple(aToExpect));
      aToExpect.af.a++;
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
