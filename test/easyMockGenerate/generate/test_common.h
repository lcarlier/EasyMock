#ifndef TEST_COMMON_H
#define TEST_COMMON_H

#include <gtest/gtest.h>

#include <easyMock.h>

#include <CodeParserItf.h>
#include <ElementToMockContext.h>

#include <string>

void createDir(const std::string &dir);
void rmDir(const std::string &dir);
bool isFifoCallEmpty();
std::string getCurrentFifoCall();
int fifoCallSize();
#define EASYMOCK_ASSERT_NO_ERROR \
{ \
  const char *error = easyMock_getErrorStr(); \
  ASSERT_EQ(error, nullptr) << error; \
\
  unsigned int size; \
  const char **errorArr = easyMock_getErrorArr(&size); \
\
  ASSERT_EQ(size, 0); \
  ASSERT_EQ(errorArr, nullptr); \
}

class EasyMock_ErrorArrayPrinter
{
public:

  EasyMock_ErrorArrayPrinter(const char **in) : m_in(in) { }
  friend std::stringstream &operator<<(std::stringstream &out, const EasyMock_ErrorArrayPrinter &obj);

  const char **m_in;
};

class easyMockGenerate_baseTestCase : public ::testing::Test
{
public:
  easyMockGenerate_baseTestCase(const std::string functionToMock, const std::string pathToFileToMock, const std::string mockDir, bool generateTypes, bool rmDir = true);
  //Only 1 matcher can be supported at a time!! this means that we cannot test union matcher and struct matcher in the same UT
  //No problem since 1 UT only tests 1 functionality
  void setComparatorToMatch(const std::string structTypeToMatch);
protected:
  const std::string m_functionToMock;
  std::string m_comparatorToMatch;
  std::string m_ptrOutputTypeToMatch;
  const std::string m_pathToFileToMock;
  const std::string m_mockDir;
  ElementToMockContext m_ctxt;
  bool m_rmDir;

  void SetUp() override;
  virtual void ExtraSetup() {}

  void TearDown() override;
  virtual void ExtraTearDown() {}

  void getFunPtr(void **fPtr, void **fExpectPtr);
  void getFunPtr(void **fPtr, void **fExpectPtr, void **fMatcherPtr);
  void getFunPtr(void **fPtr, void **fExpectPtr, void **fMatcherPtr, void **fOutputPtr);
  void setGenerateTypes(bool p_generateTypes);
private:
  void prepareTest(const ElementToMockContext &ctxt, const std::string &functionToMock, std::string &comparatorToMatch, const std::string &fullPathToFileToMock, const std::string &mockDir, void **funcPtr, void **functExpectPtr, void **functMatcherPtr, void **functOutputPtr, void **handle);
  void *handle;
  void *m_fptr;
  void *m_fptr_expect;
  void *m_fptr_matcher;
  void *m_fptr_output_ptr;
  bool m_generate_types;
};

#endif /* TEST_COMMON_H */

