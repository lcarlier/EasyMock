#include <VoidFunStructWithFirstAnonymousStructFieldFactory.h>

#include <StructType.h>

FunctionDeclaration VoidFunStructWithFirstAnonymousStructFieldFactory::functionFactory()
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
  StructType* top = new StructType("topAnonymousFirstStructField", !isEmbeddedStruct); //NOT EMBEDDED
  StructType* beingDefined = new StructType("", isEmbeddedStruct);
  beingDefined->addField(new ComposableField(CTYPE_INT, "s1"));
  beingDefined->addField(new ComposableField(CTYPE_FLOAT, "s2"));
  top->addField(new ComposableField(beingDefined, ""));
  top->addField(new ComposableField(CTYPE_INT, "a"));
  FunctionDeclaration f(functionGetFunctionName(), TypedReturnValue(CTYPE_VOID), Parameter::Vector({new Parameter(top, "t")}));

  return f;
}

FunctionDeclaration* VoidFunStructWithFirstAnonymousStructFieldFactory::newFunctionFactory()
{
  return functionFactory().clone();
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
