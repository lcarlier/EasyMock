#include <StructSubStructRecursiveTypeFactory.h>

#include <StructType.h>
#include <CType.h>
#include <Pointer.h>

/*
 * struct s2;
 *
 * struct s1 {
 *    struct s1 *s1SubS1;
 *    struct s2 *s1SubS2;
 * }
 *
 * struct s2 {
 *    struct s1 s2SubS1;
 * }
 *
 */

FunctionDeclaration StructSubStructRecursiveTypeFactory::functionFactory()
{
  bool isEmbeddedInOtherType = false;
  StructType *st1 = new StructType("st1", isEmbeddedInOtherType);
  StructType *st2 = new StructType("st2", isEmbeddedInOtherType);
  st1->addField(new ComposableField(st2, "st1SubSt2"));
  //st1 is recursive in st2 because it is access via the parameter "st1Val" which is type st2 and has a st1 as field member
  st2->addField(new ComposableField(new Pointer (st1), "st2SubSt1", {.arraySize=-1, .isRecursiveTypeField=true}));
  st2->addField(new ComposableField(new Pointer (st2), "st2SubSt2", {.arraySize=-1, .isRecursiveTypeField=true}));
  FunctionDeclaration f(functionGetFunctionName(), VoidReturnValue(), Parameter::Vector({new Parameter(st1, "st1Val")}));
  return f;
}

std::string StructSubStructRecursiveTypeFactory::functionGetFunctionName()
{
  return "structSubStructRecursiveType";
}

std::string StructSubStructRecursiveTypeFactory::getFilename()
{
  return "structSubStructRecursiveType.h";
}

std::string StructSubStructRecursiveTypeFactory::getMatcherFunctionName()
{
  return "cmp_struct_st1";
}

std::string StructSubStructRecursiveTypeFactory::getFieldWrongName()
{
  return "st1Val.st1SubSt2";
}

std::string StructSubStructRecursiveTypeFactory::getSubFieldWrongName()
{
  return "st2SubSt1";
}

std::string StructSubStructRecursiveTypeFactory::getSubFieldWrongTypeName()
{
  return "st2";
}

std::string StructSubStructRecursiveTypeFactory::getSubComposableTypeType()
{
  return " struct";
}

void StructSubStructRecursiveTypeFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  struct st1 aToExpect;
  aToExpect.st1SubSt2.st2SubSt1 = (struct st1*)0xf00;
  aToExpect.st1SubSt2.st2SubSt1 = (struct st1*)0xba3;

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
        aToExpect.st1SubSt2.st2SubSt1++;
        m_expects.push_back(std::make_tuple(aToExpect));
        m_params.push_back(std::make_tuple(aToExpect));
        m_compare.push_back(std::make_tuple(m_user_matcher));
      }
      break;
    }
    case EasyMockTestCase::OneExpectArgIsBad:
      m_expects.push_back(std::make_tuple(aToExpect));
      aToExpect.st1SubSt2.st2SubSt1++;
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(m_user_matcher));
      break;
    case EasyMockTestCase::SecondExpectArgIsBad:
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(m_user_matcher));

      m_expects.push_back(std::make_tuple(aToExpect));
      aToExpect.st1SubSt2.st2SubSt1++;
      m_params.push_back(std::make_tuple(aToExpect)); //second call fails
      m_compare.push_back(std::make_tuple(m_user_matcher));
      break;
    case EasyMockTestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        aToExpect.st1SubSt2.st2SubSt1++;
        m_expects.push_back(std::make_tuple(aToExpect));
        m_params.push_back(std::make_tuple(aToExpect));
        m_compare.push_back(std::make_tuple(m_user_matcher));
      }
      break;
    case EasyMockTestCase::NoExpect:
      break;
  }
}
