#ifndef GENGENERATE_TESTCASE_H
#define GENGENERATE_TESTCASE_H

#include "test_common.h"

template<class T>
class genGenerate_testCase : public easyMockGenerate_baseTestCase
{
public:
  genGenerate_testCase() : easyMockGenerate_baseTestCase(m_factory.functionGetFunctionName(), m_factory.functionGetIncludeDir(), m_factory.functionGetMockDir(), false)
  {
    ElementToMock *f = m_factory.newFunctionFactory();
    m_elem.push_back(f);
  }

  void ExtraTearDown() override
  {
    ASSERT_TRUE(m_factory.is_rv_queue_empty());
    ASSERT_TRUE(m_factory.is_expect_rv_cur_call_queue_empty());
    ASSERT_TRUE(m_factory.is_params_queue_empty());
    ASSERT_TRUE(m_factory.is_expects_queue_empty());
    ASSERT_TRUE(m_factory.is_compare_queue_empty());
  }

  static T m_factory;
};

template<class T>
T genGenerate_testCase<T>::m_factory;

#endif /* GENGENERATE_TESTCASE_H */

