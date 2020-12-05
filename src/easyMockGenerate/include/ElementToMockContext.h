/*! \file
 *
 * \brief Contains the class that defines a context for the elements to be mocked.
 */
#ifndef ELEMENTTOMOCKCONTEXT_H
#define ELEMENTTOMOCKCONTEXT_H

#include "ElementToMock.h"

#include <unordered_map>
#include <string>
#include <vector>

/*!
 * \brief Defines a context for the elements to be mocked.
 */
class ElementToMockContext
{
public:
  /*!
   * \brief Adds an ::ElementToMock into the context.
   *
   * \heapPointer
   */
  void addElementToMock(ElementToMock* p_elementToMock);

  /*!
   * \brief Returns the list of elements to be mocked contained in this context.
   *
   * \return Returns the list of elements to be mocked contained in this context.
   */
  const ElementToMock::Vector& getElementToMock() const;

  /*!
   * \brief Adds a macro definition (i.e <tt>\#define p_id p_definition</tt>) into the context.
   *
   * \param p_id The id of the <tt>\#define</tt> to be added.
   * \param p_definition The definition of the <tt>\#define</tt> to be added.
   */
  void addMacroDefine(const std::string& p_id, const std::string& p_definition);

  /*!
   * \brief Deletes the macro definition with <tt>id == p_id</tt> from the context.
   *
   * \param p_id The id of the <tt>\#define</tt> to be removed
   *
   * If the p_id doesn't exists, this call has no effect.
   */
  void deleteMacroDefine(const std::string &p_id);

  /*!
   * \brief Checks if a macro with <tt>id == p_id</tt> exists.
   *
   * \param p_id The id of the <tt>\#define</tt>. to be added.
   *
   * \return true if the macro with <tt>id == p_id</tt> exists.
   * \return false instead.
   */
  bool hasMacroDefine(const std::string& p_id) const;

  /*!
   * \brief Returns the definition of the macro with <tt>id == p_id</tt>
   *
   * \param p_id The id of the <tt>\#define</tt>..
   *
   * \return The definition of the macro if the id exists.
   * \return An empty std::string if the id doesn't exists.
   */
  const std::string& getMacroDefinition(const std::string& p_id);

  /*!
   * \brief Returns the unordered_map containing all the macro definitions
   * defined in this context.

   * \return Returns the unordered_map containing all the macro definitions
   * defined in this context.
   */
  const std::unordered_map<std::string, std::string>& getCrossDefinedMap() const;

private:
  std::unordered_map<std::string, std::string> m_macroDefinition;
  ElementToMock::Vector m_elementToMock;

};

#endif /* ELEMENTTOMOCKCONTEXT_H */

