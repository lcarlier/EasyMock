/*! \file
 *
 * \brief Contains the class to represent any types which are composed by
 * other types such as struct and union.
 */
#ifndef COMPOSABLETYPE_H
#define COMPOSABLETYPE_H

#include "TypeItf.h"

/*!
 * This class is used to represent any types which are composed by other types such as
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
  ComposableField::Vector& getContainedFields() override;

  /*!
   * \copydoc TypeItf::getContainedFields()
   */
  const ComposableField::Vector& getContainedFields() const override;

  /*!
   * \brief Add a new field to the composable type.
   *
   * A field is implement by the ComposableField class.
   *
   * \heapPointer
   */
  void addField(ComposableField *newField);

  /*!
   * \return A string which uniquely identify the type. This can be based on
   * name or typedef name (if they are not empty) or for anonymous type
   * based on internal logic to generate the name.
   */
  const std::string getUniqueName() const;

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

  bool operator==(const ComposableType &other) const;
  bool operator!=(const ComposableType &other) const;

  /*!
   * \brief Initialise a hash used for the type when the type is anonymous.
   *
   * The tool is foreseen to generate only 1 header file, no more.
   * A hash of the path of the file to be mocked can be used as parameter to this function.
   */
  static void setFileHash(std::size_t hash);

protected:
  ComposableType(const std::string p_name, bool p_is_embedded_in_other_type);
  ComposableType(const std::string p_name, const std::string p_type_def_name, bool p_is_embedded_in_other_type);
  ComposableType(const std::string p_name, const ComposableField::Vector p_elem, bool p_is_embedded_in_other_type);
  ComposableType(const std::string p_name, const std::string p_type_def_name, const ComposableField::Vector p_elem, bool p_is_embedded_in_other_type);

  /*
   * There is no pointer to move so I decided not to use the
   * copy-and-swap idiom
   */
  ComposableType(const ComposableType& other);
  ComposableType& operator=(const ComposableType& other);
  ComposableType(ComposableType &&other);
  //No move operator otherwise the object is not movable anymore (UT fails)

  bool isEqual(const TypeItf& other) const override;
  virtual ~ComposableType() = 0; //pure virtual. ComposableType shouldn't be instantiable

private:
  /* Don't make it constant otherwise the object is not copyable anymore */
  ComposableField::Vector m_elem;
  bool m_is_declaration_embedded_in_other_type;
  int m_anonymous_number;

  void correctIncompleteType(ComposableType *newPtr, const ComposableType* oldPtrToReplace);
  friend void ComposableField::updateIncompleteTypePtr(ComposableType* newPtr, const ComposableType* oldPtrToReplace);

  /*
   * The tool is foreseen to generate only 1 header file, no more.
   * We store into this variable a unique hash of the path of the file
   * to be mocked to be able to generate a unique name for the comparators
   * of anonymous structs and unions
   */
  static size_t m_unique_hash;
  static unsigned int m_number_of_anonymous_composable_type;
};

#endif /* COMPOSABLETYPE_H */

