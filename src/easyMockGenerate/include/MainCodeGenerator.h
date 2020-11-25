/*! @file
 *
 * \brief Contains the class implementing the main logic for generating the mocks
 */
#ifndef CODEPARSER_H
#define CODEPARSER_H

#include <vector>
#include <string>

#include "CodeParserItf.h"
#include "CodeGeneratorItf.h"

/*!
 * \brief Implements the main logic for generating the mocks.
 *
 * To generate the mocks, the user of the class can choose the strategy
 * for parsing and generating the code code.
 *
 * The current strategy implemented for parsing the code is:
 * * LLVMParser
 *
 * The current strategy implemented to generate the mocks is:
 * * CodeGeneratorCTemplate.
 *
 * User willing to implement a new strategy to parse the header file or to
 * generate the mocks need to implement the interface by CodeParserItf and
 * CodeGeneratorItf respectively. It is only needed to give the correct instance
 * to the code
 */
class MainCodeGenerator
{
public:
  /*!
   * \brief Creates a new MainCodeGenerator instance.
   */
  MainCodeGenerator(const std::string p_filename, CodeParserItf &p_codeParser, CodeGeneratorItf &p_codeGenerator);
  /*!
   * \brief Calls the logic to parse and generate the mocks.
   *
   * \return True if the mocks have been successfully generated. I.e.
   * * The header has been correctly parsed.
   * * The code containing the mocks exists in outDir.
   */
  bool generateCode(const std::string &outDir);
private:
  std::string m_filename;
  CodeParserItf &m_codeParserItf;
  CodeGeneratorItf &m_codeGeneratorItf;
};

#endif /* CODEPARSER_H */

