#include <StructSubStructRecursiveTypeFactory.h>

#include <StructType.h>
#include <EasyMock_CType.h>
#include <Pointer.h>
#include <IncompleteType.h>
#include <ComposableField.h>

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

std::shared_ptr<FunctionDeclaration> StructSubStructRecursiveTypeFactory::functionFactory()
{
  bool isEmbeddedInOtherType = false;
  auto st1 = std::make_shared<StructType>("st1", isEmbeddedInOtherType);
  auto st2 = std::make_shared<StructType>("st2", isEmbeddedInOtherType);
  st1->addField(ComposableField(st2, "st1SubSt2"));
  //st1 is recursive in st2 because it is accessed via the parameter "st1Val" which is type st2 and has a st1 as field member
  st2->addField(ComposableField(std::make_shared<Pointer>(std::make_shared<IncompleteType>(*st1, IncompleteType::Type::STRUCT)), "st2SubSt1"));
  st2->addField(ComposableField(std::make_shared<Pointer>(std::make_shared<IncompleteType>(*st2, IncompleteType::Type::STRUCT)), "st2SubSt2"));
  Parameter::Vector pv{};
  pv.emplace_back(Parameter(std::move(st1), "st1Val"));
  auto f = std::make_shared<FunctionDeclaration>(functionGetFunctionName(), VoidReturnValue(), std::move(pv));
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
  aToExpect.st1SubSt2.st2SubSt2 = (struct st2*)0xba3;

  switch(tc)
  {
    case EasyMockTestCase::TestCase::OneExpect:
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(m_user_matcher));
      break;
    case EasyMockTestCase::TestCase::ThreeExpects:
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
    case EasyMockTestCase::TestCase::OneExpectArgIsBad:
      m_expects.push_back(std::make_tuple(aToExpect));
      aToExpect.st1SubSt2.st2SubSt1++;
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(m_user_matcher));
      break;
    case EasyMockTestCase::TestCase::SecondExpectArgIsBad:
      m_expects.push_back(std::make_tuple(aToExpect));
      m_params.push_back(std::make_tuple(aToExpect));
      m_compare.push_back(std::make_tuple(m_user_matcher));

      m_expects.push_back(std::make_tuple(aToExpect));
      aToExpect.st1SubSt2.st2SubSt1++;
      m_params.push_back(std::make_tuple(aToExpect)); //second call fails
      m_compare.push_back(std::make_tuple(m_user_matcher));
      break;
    case EasyMockTestCase::TestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        aToExpect.st1SubSt2.st2SubSt1++;
        m_expects.push_back(std::make_tuple(aToExpect));
        m_params.push_back(std::make_tuple(aToExpect));
        m_compare.push_back(std::make_tuple(m_user_matcher));
      }
      break;
    case EasyMockTestCase::TestCase::NoExpect:
      break;
  }
}
