#include <UnionAnonymousTypedDefFunUnionAnonymousTypedDefFactory.h>

#include <UnionType.h>
#include <ComposableField.h>
#include <TypedefType.h>

FunctionDeclaration UnionAnonymousTypedDefFunUnionAnonymousTypedDefFactory::functionFactory()
{
  bool isEmbeddedInOtherType = false;
  TypedefType *tst1 = new TypedefType("TypedDefAnonymousUnion", new UnionType("", isEmbeddedInOtherType));
  UnionType *st1 = dynamic_cast<UnionType*>(tst1->getTypee());
  st1->addField(new ComposableField(CTYPE_INT, "a"));
  st1->addField(new ComposableField(CTYPE_INT, "b"));
  TypeItf *rv = tst1->clone();

  FunctionDeclaration f(functionGetFunctionName(), ReturnValue(rv), Parameter::Vector({new Parameter(tst1, "u")}));
  return f;
}

std::string UnionAnonymousTypedDefFunUnionAnonymousTypedDefFactory::functionGetFunctionName()
{
  return "unionAnonymousTypedDefFunUnionAnonymousTypedDef";
}

std::string UnionAnonymousTypedDefFunUnionAnonymousTypedDefFactory::getFilename()
{
  return "unionAnonymousTypedDefFunUnionAnonymousTypedDef.h";
}

void UnionAnonymousTypedDefFunUnionAnonymousTypedDefFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  TypedDefAnonymousUnion t;
  t.a = 42;
  t.b = 84;
  switch(tc)
  {
    case EasyMockTestCase::OneExpect:
      m_rvContext.m_rv.push_back(t);
      m_expects.push_back(std::make_tuple(t));
      m_params.push_back(std::make_tuple(t));
      m_compare.push_back(std::make_tuple(nullptr)); //Seperate dedicated UT are writen to test the generation and function of the comparators for structs
      break;
    case EasyMockTestCase::ThreeExpects:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(t);
        m_expects.push_back(std::make_tuple(t));
        m_params.push_back(std::make_tuple(t));
        m_compare.push_back(std::make_tuple(nullptr)); //Seperate dedicated UT are writen to test the generation and function of the comparators for structs
      }
      break;
    case EasyMockTestCase::NotEnoughCall:
      for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
      {
        m_rvContext.m_rv.push_back(t);
        m_expects.push_back(std::make_tuple(t));
        m_params.push_back(std::make_tuple(t));
        m_compare.push_back(std::make_tuple(nullptr)); //Seperate dedicated UT are writen to test the generation and function of the comparators for structs
      }
      break;
    case EasyMockTestCase::OneExpectArgIsBad: //Not tested in a generic way
    case EasyMockTestCase::SecondExpectArgIsBad: //Not tested in a generic way
    case EasyMockTestCase::NoExpect:
      break;
  }
}
