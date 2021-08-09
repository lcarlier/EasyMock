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
using GenerateAttrList = std::unordered_set<std::string>;

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
  bool generateCode(const std::string& p_outDir, const std::string &p_fullPathToHeaderToMock, const ElementToMockContext& p_elem);
  /*!
   * \brief Sets the list of functions to be mocked.
   * \param p_list The list of function to mock.
   *
   * Only the list of functions provided into the parameter will be mocked. The rest will be ignored.
   */
  void setMockOnlyFunction(MockOnlyList p_list);
  /*!
   * \brief Sets the function attributes to generate.
   * \param p_list The list of function attributes to generated.
   */
  void setGenerateAttrList(GenerateAttrList p_list);
  /*!
   * \brief Specifies whether the mock must generate the used type or not.
   *
   * \param p_value true if the mock must generate the used type else false.
   *
   * When the used type are generated, the mocked function signature is also part of the generated mock header file.
   * This means that that original header file doesn't need to be used when compiling the mock.
   */
  void setGenerateUsedType(bool p_value);
protected:

  /*!
   * \brief Method to be overridden by any classes generating the mocks.
   *
   * \copydetails ::CodeGeneratorItf::generateCode
   */
  virtual bool generateCodeImplementation(const std::string& p_outDir, const std::string &p_fullPathToHeaderToMock, const ElementToMockContext& p_elem) = 0;
  MockOnlyList m_mockOnlyList;
  GenerateAttrList m_generateAttrList;
  bool m_generateUsedType;
};

#endif /* CODEGENERATORITF_H */
