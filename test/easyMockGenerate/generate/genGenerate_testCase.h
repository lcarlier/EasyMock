#ifndef GENGENERATE_TESTCASE_H
#define GENGENERATE_TESTCASE_H

#include "test_common.h"

template<class T>
class genGenerate_testCase : public easyMockGenerate_baseTestCase
{
public:
  genGenerate_testCase() : easyMockGenerate_baseTestCase(m_factory.functionGetFunctionName(), m_factory.functionGetIncludeDir(), m_factory.functionGetMockDir(), m_factory.getGenerateTypes(), m_factory.getRmDir())
  {
    for(const auto f : m_factory.functionFactoryArray())
    {
      m_ctxt.addElementToMock(f->clone());
    }
    for(const auto& p : m_factory.getDefinedMacroList())
    {
      const MacroDefinition& macroDefinition = p.second;
      m_ctxt.addMacroDefine(macroDefinition.getId(), macroDefinition.getParameters(), macroDefinition.getDefinition());
    }
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

