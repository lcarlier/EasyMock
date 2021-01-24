#include <cstring.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

cstring cstring_new()
{
  cstring rv;
  rv.stack[0] = '\0';
  rv.heap = NULL;

  return rv;
}

cstring cstring_new_init(const char *initVal)
{
  cstring rv = cstring_new();

  cstring_append(&rv, initVal);

  return rv;
}

easyMock_size_t cstring_length(const cstring *s)
{
  if(s->heap)
  {
    return strlen(s->heap);
  }
  else
  {
    return strlen(s->stack);
  }
}

const char* cstring_c_str(const cstring* s)
{
  if(s->heap)
  {
    return s->heap;
  }
  else
  {
    return s->stack;
  }
}

int cstring_compare_const_char(const cstring *s, const char* other)
{
  return strcmp(cstring_c_str(s), other);
}

int cstring_compare_const_cstring(const cstring *s, const cstring* other)
{
  return cstring_compare_const_char(s, cstring_c_str(other));
}

void cstring_append(cstring *s, const char *strToAppend)
{
  size_t currentSize = cstring_length(s);
  size_t sizeToAppend = strlen(strToAppend);
  size_t newSize = currentSize + sizeToAppend + 1;
  char* ptrToUpdate = NULL;
  if(s->heap)
  {
    s->heap = realloc(s->heap, newSize);
    if(s->heap == NULL)
    {
      fprintf(stderr, "Couldn't reallocate the memory: %s",strerror(errno));
      exit(1);
    }
    ptrToUpdate = s->heap;
  }
  else
  {
    if(newSize <= CSTRING_MAX_STACK_SIZE)
    {
      ptrToUpdate = s->stack;
    }
    else
    {
      s->heap = malloc(newSize);
      s->heap[0] = '\0';
      ptrToUpdate = s->heap;
    }
  }
  strcat(ptrToUpdate, strToAppend);
}

void cstring_free(cstring *s)
{
  if(s->heap)
  {
    free(s->heap);
    s->heap = NULL;
  }
}