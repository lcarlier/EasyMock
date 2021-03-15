/*! \file
 *
 * \brief Contains the interface which is used to implement a field of
 * ::ComposableType types (i.e. struct and union).
 * It is subclassed by ::ComposableField and ::ComposableBitfield
 */
#ifndef COMPOSABLEFIELDITF_H
#define COMPOSABLEFIELDITF_H

#include "Declarator.h"

#include <AutoCleanVectorPtr.h>

#include <string>

class TypeItf;

/*!
 * \brief The interface for a field to be added to a ::ComposableType
 *
 * It is a pure virtual class. Subclasser must implement
 * ::ComposableFieldItf::clone
 */
class ComposableFieldItf : public Declarator
{
public:
  /*!
   * \brief A ::AutoCleanVectorPtr containing classes inheriting from ::ComposableFieldItf.
   *
   * \heapPointer
   */
  typedef AutoCleanVectorPtr<ComposableFieldItf> Vector;

  /*!
   * \brief Forwards the call to the ::Declarator class constructor
   */
  ComposableFieldItf(TypeItf* p_type, std::string& p_name);

  ComposableFieldItf(const ComposableFieldItf &other) = default;
  ComposableFieldItf& operator=(const ComposableFieldItf &other) = default;

  ComposableFieldItf(ComposableFieldItf &&other) = default;
  //No move assignment operator when using copy and swap idiom

  /*!
   * \brief Returns whether the subclasser is a ::ComposableField object
   */
  virtual bool isComposableField() const;

  /*!
   * \brief Returns whether the subclasser is a ::ComposableBitfield object
   */
  virtual bool isComposableBitfield() const;

  /*!
   * \brief Returns if the field is anonymous.
   *
   * A field is said to be anonymous whenever it has no name.
   *
   * For instance in the following code
   * \code{.c}
   * union u
   * {
   *   uint32_t val;
   *   struct
   *   {
   *     uint8_t b1;
   *     uint8_t b2;
   *     uint8_t b3;
   *     uint8_t b4;
   *   };
   * };
   * \endcode
   * the anonymously typed struct is an anonymous field of union u
   */
  bool isAnonymous() const;

  /*!
   * \brief Returns the name of the field.
   *
   * The string returned is empty if the field is anonymous.
   * \see ::ComposableFieldItf::isAnonymous()
   */
  const std::string& getName() const;

  virtual bool isEqual(const Declarator& p_other) const override;

  /*!
   * \copydoc ::TypeItf::clone
   */
  virtual ComposableFieldItf* clone() const override = 0;

  /*!
   * \copydoc ::EasyMock::Hashable::getHash()
   */
  std::size_t getHash() const override;

  virtual ~ComposableFieldItf() {}
private:
  std::string m_name;
};

#endif /* COMPOSABLEFIELDITF_H */
