#ifndef TYPEITF_H
#define TYPEITF_H

#include <string>
#include "AutoCleanVectorPtr.h"
#include "ComposableField.h"

class TypeItf
{
public:
  explicit TypeItf(const std::string p_name);
  TypeItf(const std::string p_name, const std::string p_typed_def_name);

  typedef AutoCleanVectorPtr<TypeItf> Vector;

  TypeItf(const TypeItf &other) = default;
  TypeItf& operator=(const TypeItf &other) = default;
  TypeItf(TypeItf &&other) = default;
  TypeItf& operator=(TypeItf &&other) = default;

  const std::string &getName() const; //return the basic C type (e.g. int, char) or the tag of a struct of an union
  const std::string &getTypedDefName() const;
  const std::string &getMostDefinedName() const; //If typedef is set, returns it, otherwise returns the name;

  std::string getFullDeclarationName() const; //returns the string that should be used to declare a variable of the type
  std::string getFullNonQualifiedDeclarationName() const; //returns the same as getFullDeclarationName but without the const qualifier

  virtual easyMock_cTypes_t getCType() const;
  virtual ComposableField::Vector& getContainedFields();
  virtual const ComposableField::Vector& getContainedFields() const;

  bool isStruct() const;
  bool isUnion() const;
  bool isCType() const;
  bool isTypedDef() const;
  bool isAnonymous() const;
  bool isComposableType() const;
  bool isPointer() const;
  bool isConst() const;
  bool isImplicit() const;

  TypeItf* setConst(bool value);
  TypeItf* setImplicit(bool value);

  virtual bool isEqual(const TypeItf &other) const;

  bool operator==(const TypeItf &other) const;
  bool operator!=(const TypeItf &other) const;

  virtual TypeItf* clone() const = 0;
  virtual ~TypeItf();

#define TYPEITF_COMMON_CLASS_MEMBERS(prefix) \
  std::string prefix ## name; \
  std::string prefix ## typed_def_name; \
  bool prefix ## isCType; \
  bool prefix ## isStruct; \
  bool prefix ## isUnion; \
  bool prefix ## isPointer; \
  bool prefix ## isConst; \
  bool prefix ## isImplicit;

protected:
  TypeItf(); //Needed for Pointer subclass
  void setStruct(bool value);
  void setUnion(bool value);
  void setCType(bool value);
  void setPointer(bool value);
  void setName(std::string p_name);
  void setTypedDefName(std::string p_typed_def_name);

private:
  static std::string s_getFullDeclarationName(const TypeItf* type, bool fullyQualified);
  typedef struct
  {
    TYPEITF_COMMON_CLASS_MEMBERS()
  } attributes;
  TypeItf(attributes attrib);

  TYPEITF_COMMON_CLASS_MEMBERS(m_)
#undef TYPEITF_COMMON_CLASS_MEMBERS
};

#endif /* TYPEITF_H */

