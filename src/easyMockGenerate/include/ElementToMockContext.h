/*! \file
 *
 * \brief Contains the class that defines a context for the elements to be mocked.
 */
#ifndef ELEMENTTOMOCKCONTEXT_H
#define ELEMENTTOMOCKCONTEXT_H

#include "ElementToMock.h"
#include "MacroDefinition.h"

#include <unordered_map>
#include <string>
#include <vector>

/*!
 * \brief Defines a context for the elements to be mocked.
 */
class ElementToMockContext
{
public:
  using MacroDefinitionList = std::unordered_map<std::string, MacroDefinition>;
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
  void addMacroDefine(std::string p_id, std::string p_definition);

  /*!
   * \brief Adds a function like macro definition (i.e <tt>\#define p_id(a, b) p_definition</tt>) into the context.
   *
   * \param p_id The id of the <tt>\#define</tt> to be added.
   * \param p_parameters The parameters of the function like macro.
   * \param p_definition The definition of the <tt>\#define</tt> to be added.
   *
   * Variadic macro accepts "..." as last parameter. However no check is done to ensure that
   * "..." is actually the last parameter.
   */
  void addMacroDefine(std::string p_id, std::vector<std::string> p_parameters, std::string p_definition);

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
   * \return A ::MacroDefinition object if the id exists.
   * \return An empty ::MacroDefinition object if the id doesn't exists.
   */
  const MacroDefinition& getMacroDefinition(const std::string& p_id);

  /*!
   * \brief Returns the unordered_map containing all the macro definitions
   * defined in this context.

   * \return Returns the unordered_map containing all the macro definitions
   * defined in this context.
   */
  const std::unordered_map<std::string, MacroDefinition>& getCrossDefinedMap() const;

private:
  MacroDefinitionList m_macroDefinition;
  ElementToMock::Vector m_elementToMock;

};

#endif /* ELEMENTTOMOCKCONTEXT_H */

