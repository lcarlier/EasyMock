/*! \file
 *
 * \brief Contains the interface which must be implemented by a generator.
 */
#ifndef CODEGENERATORITF_H
#define CODEGENERATORITF_H

#include <string>
#include <unordered_set>
#include "ElementToMockContext.h"

using MockOnlyList = std::unordered_set<std::string>;

/*!
 * \brief The interface which must be implemented by a generator.
 */
class CodeGeneratorItf {
public:
  /*!
   * \brief Generates the mocks.
   *
   * \param p_outDir Directory into which the mocks must be generated
   * \param p_fullPathToHeaderToMock Path to the header to be mocked
   * \param p_elem Vector containing the EasyMock internal object representation
   * of the element to be mocked
   *
   * \return true if the generation of the mocks is successful
   * \return false instead.
   */
  virtual bool generateCode(const std::string& p_outDir, const std::string &p_fullPathToHeaderToMock, const ElementToMockContext& p_elem) = 0;
  void setMockOnlyFunction(const MockOnlyList& list);
  void setGenerateUsedType(bool value);
protected:
  MockOnlyList m_mockOnlyList;
  bool m_generateUsedType;
};

#endif /* CODEGENERATORITF_H */

