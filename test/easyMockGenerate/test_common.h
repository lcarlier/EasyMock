#ifndef TEST_COMMON_H
#define TEST_COMMON_H

#include <gtest/gtest.h>

#include <string>
#include <CodeParserItf.h>
#include <easyMock.h>

void createDir(const std::string &dir);
void rmDir(const std::string &dir);
bool isFifoCallEmpty();
std::string getCurrentFifoCall();
int fifoCallSize();
#define ASSERT_NO_ERROR \
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
  easyMockGenerate_baseTestCase(const std::string functionToMock, const std::string pathToFileToMock, const std::string mockDir, bool rmDir = true);
  void setParamToMatch(const std::string paramToMatch);
protected:
  const std::string m_functionToMock;
  std::string m_paramToMatch;
  const std::string m_pathToFileToMock;
  const std::string m_mockDir;
  ElementToMock::Vector m_elem;
  bool m_rmDir;

  void SetUp() override;

  void TearDown() override;

  void getFunPtr(void **fPtr, void **fExpectPtr);
  void getFunPtr(void **fPtr, void **fExpectPtr, void **fMatcherPtr);
private:
  void *handle;
  void *m_fptr;
  void *m_fptr_expect;
  void *m_fptr_matcher;
};

#endif /* TEST_COMMON_H */

