#include <gtest/gtest.h> // googletest header file

#include <easyMock.h>
#include <CodeGeneratorCTemplate.h>

#include "genGenerate_testCase.h"
#include "test_common.h"

#include <TestTypes.h>

#include <Pointer.h>
#include <ConstQualifiedType.h>

template<class T>
class genGenerateOutputPtr_testCase : public genGenerate_testCase<T>
{
public:
  genGenerateOutputPtr_testCase() : genGenerate_testCase<T>()
  {
  }
};

TYPED_TEST_SUITE(genGenerateOutputPtr_testCase, PtrFunPtrTypes);

TYPED_TEST(genGenerateOutputPtr_testCase, TestOutputPtrGenerated)
{
  void *fptr;
  void *fptr_expect;
  void *fptr_matcher;
  void *fptr_output_ptr;
  easyMockGenerate_baseTestCase::getFunPtr(&fptr, &fptr_expect, &fptr_matcher, &fptr_output_ptr);

  auto f = this->m_factory.functionFactory();
  const Parameter::Vector &parameters = f->getFunctionsParameters();
  const Parameter &firstParam = parameters[0];
  const TypeItf* firstParamType = firstParam.getType();
  const TypeItf* pointedType = dynamic_cast<const Pointer *>(firstParamType)->getPointedType();

  if(firstParamType->isPointer() && pointedType->isConst())
  {
    ASSERT_EQ(fptr_output_ptr, nullptr);
  }
  else
  {
    ASSERT_NE(fptr_output_ptr, nullptr);
  }
}

template<class T>
class nonPtrGenerateOutputPtr_testCase : public genGenerate_testCase<T>
{
public:
  nonPtrGenerateOutputPtr_testCase() : genGenerate_testCase<T>()
  {
  }
};

TYPED_TEST_SUITE(nonPtrGenerateOutputPtr_testCase, NonPtrFunTypes);

TYPED_TEST(nonPtrGenerateOutputPtr_testCase, TestOutputPtrNotGenerated)
{
  void *fptr;
  void *fptr_expect;
  void *fptr_matcher;
  void *fptr_output_ptr;
  easyMockGenerate_baseTestCase::getFunPtr(&fptr, &fptr_expect, &fptr_matcher, &fptr_output_ptr);

  ASSERT_EQ(fptr_output_ptr, nullptr);
}
