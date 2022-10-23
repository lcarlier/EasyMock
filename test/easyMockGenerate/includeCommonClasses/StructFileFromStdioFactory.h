#ifndef STRUCTFILEFROMSTDIOFACTORY_H
#define STRUCTFILEFROMSTDIOFACTORY_H

#include <FunctionFactory.h>
#include <structFileFromStdio.h>

class StructFileFromStdioFactory : public FunctionFactory<int, std::tuple<T_MY_IO_FILE>, std::tuple<EasyMock_Matcher>>
{
public:
  std::shared_ptr<FunctionDeclaration> functionFactory() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;

};

class StructFileFromStdioGenerateTypeFactory : public StructFileFromStdioFactory
{
public:
  StructFileFromStdioGenerateTypeFactory() { m_generate_types = true; }
};

#endif /* STRUCTFILEFROMSTDIOFACTORY_H */
