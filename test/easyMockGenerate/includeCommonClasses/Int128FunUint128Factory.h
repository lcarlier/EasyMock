#ifndef INT128FUNUINT128FACTORY_H
#define INT128FUNUINT128FACTORY_H

#include <FunctionFactory.h>
#include <int128FunUint128.h>

class Int128FunUint128Factory: public FunctionFactory<__int128, std::tuple<unsigned __int128, __uint128_t, __int128_t>, std::tuple<EasyMock_Matcher, EasyMock_Matcher, EasyMock_Matcher>>
{
public:
  std::shared_ptr<FunctionDeclaration> functionFactory() override;
  ElementToMockList functionFactoryArray() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  void setupTestCase(EasyMockTestCase::TestCase tc) override;

};

class Int128FunUint128FactoryGenTypeFactory: public Int128FunUint128Factory
{
public:
  Int128FunUint128FactoryGenTypeFactory() : Int128FunUint128Factory()
  {
    this->m_generate_types = true;
  }
};

#endif /* INT128FUNUINT128FACTORY_H */
