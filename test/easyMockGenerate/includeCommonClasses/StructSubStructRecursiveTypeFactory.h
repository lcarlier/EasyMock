#ifndef STRUCTSUBSTRUCTRECURSIVETYPEFACTORY_H
#define STRUCTSUBSTRUCTRECURSIVETYPEFACTORY_H

#include <FunctionFactory.h>
#include <easyMock.h>
#include <structSubStructRecursiveType.h>

class StructSubStructRecursiveTypeFactory : public FunctionFactory<unsigned short, std::tuple<struct st1*>, std::tuple<EasyMock_Matcher>>
{
public:
  Function functionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;
  //No test en generates because it boils down of testing the field structures that are pointers
};

#endif /* STRUCTSUBSTRUCTRECURSIVETYPEFACTORY_H */

