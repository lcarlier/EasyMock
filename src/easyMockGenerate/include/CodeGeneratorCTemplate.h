#ifndef CODEGENERATORCTEMPLATE_H
#define CODEGENERATORCTEMPLATE_H

#include <CodeGeneratorItf.h>
#include <ctemplate/template.h>
#include <string>
#include <unordered_set>

class CodeGeneratorCTemplate : public CodeGeneratorItf
{
public:
  CodeGeneratorCTemplate();
  bool generateCode(const std::string& outDir, const std::string &headerToMock, const ElementToMock::Vector& elem);
private:
  void fillInTemplateVariables(ctemplate::TemplateDictionary *dict, const std::string &mockedHeader, const ElementToMock::Vector &fList);
  void generateFunctionSection(ctemplate::TemplateDictionary *rootDictionnary, const ElementToMock *f);
  void generateFunctionParamSection(ctemplate::TemplateDictionary *rootDictionnary, ctemplate::TemplateDictionary *dict, const Parameter::Vector *functionParam);
  void generateBodyStructCompare(ctemplate::TemplateDictionary *rootDictionnary, ctemplate::TemplateDictionary *paramSectDict, const TypeItf *p_structType, const StructField *curField);
  void generateStructCompareSection(ctemplate::TemplateDictionary *rootDictionnary, const TypeItf *structType);
  bool generateCodeToFile(const std::string &outDir, const std::string &filename, const std::string &extension, const std::string &generatedCode);
  std::string getDeclaratorString(const Declarator* decl);
  void generateBasicTypeField(const StructField *curField, ctemplate::TemplateDictionary *paramSectDict, const TypeItf *p_structType);

  std::unordered_set<std::string> m_generatedStructs;
};

#endif /* CODEGENERATORCTEMPLATE_H */

