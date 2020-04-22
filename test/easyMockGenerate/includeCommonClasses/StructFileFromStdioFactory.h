#ifndef STRUCTFILEFROMSTDIOFACTORY_H
#define STRUCTFILEFROMSTDIOFACTORY_H

#include <FunctionFactory.h>
#include <structFileFromStdio.h>

class StructFileFromStdioFactory : public FunctionFactory<int, std::tuple<T_MY_IO_FILE>, std::tuple<EasyMock_Matcher>>
{
public:
public:
  Function functionFactory() override;
  Function* newFunctionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;

};

#endif /* STRUCTFILEFROMSTDIOFACTORY_H */

