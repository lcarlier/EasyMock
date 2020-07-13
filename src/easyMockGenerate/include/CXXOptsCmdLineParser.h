/*! \file
 * \brief Contains the declaration of the class implementing the command line
 * parser using cxxopts.
 *
 * \see https://github.com/jarro2783/cxxopts
 */
#ifndef CXXOPTSCMDLINEPARSER_H
#define CXXOPTSCMDLINEPARSER_H

#include <CommandLineParserItf.h>

/*!
 * \brief The class implementing the command line parser using cxxopts.
 */
class CXXOptsCmdLineParser : public CommandLineParserItf
{
public:
  /*!
   * \copydoc CommandLineParserItf::getParsedArguments
   */
  EasyMockOptions getParsedArguments(int argc, char* argv[]) const override;

};

#endif /* CXXOPTSCMDLINEPARSER_H */

