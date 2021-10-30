/*! \file
 *
 * \brief Contains the class to represent any types which are composed by
 * other types such as struct and union.
 */
#ifndef COMPOSABLETYPE_H
#define COMPOSABLETYPE_H

#include "TypeItf.h"

/*!
 * \brief Represents any types which are composed by other types such as
 * struct and union.
 *
 * A new field can be added using the addField() function.
 *
 * This class is pure virtual and serve as a common interface to the StructType and UnionType classes.
 */
class ComposableType : public TypeItf
{
public:
  /*!
   * \copydoc TypeItf::getContainedFields()
   */
  ComposableFieldItf::Vector& getContainedFields() override;

  /*!
   * \copydoc ::TypeItf::getContainedFields()
   */
  const ComposableFieldItf::Vector& getContainedFields() const override;

  /*!
   * \brief Add a new field to the composable type.
   *
   * A field is implement by a class inheriting from ::ComposableFieldItf interface.
   *
   * \heapPointer
   */
  void addField(ComposableFieldItf *newField);

  /*!
   * \return true if the type declaration is embedded in another type.
   * \return false if the type declaration is not embedded in another type.
   *
   * For example, in the following code
   * \code{.c}
   * struct topEmbedded
   * {
   *   struct embeddedStruct
   *   {
   *     int a;
   *   } b;
   * };
   * \endcode
   * the declaration of the type <tt>struct embeddedStruct</tt> is embedded.
   *
   * The above C code can be represented by the following C++ code
   * \code{.cpp}
   * bool isEmbeddedStruct = true;
   * StructType* top = new StructType("topEmbedded", !isEmbeddedStruct); //NOT EMBEDDED
   * StructType* beingDefined = new StructType("embeddedStruct", isEmbeddedStruct);
   * beingDefined->addField(new ComposableField(CTYPE_INT, "a"));
   * top->addField(new ComposableField(beingDefined, "b"));
   *
   * //The following asserts will not fail
   * assert(top->isDeclarationEmbeddedInOtherType() == false);
   * assert(beingDefined->isDeclarationEmbeddedInOtherType() == true);
   * \endcode
   */
  bool isDeclarationEmbeddedInOtherType() const;

  /*!
   * \brief Returns whether the type corresponds to a forward declared type or not.
   *
   * \return True if the type corresponds to a forward declared type.
   *         False instead
   */
  bool isForwardDeclared() const;

  /*!
   * \brief Sets whether the composable type is forward declared or not.
   *
   * \param p_value True to set the composable type as forward declared. False instead.
   */
  void setForwardDecl(bool p_value);

  /*!
   * \brief Returns the keyword to declare the composable type.
   *
   * i.e. return "struct" for struct and "union" for union
   */
  virtual const char* getComposableTypeKeyword() const = 0;

  /*!
   * \copydoc ::EasyMock::Hashable::getHash()
   */
  std::size_t getHash() const override;

  /*!
   * \copydoc ::TypeItf::getDeclarationPrefix
   */
  virtual std::string getDeclarationPrefix(bool p_naked = false) const override;

  bool operator==(const TypeItf &other) const;
  bool operator!=(const TypeItf &other) const;

protected:
  ComposableType(const std::string p_name, bool p_is_embedded_in_other_type);
  ComposableType(const std::string p_name, const ComposableFieldItf::Vector p_elem, bool p_is_embedded_in_other_type);

  /*
   * There is no pointer to move so I decided not to use the
   * copy-and-swap idiom
   */
  ComposableType(const ComposableType& other);
  ComposableType& operator=(const ComposableType& other);
  ComposableType(ComposableType &&other);
  //No move operator otherwise the object is not movable anymore (UT fails)

  /*!
   * \copydoc ::TypeItf::isEqual
   */
  bool isEqual(const TypeItf& p_other) const override;
  virtual ~ComposableType() = 0; //pure virtual. ComposableType shouldn't be instantiable

private:
  ComposableFieldItf::Vector m_elem;
  bool m_is_declaration_embedded_in_other_type;
  bool m_is_forward_declared;
};

#endif /* COMPOSABLETYPE_H */
