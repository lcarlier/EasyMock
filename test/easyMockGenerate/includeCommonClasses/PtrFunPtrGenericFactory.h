#ifndef PTRFUNPTRGENERICFACTORY_H
#define PTRFUNPTRGENERICFACTORY_H

#include <FunctionFactory.h>
#include <EasyMock_CType.h>
#include <vector>
#include <Pointer.h>

template <typename PTR_TYPE, easyMock_cTypes_t C_TYPE, bool isConst>
class PtrFunPtrGenericFactory : public FunctionFactory<PTR_TYPE *, std::tuple<PTR_TYPE *>, std::tuple<EasyMock_Matcher>>
{
  public:

  std::string getFilename() override
  {
    std::string filename(functionGetFunctionName());
    filename.append(".h");
    return filename;
  }

  FunctionDeclaration functionFactory() override
  {
    TypeItf *rvType = new Pointer(new CType(C_TYPE, isConst));
    TypeItf *paramType = rvType->clone();

    FunctionDeclaration f(functionGetFunctionName(), ReturnValue(rvType), Parameter::Vector({new Parameter(paramType, "ptr")}));

    rvType = nullptr; //We lost the ownership
    paramType = nullptr; //We lost the ownership
    return f;
  }

  FunctionDeclaration * newFunctionFactory() override
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
    std::string funName;
    if(isConst)
    {
      funName.append("const");
      firstToken[0] = std::toupper(firstToken[0]);
    }
    funName.append(firstToken);
    funName.append(type_subName);
    funName.append("PtrFun");
    if(isConst)
    {
      funName.append("Const");
    }
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
        this->m_rvContext.m_rv.push_back((PTR_TYPE *) rvToExpect);
        this->m_expects.push_back(std::make_tuple((PTR_TYPE *) aToExpect));
        this->m_params.push_back(std::make_tuple((PTR_TYPE *) aToExpect));
        this->m_compare.push_back(std::make_tuple(&cmp_pointer));
        break;
      case EasyMockTestCase::ThreeExpects:
      {
        for (unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::ThreeExpects_NbExpects; expectIdx++)
        {
          unsigned char* ptrToExpect = aToExpect + expectIdx;
          this->m_rvContext.m_rv.push_back((PTR_TYPE *) ptrToExpect);
          this->m_expects.push_back(std::make_tuple((PTR_TYPE *) ptrToExpect));
          this->m_params.push_back(std::make_tuple((PTR_TYPE *) ptrToExpect));
          this->m_compare.push_back(std::make_tuple(&cmp_pointer));
        }
        break;
      }
      case EasyMockTestCase::OneExpectArgIsBad:
      {
        unsigned char *wrongPointer = aToExpect + 1;
        this->m_rvContext.m_rv.push_back((PTR_TYPE *) rvToExpect);
        this->m_expects.push_back(std::make_tuple((PTR_TYPE *) aToExpect));
        this->m_params.push_back(std::make_tuple((PTR_TYPE *) wrongPointer));
        this->m_compare.push_back(std::make_tuple(&cmp_pointer));
        break;
      }
      case EasyMockTestCase::SecondExpectArgIsBad:
      {
        unsigned char *wrongPointer = aToExpect + 1;
        this->m_rvContext.m_rv.push_back((PTR_TYPE *) rvToExpect);
        this->m_expects.push_back(std::make_tuple((PTR_TYPE *) aToExpect));
        this->m_params.push_back(std::make_tuple((PTR_TYPE *) aToExpect));
        this->m_compare.push_back(std::make_tuple(&cmp_pointer));

        this->m_rvContext.m_rv.push_back((PTR_TYPE *) rvToExpect);
        this->m_expects.push_back(std::make_tuple((PTR_TYPE *) aToExpect));
        this->m_params.push_back(std::make_tuple((PTR_TYPE *) wrongPointer)); //second call fails
        this->m_compare.push_back(std::make_tuple(&cmp_pointer));
      }
        break;
      case EasyMockTestCase::NotEnoughCall:
        for(unsigned int expectIdx = 0; expectIdx < EasyMockTestCase::NotEnoughCall_NbExpects; expectIdx++)
        {
          unsigned char* ptrToExpect = aToExpect + expectIdx;
          this->m_rvContext.m_rv.push_back((PTR_TYPE *) ptrToExpect);
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
class VoidPtrFunVoidPtrFactory : public PtrFunPtrGenericFactory<void, CTYPE_VOID, false>{};
class CharPtrFunCharPtrFactory : public PtrFunPtrGenericFactory<char, CTYPE_CHAR, false>{};
class UnsCharPtrFunUnsCharPtrFactory : public PtrFunPtrGenericFactory<unsigned char, CTYPE_UCHAR, false>{};
class ShortPtrFunShortPtrFactory : public PtrFunPtrGenericFactory<short, CTYPE_SHORT, false>{};
class UnsShortPtrFunUnsShortPtrFactory : public PtrFunPtrGenericFactory<unsigned short, CTYPE_USHORT, false>{};
class IntPtrFunIntPtrFactory : public PtrFunPtrGenericFactory<int, CTYPE_INT, false>{};
class UnsIntPtrFunUnsIntPtrFactory : public PtrFunPtrGenericFactory<unsigned int, CTYPE_UINT, false>{};
class LongPtrFunLongPtrFactory : public PtrFunPtrGenericFactory<long, CTYPE_LONG, false>{};
class UnsLongPtrFunUnsLongPtrFactory : public PtrFunPtrGenericFactory<unsigned long, CTYPE_ULONG, false>{};
class LongLongPtrFunLongLongPtrFactory : public PtrFunPtrGenericFactory<long long, CTYPE_LONG_LONG, false>{};
class UnsLongLongPtrFunUnsLongLongPtrFactory : public PtrFunPtrGenericFactory<unsigned long long, CTYPE_ULONG_LONG, false>{};
class FloatPtrFunFloatPtrFactory : public PtrFunPtrGenericFactory<int, CTYPE_FLOAT, false>{};
class DoublePtrFunDoublePtrFactory : public PtrFunPtrGenericFactory<double, CTYPE_DOUBLE, false>{};
class LongDoublePtrFunLongDoublePtrFactory : public PtrFunPtrGenericFactory<long double, CTYPE_LONG_DOUBLE, false>{};
class ConstIntPtrFunConstIntPtrFactory : public PtrFunPtrGenericFactory<int, CTYPE_INT, true>{};

#endif /* PTRFUNPTRGENERICFACTORY_H */

