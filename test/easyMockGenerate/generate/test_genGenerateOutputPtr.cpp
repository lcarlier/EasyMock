#include <gtest/gtest.h> // googletest header file

#include <easyMock.h>
#include <CodeGeneratorCTemplate.h>

#include "genGenerate_testCase.h"
#include "test_common.h"

#include <TestTypes.h>

template<class T>
class genGenerateOutputPtr_testCase : public genGenerate_testCase<T>
{
public:
  genGenerateOutputPtr_testCase() : genGenerate_testCase<T>()
  {
    this->setPtrOutputTypeToMatch(genGenerate_testCase<T>::m_factory.getPointerName());
  }
};

TYPED_TEST_CASE(genGenerateOutputPtr_testCase, PtrFunPtrTypes);

TYPED_TEST(genGenerateOutputPtr_testCase, TestOutputPtrGenerated)
{
  void *fptr;
  void *fptr_expect;
  void *fptr_matcher;
  void *fptr_output_ptr;
  easyMockGenerate_baseTestCase::getFunPtr(&fptr, &fptr_expect, &fptr_matcher, &fptr_output_ptr);

  ASSERT_NE(fptr_output_ptr, nullptr);
}