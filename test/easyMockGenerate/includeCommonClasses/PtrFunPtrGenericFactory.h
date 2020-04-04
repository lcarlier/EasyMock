#ifndef PTRFUNPTRGENERICFACTORY_H
#define PTRFUNPTRGENERICFACTORY_H

#include <FunctionFactory.h>
#include <CType.h>
#include <vector>

template <typename PTR_TYPE, easyMock_cTypes_t C_TYPE>
class PtrFunPtrGenericFactory : public FunctionFactory<PTR_TYPE *, std::tuple<PTR_TYPE *>, std::tuple<EasyMock_Matcher>>
{
  public:

  std::string getFilename() override
  {
    std::string filename(functionGetFunctionName());
    filename.append(".h");
    return filename;
  }

  Function functionFactory() override
  {
    bool isPointer = true;
    Function f(functionGetFunctionName(), ReturnValue(new CType(C_TYPE), isPointer), Parameter::Vector({NamedParameter(C_TYPE, "ptr", isPointer)}));
    return f;
  }

  Function * newFunctionFactory() override
  {
    return functionFactory().clone();
  }

  std::string getPointerName()
  {
    CType t(C_TYPE);
    return t.getName();
  }

  std::string functionGetFunctionName() override
  {
    CType t(C_TYPE);
    std::string typeName = t.getName();

    std::vector<std::string> tokens = this->split(typeName, " ");
    std::string type_subName; //In case of "unsigned int", it is "int"
    for(unsigned int tokenIdx = 1; tokenIdx < tokens.size(); tokenIdx++)
    {
      std::string &thisToken = tokens[tokenIdx];
      thisToken[0] = std::toupper(thisToken[0]);
      type_subName.append(thisToken);
    }

    std::string &firstToken = tokens[0];
    std::string funName(firstToken);
    funName.append(type_subName);
    funName.append("PtrFun");
    firstToken[0] = std::toupper(firstToken[0]);
    funName.append(firstToken);
    funName.append(type_subName);
    funName.append("Ptr");
    return funName;
  }

  void setupTestCase(EasyMockTestCase::TestCase tc) override
  {
    unsigned char* aToExpect = (unsigned char *) 0xcafebabe;
    unsigned char* rvToExpect = (unsigned char *) 0xdeadbead;
    switch (tc)
    {
      case EasyMockTestCase::OneExpect:
        this->m_rv.push_back((PTR_TYPE *) rvToExpect);
        this->m_expects.push_back(std::make_tuple((PTR_TYPE *) aToExpect));
        this->m_params.push_back(std::make_tuple((PTR_TYPE *) aToExpect));
        this->m_compare.push_back(std::make_tuple(&cmp_pointer));
        break;
      case EasyMockTestCase::ThreeExpects:
      {
        for (unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
        {
          unsigned char* ptrToExpect = aToExpect + expectIdx;
          this->m_rv.push_back((PTR_TYPE *) ptrToExpect);
          this->m_expects.push_back(std::make_tuple((PTR_TYPE *) ptrToExpect));
          this->m_params.push_back(std::make_tuple((PTR_TYPE *) ptrToExpect));
          this->m_compare.push_back(std::make_tuple(&cmp_pointer));
        }
        break;
      }
      case EasyMockTestCase::OneExpectArgIsBad:
      {
        unsigned char *wrongPointer = aToExpect + 1;
        this->m_rv.push_back((PTR_TYPE *) rvToExpect);
        this->m_expects.push_back(std::make_tuple((PTR_TYPE *) aToExpect));
        this->m_params.push_back(std::make_tuple((PTR_TYPE *) wrongPointer));
        this->m_compare.push_back(std::make_tuple(&cmp_pointer));
        break;
      }
      case EasyMockTestCase::SecondExpectArgIsBad:
      {
        unsigned char *wrongPointer = aToExpect + 1;
        this->m_rv.push_back((PTR_TYPE *) rvToExpect);
        this->m_expects.push_back(std::make_tuple((PTR_TYPE *) aToExpect));
        this->m_params.push_back(std::make_tuple((PTR_TYPE *) aToExpect));
        this->m_compare.push_back(std::make_tuple(&cmp_pointer));

        this->m_rv.push_back((PTR_TYPE *) rvToExpect);
        this->m_expects.push_back(std::make_tuple((PTR_TYPE *) aToExpect));
        this->m_params.push_back(std::make_tuple((PTR_TYPE *) wrongPointer)); //second call fails
        this->m_compare.push_back(std::make_tuple(&cmp_pointer));
      }
        break;
      case EasyMockTestCase::NotEnoughCall:
        for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
        {
          unsigned char* ptrToExpect = aToExpect + expectIdx;
          this->m_rv.push_back((PTR_TYPE *) ptrToExpect);
          this->m_expects.push_back(std::make_tuple((PTR_TYPE *) ptrToExpect));
          this->m_params.push_back(std::make_tuple((PTR_TYPE *) ptrToExpect));
          this->m_compare.push_back(std::make_tuple(&cmp_pointer));  
        }
      case EasyMockTestCase::NoExpect:
        break;
    }
  }

private:
  std::deque<PTR_TYPE *> m_out_ptr;
  std::vector<std::string> split(const std::string& str, const std::string & delim)
  {
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
      pos = str.find(delim, prev);
      if (pos == std::string::npos)
      {
        pos = str.length();
      }
      std::string token = str.substr(prev, pos - prev);
      if (!token.empty())
      {
        tokens.push_back(token);
      }
      prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
  }
};

/*
 * Specialisation of all the factories
 */
class VoidPtrFunVoidPtrFactory : public PtrFunPtrGenericFactory<void, CTYPE_VOID>{};
class CharPtrFunCharPtrFactory : public PtrFunPtrGenericFactory<char, CTYPE_CHAR>{};
class UnsCharPtrFunUnsCharPtrFactory : public PtrFunPtrGenericFactory<unsigned char, CTYPE_UCHAR>{};
class ShortPtrFunShortPtrFactory : public PtrFunPtrGenericFactory<short, CTYPE_SHORT>{};
class UnsShortPtrFunUnsShortPtrFactory : public PtrFunPtrGenericFactory<unsigned short, CTYPE_USHORT>{};
class IntPtrFunIntPtrFactory : public PtrFunPtrGenericFactory<int, CTYPE_INT>{};
class UnsIntPtrFunUnsIntPtrFactory : public PtrFunPtrGenericFactory<unsigned int, CTYPE_UINT>{};
class LongPtrFunLongPtrFactory : public PtrFunPtrGenericFactory<long, CTYPE_LONG>{};
class UnsLongPtrFunUnsLongPtrFactory : public PtrFunPtrGenericFactory<unsigned long, CTYPE_ULONG>{};
class LongLongPtrFunLongLongPtrFactory : public PtrFunPtrGenericFactory<long long, CTYPE_LONG_LONG>{};
class UnsLongLongPtrFunUnsLongLongPtrFactory : public PtrFunPtrGenericFactory<unsigned long long, CTYPE_ULONG_LONG>{};
class FloatPtrFunFloatPtrFactory : public PtrFunPtrGenericFactory<int, CTYPE_FLOAT>{};
class DoublePtrFunDoublePtrFactory : public PtrFunPtrGenericFactory<double, CTYPE_DOUBLE>{};
class LongDoublePtrFunLongDoublePtrFactory : public PtrFunPtrGenericFactory<long double, CTYPE_LONG_DOUBLE>{};

#endif /* PTRFUNPTRGENERICFACTORY_H */

