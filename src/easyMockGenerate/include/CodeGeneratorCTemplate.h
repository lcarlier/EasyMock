/*! \file
 *
 * \brief Contains the CodeGeneratorCTemplate which is the CTemplate
 * implementation of the generator.
 */
#ifndef CODEGENERATORCTEMPLATE_H
#define CODEGENERATORCTEMPLATE_H

#include <CodeGeneratorItf.h>
#include <ctemplate/template.h>
#include <string>
#include <unordered_set>

class Declarator;
class FunctionDeclaration;
class FunctionType;
class ComposableType;
class ComposableFieldItf;

/*!
 * \brief CTemplate based implementation of the generator
 *
 * This implementation uses Google libctemplate. Bear in mind that the term
 * template here has nothing to do with C++ templated class. The 2 main
 * templates are:
 * * #templateText: \copydoc templateText
 * * #headerFileTemplate: \copydoc headerFileTemplate
 *
 * In order to abstract the syntax of CTemplate, a set of C macro have been
 * implemented.
 *
 * The following sets of macro helps printing template variable (e.g. the
 * function name of the function being mocked).
 * * #TEMPLATE_VAR: \copydoc TEMPLATE_VAR
 *
 * Sections are used to generate code structure that needs repetition.
 * (e.g. the body of a mocked function):
 * * #TEMPLATE_BEG_SECTION: \copydoc TEMPLATE_BEG_SECTION
 * * #TEMPLATE_END_SECTION: \copydoc TEMPLATE_END_SECTION
 *
 * Some macro are implemented to print element conditionally:
 * * #IF_RETURN_VALUE: \copydoc IF_RETURN_VALUE
 * * #IF_SECTION_EXISTS: \copydoc IF_SECTION_EXISTS
 *
 * Finally, there are some helper macro defined:
 * * #FUNCTION_PARAM_LIST: \copydoc FUNCTION_PARAM_LIST
 * * #FUNCTION_PARAM_CALL: \copydoc FUNCTION_PARAM_CALL
 * * #FUNCTION_HARDCODED_PARAM_CALL: \copydoc FUNCTION_HARDCODED_PARAM_CALL
 */
class CodeGeneratorCTemplate : public CodeGeneratorItf
{
public:
  CodeGeneratorCTemplate();
  bool generateCode(const std::string& p_outDir, const std::string &p_fullPathToHeaderToMock, const ElementToMockContext& p_elem) override;
private:
  void fillInTemplateVariables(ctemplate::TemplateDictionary *dict, const std::string &mockedHeader, const ElementToMock::Vector &fList);
  void fillInMacroDefinition(const ElementToMockContext& p_elem);
  void generateFunctionSection(ctemplate::TemplateDictionary *rootDictionnary, const FunctionDeclaration *f);
  void generateFunctionParamSection(ctemplate::TemplateDictionary *rootDictionnary, ctemplate::TemplateDictionary *dict, const Parameter::Vector& functionParam);
  //p_uniquePrepend and p_declPrepend must never become a reference because the string appended in recursive calls must reverted when the recursive call returns
  void generateBodyStructCompare(ctemplate::TemplateDictionary *rootDictionnary, ctemplate::TemplateDictionary *paramSectDict, const ComposableType *p_structType, const ComposableFieldItf *p_curField, const ComposableFieldItf *p_previousField, std::string p_uniquePrepend, std::string p_declPrepend);
  void generateComposedTypedCompareSection(ctemplate::TemplateDictionary *p_rootDictionnary, const ComposableType *p_composedType, std::string p_uniquePrepend, std::string p_declPrepend);
  ctemplate::TemplateDictionary* generateDeclarationOfAnonymousType(ctemplate::TemplateDictionary *p_rootDictionnary, ctemplate::TemplateDictionary *compareDir, const ComposableType *p_composedType, bool p_forceAnonymousType);
  void generateDeclarationOfUsedType(ctemplate::TemplateDictionary *p_rootDictionnary, const TypeItf* p_type);
  bool generateCodeToFile(const std::string &outDir, const std::string &filename, const std::string &extension, const std::string &generatedCode);
  std::string getDeclaratorString(const Declarator* p_decl);
  std::string getNonQualifiedDeclaratorString(const Declarator* p_decl);
  void generateBasicTypeField(const ComposableFieldItf *curField, ctemplate::TemplateDictionary *paramSectDict, const ComposableType *p_composedType, std::string p_declPrepend);
  void generateExtraDecl(ctemplate::TemplateDictionary *p_rootDictionnary, ctemplate::TemplateDictionary *dict, const char *sectionName, const char *templateFileName, const FunctionType *ft);
  void generateFieldCmp(std::string &p_condition, const ComposableType *p_composedType, const ComposableFieldItf *p_curField, const ComposableFieldItf *p_previousField, std::string p_varName);
  void setStructCompareStringFormat(ctemplate::TemplateDictionary *p_errorDict, const TypeItf* p_curFieldType);

  std::unordered_set<std::string> m_generatedComparator;
  unsigned int m_nbUnamedParam;
  ctemplate::TemplateDictionary *m_generateMockedTypeSection;
  std::unordered_set<std::string> m_generateTypes;
};

#endif /* CODEGENERATORCTEMPLATE_H */

