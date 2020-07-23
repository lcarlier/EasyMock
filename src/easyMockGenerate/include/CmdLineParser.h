/*! \file
 * \brief Contains the declaration of the class implementing the command line
 * parser.
 */

#ifndef CMDLINEPARSER_H
#define CMDLINEPARSER_H

#include <CommandLineParserItf.h>

/*!
 * \brief The class implementing the command line parser.
 */
class CmdLineParser : public CommandLineParserItf
{
public:
  /*!
   * \copydoc CommandLineParserItf::getParsedArguments
   */
  EasyMockOptions getParsedArguments(int argc,const char* argv[]) const override;

};

#endif /* CMDLINEPARSER_H */

