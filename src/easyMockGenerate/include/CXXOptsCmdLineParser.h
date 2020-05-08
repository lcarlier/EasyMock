#ifndef CXXOPTSCMDLINEPARSER_H
#define CXXOPTSCMDLINEPARSER_H

#include <CommandLineParserItf.h>

class CXXOptsCmdLineParser : public CommandLineParserItf
{
public:
  EasyMockOptions getParsedArguments(int argc, char* argv[]) const override;

};

#endif /* CXXOPTSCMDLINEPARSER_H */

