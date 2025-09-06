/*! \file
 *
 * \brief Contains the class to represent any types which are composed by
 * other types such as struct and union.
 */
#ifndef COMPOSABLETYPE_H
#define COMPOSABLETYPE_H

#include <vector>
#include <variant>
#include <memory>

#include "TypeItf.h"
#include "ComposableField.h"
#include "ComposableBitfield.h"

class FunctionDeclaration;
struct Namespace;

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
  using ComposableFieldType = std::variant<ComposableField, ComposableBitfield>;
  using ComposableFieldTypeVector = std::vector<ComposableFieldType>;
  using ComposableMethodType = std::shared_ptr<const FunctionDeclaration>;
  using ComposableMethodVector = std::vector<ComposableMethodType>;
  /*!
   * \brief Returns the fields contained by the type
   *
   * \return A ::ComposableType::ComposableFieldTypeVector containing the fields contained by the type
   */
  ComposableFieldTypeVector& getContainedFields();

  /*!
   * \copydoc ::ComposableType::getContainedFields()
   */
  const ComposableFieldTypeVector& getContainedFields() const;

  /*!
   * \brief Add a new field to the composable type.
   *
   * A field is implement by a class inheriting from ::ComposableFieldItf interface.
   */
  void addField(ComposableType::ComposableFieldType newField);

  void addFunction(ComposableType::ComposableMethodType newFunction);

  const ComposableMethodVector& getFunctions() const;

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
  std::size_t getHash() const noexcept override;

  /*!
   * \copydoc ::EasyMock::Hashable::cacheHash()
   */
  void cacheHash() noexcept override;

  /*!
   * \copydoc ::TypeItf::getDeclarationPrefix
   */
  virtual std::string getDeclarationPrefix(bool p_naked = false) const override;

  bool operator==(const TypeItf &other) const;
  bool operator!=(const TypeItf &other) const;

protected:
  ComposableType(std::string p_name, bool p_is_embedded_in_other_type);
  ComposableType(std::string p_name, ComposableFieldTypeVector p_elem, bool p_is_embedded_in_other_type);
  ComposableType(std::string p_name, ComposableFieldTypeVector p_elem, bool p_is_embedded_in_other_type, std::shared_ptr<const Namespace> p_namespace);

  ComposableType(const ComposableType& other) = delete;
  ComposableType& operator=(const ComposableType& other) = delete;
  ComposableType(ComposableType &&other) = default;
  ComposableType& operator=(ComposableType &&other) = default;
  /*!
   * \copydoc ::TypeItf::isEqual
   */
  bool isEqual(const TypeItf& p_other) const override;
  virtual ~ComposableType() = 0; //pure virtual. ComposableType shouldn't be instantiable

private:
  ComposableFieldTypeVector m_elem;
  bool m_is_declaration_embedded_in_other_type;
  bool m_is_forward_declared;
  std::size_t m_cachedHash;
  ComposableMethodVector m_functions;
};

namespace boost
{
  std::size_t hash_value(const ComposableType&);
}

#endif /* COMPOSABLETYPE_H */
