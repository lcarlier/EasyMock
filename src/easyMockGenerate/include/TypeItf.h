/*! \file
 *
 * \brief Contains the base class of most of the [EasyMock internal objects](md_docs_architecture.html#user-content-eio).
 */
#ifndef TYPEITF_H
#define TYPEITF_H

#include <string>
#include "AutoCleanVectorPtr.h"
#include "ComposableField.h"

/*!
 * \brief Base class of all types related classes
 */
class TypeItf
{
public:
  typedef AutoCleanVectorPtr<TypeItf> Vector;

  TypeItf(const TypeItf &other) = default;
  TypeItf& operator=(const TypeItf &other) = default;
  TypeItf(TypeItf &&other) = default;
  TypeItf& operator=(TypeItf &&other) = default;

  /*!
   * \return The basic C type (e.g. int, char) or the tag of a struct of an union
   */
  const std::string &getName() const;

  /*!
   * \return The typedef string
   * If there is not typedef aliasing this type, this string is empty
   */
  const std::string &getTypedDefName() const;

  /*!
   * \return If typedef is set, returns it, otherwise returns the name
   */
  const std::string &getMostDefinedName() const;

  /*!
   * \return The string that should be used to declare a variable of the type
   */
  std::string getFullDeclarationName() const;

  /*!
   * \return The same as getFullDeclarationName but without the const qualifier
   */
  std::string getFullNonQualifiedDeclarationName() const;

  /*!
   * \brief Returns the C type this type defines
   * \warning The value returned is only valid if TypeItf::isCType() returns true
   * \return If this type is a C type, the actual type
   * \return If this is not a C type, returns easyMock_cTypes_t::CTYPE_INVALID
   */
  virtual easyMock_cTypes_t getCType() const;

  /*!
   * \brief Returns the fields contained by the type
   * \warning If this function is called when TypeItf::isComposableType() returns false,
   * the function will abort the execution of the program with an assert.
   * \warning If isComposableType() is false, an assert will be generated
   * \return A ComposableField::Vector containing the fields contained by the type
   */
  virtual ComposableField::Vector& getContainedFields();

  /*! \copydoc getContainedFields() */
  virtual const ComposableField::Vector& getContainedFields() const;

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
   * can be safely down casted to a ComposableType instance of a StructType instance.
   *
   * The fields definition can be access via the ComposableType::getContainedFields() function.
   *
   * \return True if the type is a struct.
   * \return False instead.
   */
  bool isStruct() const;

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
   * can be safely down casted to a ComposableType instance of a UnionType instance.
   *
   * The fields definition can be access via the ComposableType::getContainedFields() function.
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
   * can be safely down casted to a CType instance.
   *
   * When this function returns true, the function TypeItf::getCType() returns the actual
   * C type this type defines
   *
   * \return True if the type is an union.
   * \return False instead.
   */
  bool isCType() const;

  /*!
   * \brief Returns if the type has a typedef alias.
   *
   * A typedef alias can be set with the TypeItf::setTypedDefName() function
   *
   * When this function returns true, the function TypeItf::getTypedDefName() can
   * be used to retrieve it.
   *
   * When this function returns true, the function TypeItf::getMostDefinedName()
   * returns the same as TypeItf::getTypedDefName()
   *
   * \return True if the type has a typedef alias
   * \return False instead.
   */
  bool isTypedDef() const;

  /*!
   * \brief Returns if the type is anonymous.
   *
   * An anonymous type is a type which doesn't have a name or any alias name
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
   * can be safely down casted to a ComposableType instance.
   *
   * \return True if the type is composable
   * \return False instead.
   */
  bool isComposableType() const;

  /*!
   * \brief Returns if the type is a Pointer.
   *
   * When this function return true, a pointer or reference holding this type
   * can be safely down casted to a Pointer instance.
   *
   * Use the function Pointer::getPointedType() to know the type on which
   * the pointer points
   *
   * \return True if the type is a pointer
   * \return False instead.
   */
  bool isPointer() const;

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
   * \brief Set the type to be const.
   *
   * \warning When the type is a Pointer, make sure to use this function with care as the way
   * to declare constant pointed value is by using this function the the type
   * returned by Pointer::getPointedType().
   *
   * \sa isConst()
   */
  TypeItf* setConst(bool value);

  /*!
   * \brief Set the type to be implicit.
   *
   * Implicit types are types that are defined by the compiler such as va_args.
   */
  TypeItf* setImplicit(bool value);

  /*!
   * \brief Checks if 2 TypeItf instances are equal.
   *
   * In order to support the comparison of 2 objects that inherits from TypeItf
   * stored into TypeItf pointers, this function calls the isEqual() virtual protected
   * method. This allows the comparison of 2 objects hold in TypeItf pointers to be
   * compared because each class inheriting from TypeItf can reimplement this function.
   *
   * \see isEqual()
   */
  bool operator==(const TypeItf &other) const;
  bool operator!=(const TypeItf &other) const;

  /*!
   * \brief Creates a deep clone of the object.
   *
   * The returned pointer needs to be freed manually with the delete operator or
   * passed to another class (such as Pointer) that will delete it when that
   * other class is deleted.
   */
  virtual TypeItf* clone() const = 0;

  /*!
   * \brief Deletes the object and free all the allocated memory it holds if any.
   *
   * I.E. it calls the delete operator on all the non-static pointer members
   */
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
  TypeItf();
  explicit TypeItf(const std::string p_name);
  TypeItf(const std::string p_name, const std::string p_typed_def_name);

  /*!
   * \brief Specify that the type is a C structure.
   *
   * It is called by StructType objects
   */
  void setStruct(bool value);

  /*!
   * \brief Specify that the type is a C union.
   *
   * It is called by UnionType objects
   */
  void setUnion(bool value);

  /*!
   * \brief Specify that the type is a C type.
   *
   * It is called by CType objects
   */
  void setCType(bool value);

  /*!
   * \brief Specify that the type is a pointer.
   *
   * It is called by Pointer objects
   */
  void setPointer(bool value);

  /*!
   * \brief Function called by the subclasses to set the type name.
   *
   * For C type, it is the string to be used to declare a variable of that C type (e.g. <tt>unsigned int</tt>).
   *
   * For C union and C struct, it is the name of the struct. Not the typedef alias.
   *
   * Pointer object does not call this function because a pointer doesn't have a name, so the type name remains empty.
   */
  void setName(std::string p_name);

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
   * Thanks to that, the following example code calls the isEqual implementation of the CType class.
   * \code{.cpp}
   * TypeItf *t1 = new CType(CTYPE_INT);
   * TypeItf *t2 = new CType(CTYPE_INT);
   *
   * assert(*t1 == *t2); //will not fail;
   * \endcode
   *
   * When a subclass implements this method, it is very important to make sure that
   * the function makes sure that the <tt>other</tt> parameter have the same type.
   * This can typically be achieve by calling the TypeItf::isEqual function.
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

  /*!
   * \brief Set the typedef alias
   */
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

