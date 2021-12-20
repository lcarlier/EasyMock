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
#include <unordered_map>

#include <EasyMock_Hashable.h>

class Declarator;
class FunctionDeclaration;
class FunctionType;
class ComposableType;
class ComposableFieldItf;
class TypedefType;
class TypeItf;
class Enum;

/*!
 * \brief CTemplate based implementation of the generator
 *
 * This implementation uses Google libctemplate. Bear in mind that the term
 * template here has nothing to do with C++ templated class. The 2 main
 * templates are:
 * * #anonymous_namespace{CodeGeneratorCTemplate.cpp}::templateText: \copydoc anonymous_namespace{CodeGeneratorCTemplate.cpp}::templateText
 * * #anonymous_namespace{CodeGeneratorCTemplate.cpp}::headerFileTemplate: \copydoc anonymous_namespace{CodeGeneratorCTemplate.cpp}::headerFileTemplate
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
private:
  enum class GenerateDeclarationOfComposableTypeOrigin
  {
    GENERATE_COMPARE_FUNCTION,
    GENERATE_TOP_LEVEL_USED_TYPE,
    GENERATE_SUB_LEVEL_USED_TYPE
  };
public:
  CodeGeneratorCTemplate();
protected:
  /*!
   * \copydoc ::CodeGeneratorItf::generateCodeImplementation
   */
  bool generateCodeImplementation(const std::string& p_outDir, const std::string &p_fullPathToHeaderToMock, const ElementToMockContext& p_elem) override;
private:
  void fillInTemplateVariables(const std::string &mockedHeader, const ElementToMockContext &p_ctxt);
  void fillInMacroDefinition(const ElementToMockContext& p_elem);
  void generateFunctionSection(const FunctionDeclaration *f);
  void generateFunctionAttributes(const FunctionDeclaration *f, ctemplate::TemplateDictionary *functionSectionDict);
  void generateFunctionParamSection(ctemplate::TemplateDictionary *dict, const Parameter::Vector& functionParam);
  //p_uniquePrepend and p_declPrepend must never become a reference because the string appended in recursive calls must reverted when the recursive call returns
  void generateAllFieldStructCompare(ctemplate::TemplateDictionary *p_compareFunDict, const ComposableType *p_composedType, std::string p_uniquePrepend, std::string p_declPrepend);
  void generateBodyStructCompare(ctemplate::TemplateDictionary *p_compareFunDict, const char* p_sectionToAdd, const ComposableType *p_structType, const ComposableFieldItf *p_curField, const ComposableFieldItf *p_previousField, std::string p_uniquePrepend, std::string p_declPrepend);
  void generateComposedTypedCompareSection(const ComposableType *p_composedType, std::string p_uniquePrepend, std::string p_declPrepend);
  ctemplate::TemplateDictionary* generateDeclarationOfComposableType(ctemplate::TemplateDictionary *compareDir, const ComposableType *p_composedType, int p_level, GenerateDeclarationOfComposableTypeOrigin p_origin);
  void generateDeclarationOfUsedType(ctemplate::TemplateDictionary* p_parentDict, const TypeItf* p_type, bool p_generateIncomplete);
  bool generateCodeToFile(const std::string &outDir, const std::string &filename, const std::string &extension, const std::string &generatedCode);
  std::string getDeclaratorString(const Declarator& p_decl);
  std::string getNonQualifiedDeclaratorString(const Declarator& p_decl);
  void generateBasicTypeField(const ComposableFieldItf *curField, ctemplate::TemplateDictionary *paramSectDict, const ComposableType *p_composedType, std::string p_declPrepend);
  void generateExtraDecl(ctemplate::TemplateDictionary *dict, const char *sectionName, const char *templateFileName, const FunctionType *ft);
  void generateFieldCmp(std::string &p_condition, const ComposableType *p_composedType, const ComposableFieldItf *p_curField, const ComposableFieldItf *p_previousField, std::string p_varName);
  void setStructCompareStringFormat(ctemplate::TemplateDictionary *p_errorDict, const TypeItf* p_curFieldType);
  bool isTypeGenerated(const TypeItf* p_type, bool p_insert);
  void generateSimpleTypeDef(const TypeItf* p_type);
  void generateEnum(const TypeItf* p_type);
  std::string getAnonymousTypedefUniqueName(const TypeItf* p_type);
  template <class T>
  std::string getComparatorName(const T* p_composableType);
  void registerTypeDef(const TypeItf* p_type);
  const std::string& getTypeDefName(const TypeItf* p_type);
  const TypeItf* getRawType(const TypeItf* p_type);
  const std::string& getMostDefinedName(const TypeItf* p_type);
  void generateForwardDeclaration(const TypeItf* p_type);

  const TypeItf* getMostPointedType(const TypeItf* p_type);

  std::unordered_set<std::string> m_generatedComparator;
  unsigned int m_nbUnamedParam;
  ctemplate::TemplateDictionary *m_rootDictionary;
  ctemplate::TemplateDictionary *m_generateMockedTypeSection;
  EasyMock::HashablePointerUnorderedMap<const TypeItf*, const TypedefType*> m_typeToTypedef;
  EasyMock::HashablePointerUnorderedSet<const TypeItf*> m_generateTypes;
  EasyMock::HashablePointerUnorderedSet<const TypeItf*> m_generateForwardTypes;
  EasyMock::HashablePointerUnorderedSet<const TypedefType*> m_generatedTypeTypedDefSection;
  EasyMock::HashablePointerUnorderedSet<const Enum*> m_generatedTypeEnumSection;
  std::vector<const ComposableType*> m_lateDeclaration;
};

#endif /* CODEGENERATORCTEMPLATE_H */
