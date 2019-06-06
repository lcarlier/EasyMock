#ifndef TEST_COMMON_H
#define TEST_COMMON_H

#include <gtest/gtest.h>

#include <string>
#include <CodeParserItf.h>

void createDir(const std::string &dir);
void rmDir(const std::string &dir);
bool isFifoCallEmpty();
std::string getCurrentFifoCall();
int fifoCallSize();

class easyMockGenerate_baseTestCase : public ::testing::Test
{
public:
  easyMockGenerate_baseTestCase(const std::string functionToMock, const std::string pathToFileToMock, const std::string mockDir, bool rmDir = true);
protected:
  const std::string m_functionToMock;
  const std::string m_pathToFileToMock;
  const std::string m_mockDir;
  ElementToMockVector m_elem;
  bool m_rmDir;

  void SetUp() override;

  void TearDown() override;

  void getFunPtr(void **fPtr, void **fExpectPtr);
private:
  void *handle;
  void *m_fptr;
  void *m_fptr_expect;
};

#endif /* TEST_COMMON_H */

