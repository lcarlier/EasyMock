#include <VoidFunStructWithAnonymousUnionFieldWithStructFactory.h>

#include <FunctionDeclaration.h>
#include <EasyMock_CType.h>
#include <ConstQualifiedType.h>
#include <Pointer.h>
#include <StructType.h>
#include <UnionType.h>
#include <ComposableField.h>

FunctionDeclaration VoidFunStructWithAnonymousUnionFieldWithStructFactory::functionFactory()
{
  return functionFactoryArray()[0];
}

ElementToMockList VoidFunStructWithAnonymousUnionFieldWithStructFactory::functionFactoryArray()
{
  ElementToMockList returnedList;
  {
    StructType *ss1 = new StructType{"subAnonUnion1", false};
    ss1->addField(new ComposableField{CTYPE_INT, "a"});
    ss1->addField(new ComposableField{CTYPE_INT, "b"});

    StructType *ss2 = new StructType{"subAnonUnion2", false};
    ss2->addField(new ComposableField{CTYPE_INT, "a"});

    UnionType *ut = new UnionType{"", true};
    ut->addField(new ComposableField{new Pointer{ss1}, "s1"});
    ut->addField(new ComposableField{new Pointer{ss2}, "s2"});

    StructType *as1 = new StructType{"", true};
    as1->addField(new ComposableField{CTYPE_INT, "a"});

    StructType *as2 = new StructType{"", true};
    as2->addField(new ComposableField{ut, ""});

    StructType *st = new StructType{"structWithUnionFieldWithStruct", false};
    st->addField(new ComposableField{as1, "f1"});
    st->addField(new ComposableField{as2, "f2"});

    Parameter *p = new Parameter{st, "t"};
    FunctionDeclaration *f = new FunctionDeclaration{functionGetFunctionName(), TypedReturnValue(CTYPE_VOID),
                                                     Parameter::Vector({p})};

    returnedList.push_back(f);
  }
   return returnedList;
}

std::string VoidFunStructWithAnonymousUnionFieldWithStructFactory::functionGetFunctionName()
{
  return std::string("voidFunStructWithAnonymousUnionFieldWithStruct");
}

std::string VoidFunStructWithAnonymousUnionFieldWithStructFactory::getFilename()
{
  return "voidFunStructWithAnonymousUnionFieldWithStruct.h";
}

std::string VoidFunStructWithAnonymousUnionFieldWithStructFactory::getMatcherFunctionName()
{
  return "cmp_struct_structWithUnionFieldWithStruct";
}

std::string VoidFunStructWithAnonymousUnionFieldWithStructFactory::getFieldWrongName()
{
  return std::string{"t.f2"};
}

std::string VoidFunStructWithAnonymousUnionFieldWithStructFactory::getSubComposableTypeType()
{
  return std::string{" struct"};
}

std::string VoidFunStructWithAnonymousUnionFieldWithStructFactory::getSubFieldWrongTypeName()
{
  return std::string{"structWithUnionFieldWithStruct::<anonymous>::<anonymous>"};
}

std::string VoidFunStructWithAnonymousUnionFieldWithStructFactory::getSubFieldWrongName()
{
  return std::string{"s1"};
}

void VoidFunStructWithAnonymousUnionFieldWithStructFactory::setupTestCase(EasyMockTestCase::TestCase tc)
{
  structWithUnionFieldWithStruct aToExpect;
  aToExpect.f1.a = 42;
  aToExpect.f2.s1 = reinterpret_cast<struct subAnonUnion1*>(0xf00);

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
          aToExpect.f2.s1++;
          m_expects.push_back(std::make_tuple(aToExpect));
          m_params.push_back(std::make_tuple(aToExpect));
          m_compare.push_back(std::make_tuple(m_user_matcher));
        }
        break;
      }
      case EasyMockTestCase::OneExpectArgIsBad:
        m_expects.push_back(std::make_tuple(aToExpect));
        aToExpect.f2.s1++;
        m_params.push_back(std::make_tuple(aToExpect));
        m_compare.push_back(std::make_tuple(m_user_matcher));
        break;
        case EasyMockTestCase::SecondExpectArgIsBad:
          m_expects.push_back(std::make_tuple(aToExpect));
          m_params.push_back(std::make_tuple(aToExpect));
          m_compare.push_back(std::make_tuple(m_user_matcher));

          m_expects.push_back(std::make_tuple(aToExpect));
          aToExpect.f2.s1++;
          m_params.push_back(std::make_tuple(aToExpect)); //second call fails
          m_compare.push_back(std::make_tuple(m_user_matcher));
          break;
          case EasyMockTestCase::NotEnoughCall:
            for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
            {
              aToExpect.f2.s1++;
              m_expects.push_back(std::make_tuple(aToExpect));
              m_params.push_back(std::make_tuple(aToExpect));
              m_compare.push_back(std::make_tuple(m_user_matcher));
            }
            break;
            case EasyMockTestCase::NoExpect:
              break;
  }
}