#include <MockedFunction.h>

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x)/sizeof((x)[0]))
#endif

static void MockedFunction_emptyDataQueue(MockedFunction* mf);
static bool MockedFunction_isEmpty(MockedFunction* mf);
static unsigned int MockedFunction_getCurrentIdx(MockedFunction* mf);

void MockedFunction_init(MockedFunction *mf, const char* name, size_t dataSize)
{
  mf->name = name;
  mf->dataSize = dataSize;
  mf->actualCall = 0;
  mf->expectedCall = 0;
  unsigned int dataQueueIdx;
  for(dataQueueIdx = 0; dataQueueIdx < ARRAY_SIZE(mf->mockedData); dataQueueIdx++)
  {
    mf->mockedData[dataQueueIdx] = NULL;
  }
}

void MockedFunction_addExpectedCall(MockedFunction *mf, const void* data)
{
  if(mf->expectedCall == EASYMOCK_MAX_MOCKED_CALL)
  {
    fprintf(stderr, "No possible to queue more callbacks. Increase EASYMOCK_MAX_MOCKED_CALL macro\n\r");
    exit(1);
  }
  if(mf->mockedData[mf->expectedCall])
  {
    fprintf(stderr, "Bug in the framework. Trying to use an already used item in the queue\n\r");
    exit(1);
  }
  mf->mockedData[mf->expectedCall] = malloc(mf->dataSize);
  if(mf->mockedData[mf->expectedCall] == NULL)
  {
    fprintf(stderr, "No more memory available to allocate an item to queue: %s\n\r", strerror(errno));
    exit(1);
  }
  memcpy(mf->mockedData[mf->expectedCall], data, mf->dataSize);
  mf->expectedCall++;
}

bool MockedFunction_getCurrentCallParam(MockedFunction *mf, void* data)
{
  if(MockedFunction_isEmpty(mf))
  {
    return false;
  }
  unsigned int currentIdx = MockedFunction_getCurrentIdx(mf);
  if(mf->mockedData[currentIdx] == NULL)
  {
    fprintf(stderr, "Bug in the framework. Get the call of an empty index\n\r");
    exit(1);
  }
  memcpy(data, mf->mockedData[currentIdx], mf->dataSize);
  free(mf->mockedData[currentIdx]);
  mf->mockedData[currentIdx] = NULL;
  return true;
}

bool MockedFunction_addActualCall(MockedFunction *mf)
{
  /*
   * Increment the actualCall anyway because MockedFunction_verify()
   * will check the equality of m_actualCall and m_expectedCall
   */
  mf->actualCall++;
  if ((mf->actualCall - 1) == mf->expectedCall)
  {
    return false;
  }
  return true;
}

unsigned int MockedFunction_getNbActualCall(MockedFunction *mf)
{
  return mf->actualCall;
}

const char* MockedFunction_getName(MockedFunction *mf)
{
  return mf->name;
}

void MockedFunction_reset(MockedFunction *mf)
{
  mf->expectedCall = 0;
  mf->actualCall = 0;
  MockedFunction_emptyDataQueue(mf);
}

bool MockedFunction_verify(MockedFunction *mf)
{
  if (mf->expectedCall != mf->actualCall)
  {
    easyMock_addError(false, "Error: For function '%s' bad number of call. "
                             "Expected %d, got %d",
                             mf->name, mf->expectedCall, mf->actualCall);
    return false;
  }
  return true;
}

static void MockedFunction_emptyDataQueue(MockedFunction* mf)
{
  unsigned int data_queue_idx;
  for(data_queue_idx = 0; data_queue_idx < ARRAY_SIZE(mf->mockedData); data_queue_idx++)
  {
    if(mf->mockedData[data_queue_idx])
    {
      free(mf->mockedData[data_queue_idx]);
      mf->mockedData[data_queue_idx] = NULL;
    }
  }
}

static bool MockedFunction_isEmpty(MockedFunction* mf)
{
  unsigned int data_queue_idx;
  for(data_queue_idx = 0; data_queue_idx < ARRAY_SIZE(mf->mockedData); data_queue_idx++)
  {
    if(mf->mockedData[data_queue_idx])
    {
        return false;
    }
  }
  return true;
}

static unsigned int MockedFunction_getCurrentIdx(MockedFunction* mf)
{
  if(mf->actualCall == 0)
  {
    fprintf(stderr, "Bug in the framework. Getting the index with actuallCall == 0\n\r");
    exit(1);
  }
  return mf->actualCall - 1;
}
