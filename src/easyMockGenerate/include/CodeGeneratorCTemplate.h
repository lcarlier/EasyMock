#ifndef CODEGENERATORCTEMPLATE_H
#define CODEGENERATORCTEMPLATE_H

#include <CodeGeneratorItf.h>
#include <ctemplate/template.h>
#include <string>
#include <unordered_set>

class Declarator;

class CodeGeneratorCTemplate : public CodeGeneratorItf
{
public:
  CodeGeneratorCTemplate();
  bool generateCode(const std::string& outDir, const std::string &headerToMock, const ElementToMock::Vector& elem);
private:
  void fillInTemplateVariables(ctemplate::TemplateDictionary *dict, const std::string &mockedHeader, const ElementToMock::Vector &fList);
  void generateFunctionSection(ctemplate::TemplateDictionary *rootDictionnary, const ElementToMock *f);
  void generateFunctionParamSection(ctemplate::TemplateDictionary *rootDictionnary, ctemplate::TemplateDictionary *dict, const Parameter::Vector& functionParam);
  //p_uniquePrepend and p_declPrepend must never become a reference because the string appended in recursive calls must reverted when the recursive call returns
  void generateBodyStructCompare(ctemplate::TemplateDictionary *rootDictionnary, ctemplate::TemplateDictionary *paramSectDict, const ComposableType *p_structType, const ComposableField *p_curField, const ComposableField *p_previousField, std::string p_uniquePrepend, std::string p_declPrepend);
  void generateComposedTypedCompareSection(ctemplate::TemplateDictionary *rootDictionnary, const ComposableType *p_composedType, std::string p_uniquePrepend, std::string p_declPrepend);
  void generateDeclarationOfAnonymousType(ctemplate::TemplateDictionary *compareDir, const ComposableType *p_composedType);
  bool generateCodeToFile(const std::string &outDir, const std::string &filename, const std::string &extension, const std::string &generatedCode);
  const std::string& getDeclaratorString(const Declarator* p_decl);
  std::string getNonQualifiedDeclaratorString(const Declarator* p_decl);
  void generateBasicTypeField(const ComposableField *curField, ctemplate::TemplateDictionary *paramSectDict, const ComposableType *p_composedType, std::string p_declPrepend);

  void generateFieldCmp(std::string &p_condition, const ComposableType *p_composedType, const ComposableField *p_curField, const ComposableField *p_previousField, std::string p_varName);

  std::unordered_set<std::string> m_generatedComparator;
  unsigned int m_nbUnamedParam;
};

#endif /* CODEGENERATORCTEMPLATE_H */

