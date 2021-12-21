/*! \file
 * \brief Contains the interface that must be implemented by a parser.
 */
#ifndef CODEPARSERITF_H
#define CODEPARSERITF_H

#include <string>
#include <vector>
#include <functional>

#include "CommonParserGenerator.h"
#include "ComposableType.h"

class ElementToMockContext;

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
  m_filename(""), m_flags({}), m_mockOnlyList{}, m_ignoreTypeFieldList{}
  {}
  CodeParserItf(std::string& filename, ParserExtraArgs& flags) :
  m_filename(filename), m_flags(flags), m_mockOnlyList{}, m_ignoreTypeFieldList{}
  {}

  /*!
   * \brief Sets the path to the header file to be parsed.
   */
  void setFilename(const std::string& filename) { m_filename = filename; }

  /*!
   * \brief Sets the compiler flags that must be used by the parser to parse
   * the file.
   */
  void setFlags(const ParserExtraArgs& flags) { m_flags = flags; }

  /*!
   * \brief Parses the header file.
   *
   * \param p_ctxt Output parameter which contains the context of the elment to be mocked.
   * If an error happens, the list is not valid and can't be used.
   *
   * \see ::ElementToMockContext
   *
   * \return cp_OK if no error occurred.
   */
  virtual CodeParser_errCode getElementToMockContext(ElementToMockContext& p_ctxt) const = 0;

  /*!
   * \brief Sets the list of functions to be parsed.
   * \param p_list The list of function to parse.
   *
   * Only the list of functions provided into the parameter will be parsed. The rest will be ignored.
   */
  void setMockOnlyFunction(MockOnlyList p_list) { m_mockOnlyList = std::move(p_list); };

  /*!
   * \brief Sets the list of types whose field parsing must be ignored.
   * \param p_list The list of types whose field parsing must be ignored.
   *
   * Set the parser to ignore parsing the field of specific types.
   */
  void setIgnoreTypeFieldList(IgnoreTypeFieldList p_list) { m_ignoreTypeFieldList = std::move(p_list); };

  /*!
   * \brief Sets the list of function whose parsing must be ignored.
   * \param p_list The list of function whose parsing must be ignored.
   *
   * Set the parser to ignore parsing the specified functions.
   */
  void setIgnoreFunList(IgnoreFunList p_list) { m_ignoreFunList = std::move(p_list); };
protected:
  std::string m_filename;
  ParserExtraArgs m_flags;
  MockOnlyList m_mockOnlyList;
  IgnoreTypeFieldList m_ignoreTypeFieldList;
  IgnoreFunList m_ignoreFunList;
};

#endif /* CODEPARSERITF_H */
