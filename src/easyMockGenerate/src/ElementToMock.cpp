#include "ElementToMock.h"

ElementToMock::~ElementToMock() { }

size_t ElementToMock::getHash() const noexcept
{
  return 0;
}

void ElementToMock::cacheHash() noexcept
{}
