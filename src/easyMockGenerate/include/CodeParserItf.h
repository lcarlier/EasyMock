/*! \file
 * \brief Contains the interface that must be implemented by a parser.
 */
#ifndef CODEPARSERITF_H
#define CODEPARSERITF_H

#include <string>
#include <vector>
#include <functional>

#include "ElementToMock.h"
#include "ComposableType.h"

enum CodeParser_errCode
{
  cp_OK
};

using ParserExtraArgs = std::vector<std::string>;

/*!
 * \brief The interface that must be implemented by a parser.
 *
 * A class which implements this interface must parses the header file
 * whose path is in m_filename. The compilation flags given to the compiler
 * are available in m_flags. In its implementation of getElementToStub, the
 * class fills the p_elem vector with all the functions the parser has found
 * in the header file using the
 * [EasyMock internal objects](md_docs_architecture.html#user-content-eio).
 */
class CodeParserItf
{
public:
  CodeParserItf() :
  m_filename(""), m_flags({}) {}
  CodeParserItf(std::string& filename, ParserExtraArgs& flags) :
  m_filename(filename), m_flags(flags)
  {}

  /*!
   * \brief Sets the path to the header file to be parsed.
   */
  //setFilename is also going to initilise the hash type for anonymous name of the structs and unions comparator functions
  void setFilename(const std::string& filename) { m_filename = filename; ComposableType::setFileHash(std::hash<std::string>{}(filename)); }
  /*!
   * \brief Sets the compiler flags that must be used by the parser to parse
   * the file.
   */
  void setFlags(const ParserExtraArgs& flags) { m_flags = flags; }
  /*!
   * \brief Parses the header file.
   *
   * \param p_elem Output parameter which contains the element to be mocked.
   * If an error happens, the list is not valid and can't be used.
   *
   * \return cp_OK if no error occurred.
   */
  virtual CodeParser_errCode getElementToStub(ElementToMock::Vector &p_elem) const = 0;
protected:
  std::string m_filename;
  ParserExtraArgs m_flags;
};

#endif /* CODEPARSERITF_H */

