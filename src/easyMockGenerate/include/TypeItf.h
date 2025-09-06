/*! \file
 *
 * \brief Contains the base class of most of the [EasyMock internal objects](md_docs_architecture.html#user-content-eio).
 */
#ifndef TYPEITF_H
#define TYPEITF_H

#include <string>
#include <memory>
#include <vector>
#include "EasyMockGenerateTypes.h"
#include "EasyMock_Hashable.h"

class FunctionType;
class TypedefType;
class Enum;
class ComposableType;
class Pointer;
class Reference;
class QualifiedType;
class IncompleteType;
class CType;
struct Namespace;

/*!
 * \brief Base class of all types related classes
 */
class TypeItf : virtual public EasyMock::Hashable
{
public:
  TypeItf(const TypeItf &other) = delete;
  TypeItf& operator=(const TypeItf &other) = delete;
  TypeItf(TypeItf &&other) = default;
  TypeItf& operator=(TypeItf &&other) = default;

  /*!
   * \return The basic C type (e.g. int, char) or the tag of a struct of an union
   */
  const std::string &getName() const;

  /*!
   * \brief Function called by the subclasses to set the type name.
   *
   * For C type, it is the string to be used to declare a variable of that C type (e.g. <tt>unsigned int</tt>).
   *
   * For C union, C struct and C enum, it is the name of the type without its keyword. Not the typedef alias.
   *
   * Pointer object does not call this function because a pointer doesn't have a name, so the type name remains empty.
   */
  void setName(std::string p_name);

  /*!
   *
   * \brief Convenience function which calls ::TypeItf::getDeclarationPrefix and ::TypeItf::getDeclarationPostfix putting
   * a space in between
   *
   * \param p_naked Return the string removing any typedef if any
   *
   * \return The string resulting of the call to ::TypeItf::getDeclarationPrefix and ::TypeItf::getDeclarationPostfix
   * putting a space in between
   */
  std::string getFullDeclarationName(bool p_naked = false) const;

  [[nodiscard]]
  std::string getCxxFullDeclarationName() const;

  /*!
   * \brief Generates the string to be put before a variable name when being declared.
   *
   * \param p_naked Return the string removing any typedef if any
   *
   * \sa ::TypeItf::getDeclarationPostfix
   *
   * \return the string to be put before a variable name when being declared.
   */
  virtual std::string getDeclarationPrefix(bool p_naked = false) const = 0;

  /*!
   * \brief Generates the string to use after the variable name when being declared.
   *
   * The main purpose of this function is to get the string to be put after the variable name when a pointer to
   * a function is being declared.
   *
   * e.g.
   *
   * \code{.c}
   * int (*foo)(int param);
   * \endcode
   *
   * In the above declaration, foo is declared as a pointer to a function(int) returning int.
   * ::TypeItf::getDeclarationPostfix is going to return `)(int param)`.
   *
   * \return The string to use after the variable name when being declared
   */
  virtual std::string getDeclarationPostfix(bool p_naked = false) const;

  /*!
   * \brief Returns the raw type
   *
   * A raw type is a type without any of its qualifier, typedef and completely dereferenced.
   *
   * e.g. The raw type of
   * \code{.c}
   * const char*
   * \endcode
   * is
   * \code{.c}
   * char
   * \endcode
   *
   * \return The raw type underneath this object
   */
  const TypeItf* getRawType() const;

  /*!
   * \copydoc  ::TypeItf::getRawType() const
   */
  TypeItf* getRawType();

  /*!
   * \brief Returns the C type this type defines
   * \warning The value returned is only valid if ::TypeItf::isCType() returns true
   * \return If this type is a C type, the actual type
   * \return If this is not a C type, returns easyMock_cTypes_t::CTYPE_INVALID
   */
  virtual easyMock_cTypes_t getCType() const;

  /*!
   * \brief Returns if the type is a struct.
   *
   * i.e. This type represents the following C code snippet
   * \code{.c}
   * struct structName
   * {
   *     // fields definition
   * };
   * \endcode
   * When this function returns true, the pointer or reference holding this type
   * can be safely downcasted to a ::ComposableType instance or a ::StructType instance.
   *
   * The fields definition can be access via the ::ComposableType::getContainedFields() function.
   *
   * \return True if the type is a struct.
   * \return False instead.
   */
  bool isStruct() const;

  //bool isClass() const;

  /*!
   * \brief Returns if the type is an union.
   *
   * i.e. This type represents the following C code snippet
   * \code{.c}
   * union unionName
   * {
   *     // fields definition
   * };
   * \endcode
   * When this function returns true, a pointer or reference holding this type
   * can be safely downcasted to a ::ComposableType instance or a ::UnionType instance.
   *
   * The fields definition can be access via the ::ComposableType::getContainedFields() function.
   *
   * \return True if the type is an union.
   * \return False instead.
   */
  bool isUnion() const;

  /*!
   * \brief Returns if the type is a C type.
   *
   * All the basic C types (int, short, float, ...) are considered to be a valid C type
   *
   * When this function returns true, a pointer or reference holding this type
   * can be safely downcasted to a ::CType instance.
   *
   * When this function returns true, the function ::TypeItf::getCType() returns the actual
   * C type this type defines
   *
   * \return True if the type is an union.
   * \return False instead.
   */
  bool isCType() const;

  /*!
   * \brief Cast a ::TypeItf pointer to a ::CType pointer.
   *
   * \return If this is a pointer to ::CType, returns the casted pointed
   * \return Else returns nullptr
   */
  const CType* asCType() const;

  /*!
   * \copydoc ::TypeItf::asCType() const
   */
  CType* asCType();

  /*!
   * \brief Returns if the type has a typedef alias.
   *
   * When this function returns true, an pointer to instance of this object can be downcasted to a ::TypedefType object;
   *
   * \return True if the type has a typedef alias
   * \return False instead.
   */
  bool isTypedDef() const;

  /*!
   * \brief Cast a ::TypeItf pointer to a ::TypedefType pointer.
   *
   * \return If this is a pointer to ::TypedefType, returns the casted pointer
   * \return Else returns nullptr
   */
  const TypedefType* asTypedefType() const;

  /*!
   * \copydoc ::TypeItf::asTypedefType() const
   */
  TypedefType* asTypedefType();

  /*!
   * \brief Returns whether a ::TypeItf has a ::TypedefType in its hierarchy.
   *
   * When having code such as
   * \code{.c}
   *
   * typedef unsigned u_int;
   *
   * void foo(const u_int*);
   * \endcode
   * this function can be used to determine that the top ::ConstQualifiedType has a typedef in its hierarchy
   *
   * \return if the ::TypeItf has a ::TypedefType in its hierarchy. False instead.
   */
  bool containsTypeDef() const;

  /*!
   * \brief Returns if the type is anonymous.
   *
   * An anonymous type is a type which doesn't have a name or any typedef name
   *
   * e.g. in the following code
   * \code{.c}
   * struct word
   * {
   *    //This union is an anonymous union
   *    union
   *    {
   *        uint32_t data;
   *        //This union is an anonymous struct
   *        struct
   *        {
   *            uint8_t byte0;
   *            uint8_t byte1;
   *            uint8_t byte2;
   *            uint8_t byte3;
   *        } f;
   *    };
   * };
   * \endcode
   * the inner union is anonymous.
   *
   * The above C code can be represented using the following C++ code
   * \code{.cpp}
   * bool isEmbeddedStruct = true;
   *
   * StructType* top = new StructType("word", !isEmbeddedStruct); //NOT EMBEDDED
   *
   * //Create the anonymous union
   * UnionType* beingDefined = new UnionType("", isEmbeddedStruct);
   *
   * //Add the data field
   * beingDefined->addField(new ComposableField(new CType(CTYPE_UINT, "uint32_t"), "data"));
   *
   * //Create the anonymous struct and add the fields in it
   * StructType* fStruct = new StructType("", isEmbeddedStruct);
   * fStruct->addField(new ComposableField(new CType(CTYPE_UCHAR, "uint8_t"), "byte0"));
   * fStruct->addField(new ComposableField(new CType(CTYPE_UCHAR, "uint8_t"), "byte1"));
   * fStruct->addField(new ComposableField(new CType(CTYPE_UCHAR, "uint8_t"), "byte2"));
   * fStruct->addField(new ComposableField(new CType(CTYPE_UCHAR, "uint8_t"), "byte3"));
   *
   * //Add the anonymous struct into the union as field f
   * beingDefined->addField(new ComposableField(fStruct, "f"));
   *
   * //Add the anonymous union into the struct word as an unnamed field
   * top->addField(new ComposableField(beingDefined, ""));
   *
   * //The following asserts will not fail
   * assert(top->isAnonymous() == false);
   * assert(beingDefined->isAnonymous() == true);
   * assert(fStruct->isAnonymous() == true);
   * \endcode
   *
   * \return True if the type is anonymous
   * \return False instead.
   */
  bool isAnonymous() const;

  /*!
   * \brief Returns if the type is composable (i.e. struct or union).
   *
   * When this function return true, a pointer or reference holding this type
   * can be safely downcasted to a ::ComposableType instance.
   *
   * \return True if the type is composable
   * \return False instead.
   */
  bool isComposableType() const;

  /*!
   * \brief Cast a ::TypeItf pointer to a ::ComposableType pointer.
   *
   * \return If this is a pointer to ::ComposableType, returns the casted pointer
   * \return Else returns nullptr
   */
  const ComposableType* asComposableType() const;

  /*!
   * \copydoc ::TypeItf::asComposableType() const
   */
  ComposableType* asComposableType();

  /*!
   * \brief Returns if the type is a Pointer.
   *
   * When this function return true, a pointer or reference holding this type
   * can be safely downcasted to a ::Pointer instance using ::TypeItf::asPointer only.
   *
   * Use the function ::Pointer::getPointedType() to know the type on which
   * the pointer points
   *
   * \return True if the type is a pointer
   * \return False instead.
   */
  bool isPointer() const;

  /*!
   * \brief Cast a ::TypeItf pointer to a ::Pointer pointer.
   *
   * \warning This function unqualifies the pointer under the hood.
   *
   * \return If this is a pointer to ::Pointer, returns the casted pointed
   * \return Else returns nullptr
   */
  const Pointer* asPointer() const;

  /*!
   * \copydoc ::TypeItf::asPointer() const
   */
  Pointer* asPointer();

  /*!
   * \brief Returns if the type is a Reference.
   *
   * When this function return true, a pointer or reference holding this type
   * can be safely downcasted to a ::Reference instance using ::TypeItf::asReference only.
   *
   * Use the function ::Pointer::getPointedType() to know the type on which
   * the reference points
   *
   * \return True if the type is a reference
   * \return False instead.
   */
  bool isReference() const;

  /*!
   * \brief Cast a ::TypeItf pointer to a ::Reference pointer.
   *
   * \warning This function unqualifies the reference under the hood.
   *
   * \return If this is a pointer to ::Reference, returns the casted pointed
   * \return Else returns nullptr
   */
  const Reference* asReference() const;

  /*!
   * \copydoc ::TypeItf::asReference() const
   */
  Reference* asReference();

  /*!
   * \brief Returns if the type is a function.
   *
   * When this function returns true, a pointer or reference holding this
   * type can safely downcasted to a ::FunctionType instance.
   *
   * A function type is all the time used in combination with a Pointer
   * object to represent a pointer to a function.
   *
   * \return True if the type is a function.
   * \return False instead.
   */
  bool isFunctionType() const;

  /*!
   * \brief Cast a ::TypeItf pointer to a ::FunctionType pointer.
   *
   * \return If this is a pointer to ::FunctionType, returns the casted pointer
   * \return Else returns nullptr
   */
  const FunctionType* asFunctionType() const;

  /*!
   * \copydoc ::TypeItf::asFunctionType() const
   */
  FunctionType* asFunctionType();

  /*!
   * \brief Returns if the type is an enum.
   *
   * When this function returns true, a pointer or reference holding this
   * type can safely downcasted to an ::Enum instance.
   *
   * \return True if the type is an enum.
   * \return False instead.
   */
  bool isEnum() const;

  /*!
   * \brief Cast a ::TypeItf pointer to a ::Enum pointer.
   *
   * \return If this is a pointer to ::Enum, returns the casted pointer
   * \return Else returns nullptr
   */
  const Enum* asEnum() const;

  /*!
   * \copydoc ::TypeItf::asEnum() const
   */
  Enum* asEnum();

  /*!
   * \brief Returns if the type is an incomplete type.
   *
   * When this function returns true, a pointer or reference holding this
   * type can safely downcasted to an ::IncompleteType instance.
   *
   * \return True if the type is an incomplete type.
   * \return False instead.
   */
  bool isIncompleteType() const;

  /*!
   * \brief Cast a ::TypeItf pointer to a ::IncompleteType pointer.
   *
   * \return If this is a pointer to ::IncompleteType, returns the casted pointer
   * \return Else returns nullptr
   */
  const IncompleteType* asIncompleteType() const;

  /*!
   * \copydoc ::TypeItf::asIncompleteType() const
   */
  IncompleteType* asIncompleteType();

  /*!
   * \brief Returns if the type was declare using the \c const keyword.
   *
   * An example of const variable is
   * \code{.c}
   * const unsigned int FOO = 42;
   * \endcode
   *
   * \return True if the type is constant
   * \return False instead.
   */

  bool isConst() const;

  /*!
   * \brief Returns if the type is implicitly defined.
   *
   * An example of an implicitly defined type is va_args type from stdarg.h.
   * It is actually defined by the compiler.
   *
   * \return True indicates whether the declaration was implicitly generated by the implementation.
   * \return False indicates that this declaration was written explicitly in the source code.
   *
   */
  bool isImplicit() const;


  /*!
   * \brief Returns if the type has a qualifier.
   *
   * A qualifier can be const or volatile.
   *
   * \return True if the type is qualified
   * \return False instead.
   */
  bool isQualified() const;

  /*!
   * \brief Cast a ::TypeItf pointer to a ::QualifiedType pointer.
   *
   * \return If this is a pointer to ::QualifiedType, returns the casted pointer
   * \return Else returns nullptr
   */
  const QualifiedType* asQualifiedType() const;

  /*!
   * \copydoc ::TypeItf::asQualifiedType() const
   */
  QualifiedType* asQualifiedType();

  /*!
   * \brief Set the type to be implicit.
   *
   * Implicit types are types that are defined by the compiler such as va_args.
   */
  TypeItf* setImplicit(bool value);

  /*!
   * \brief Remove the qualifier of the type if any.
   *
   * \sa ::TypeItf::isQualified.
   *
   * \return A pointer to the unqualified type if any
   * \return The pointer to this instead.
   */
  const TypeItf* unqualify() const;

  /*!
   * \copydoc ::TypeItf::unqualify() const
   */
  TypeItf* unqualify();

  /*!
   * \copydoc ::EasyMock::Hashable::getHash()
   */
  std::size_t getHash() const noexcept override;

  /*!
   * \copydoc ::EasyMock::Hashable::cacheHash()
   */
  void cacheHash() noexcept override;

  /*!
   * \brief Return the namespace in which the type belong to
   */
  [[nodiscard]]
  std::shared_ptr<const Namespace> getNamespace() const noexcept;

  /*!
   * \brief Returns the hash of the type where all typedefs have been removed.
   *
   * For example:
   *
   * \code{.cpp}
   *
   * CType ctype{CTYPE_INT};
   * TypeDefType typeDefType{std::make_shared<CType>(CTYPE_INT)};
   *
   * assert(ctype.getHash() != typeDefType.getHash());
   * assert(ctype.getRawHash() == typeDefType.getRawHash());
   * \endcode
   *
   * both version have the same raw hash while the ::TypeItf::getHash() returns different values
   */
  virtual std::size_t getRawHash() const noexcept;

  /*!
   * \brief Checks if 2 TypeItf instances are equal.
   *
   * In order to support the comparison of 2 objects that inherits from TypeItf
   * stored into TypeItf pointers, this function calls the ::TypeItf::isEqual() virtual protected
   * method. This allows the comparison of 2 objects hold in TypeItf pointers to be
   * compared because each class inheriting from TypeItf can reimplement this function.
   *
   * \see ::TypeItf::isEqual()
   */
  bool operator==(const TypeItf &p_other) const;
  bool operator!=(const TypeItf &p_other) const;


  /*!
   * \brief Deletes the object and free all the allocated memory it holds if any.
   *
   * I.E. it calls the delete operator on all the non-static pointer members
   */
  virtual ~TypeItf() = default;

#define TYPEITF_COMMON_CLASS_MEMBERS(prefix) \
  std::string prefix ## name; \
  bool prefix ## isCType; \
  bool prefix ## isStruct; \
  bool prefix ## isUnion; \
  bool prefix ## isPointer; \
  bool prefix ## isReference; \
  bool prefix ## isFunctionType; \
  bool prefix ## isEnum; \
  bool prefix ## isImplicit; \
  bool prefix ## isIncompleteType; \
  bool prefix ## isTypedefType; \
  bool prefix ## isQualifiedType; \
  std::shared_ptr<const Namespace> prefix ## type_namespace;
protected:
  TypeItf();
  explicit TypeItf(std::string p_name);
  TypeItf(std::string p_name, std::shared_ptr<const Namespace> p_type_namespace);

  TYPEITF_COMMON_CLASS_MEMBERS(m_)

  /*!
   * \brief Specify that the type is a C structure.
   *
   * It is called by ::StructType objects
   */
  void setStruct(bool value);

  //void setClass(bool value);

  /*!
   * \brief Specify that the type is a C union.
   *
   * It is called by ::UnionType objects
   */
  void setUnion(bool value);

  /*!
   * \brief Specify that the type is a C type.
   *
   * It is called by ::CType objects
   */
  void setCType(bool value);

  /*!
   * \brief Specify that the type is a pointer.
   *
   * It is called by ::Pointer objects
   */
  void setPointer(bool value);

  /*!
   * \brief Specify that the type is a reference.
   *
   * It is called by ::Reference objects
   */
  void setReference(bool value);

  /*!
   * \brief Specify that the type is a function.
   *
   * It is called by ::FunctionType objects
   */
  void setFunction(bool value);

  /*!
   * \brief Specify that the type is an enum.
   *
   * It is called by ::Enum objects
   */
  void setEnum(bool value);

  /*!
   * \brief Specify that the type is an incomplete type.
   *
   * It is called by ::IncompleteType objects
   */
  void setIncompleteType(bool value);

  /*!
   * \brief Specify that the type is a typedef.
   *
   * It is called by ::TypedefType objects
   */
  void setTypedefType(bool value);

  /*!
   * \brief Specify that the type is qualified.
   *
   * It is called by ::QualifiedType objects
   *
   * \sa ::TypeItf::isQualified
   */
  void setQualifiedType(bool value);

  /*!
   * \brief Returns if this instance is equal to another.
   *
   * \param p_other A reference to the other object to be compared with
   *
   * For the objects having pointers members, the pointer is dereferenced
   * and the operator==() function is called.
   *
   * This function is not intended to be called directly by the users of the class
   * and is called from the operator==() function.
   *
   * This function is virtual and is meant to be overwritten by the subclass.
   * Thanks to that, the following example code calls the ::TypeItf::isEqual implementation of the ::CType class.
   * \code{.cpp}
   * TypeItf *t1 = new CType(CTYPE_INT);
   * TypeItf *t2 = new CType(CTYPE_INT);
   *
   * assert(*t1 == *t2); //will not fail;
   * \endcode
   *
   * When a subclass implements this method, it is very important to make sure that
   * the function makes sure that the <tt>other</tt> parameter have the same type.
   * This can typically be achieve by calling the ::TypeItf::isEqual function.
   * \code{.cpp}
   * bool isEqual(const TypeItf &p_other) const
   * {
   *    bool parentEq = TypeItf::isEqual(p_other);
   *    if(!parentEq)
   *    {
   *        return false;
   *    }
   *    //Do further checks
   * }
   * \endcode
   *
   * \return True if the objects are equal.
   * \return False if the objects are not equal
   */
  virtual bool isEqual(const TypeItf &p_other) const;

private:

  typedef struct
  {
    TYPEITF_COMMON_CLASS_MEMBERS()
  } attributes;
  TypeItf(attributes attrib);

  std::size_t m_cachedHash;

#undef TYPEITF_COMMON_CLASS_MEMBERS
};

#endif /* TYPEITF_H */
