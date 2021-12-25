/*! \file
 *
 * \brief Contains the interface which is used to implement a field of
 * ::ComposableType types (i.e. struct and union).
 * It is subclassed by ::ComposableField and ::ComposableBitfield
 */
#ifndef COMPOSABLEFIELDITF_H
#define COMPOSABLEFIELDITF_H

#include "Declarator.h"

#include <string>
#include <variant>

class TypeItf;
class ComposableField;
class ComposableBitfield;

/*!
 * \brief The interface for a field to be added to a ::ComposableType
 */
class ComposableFieldItf : public Declarator
{
public:

  /*!
   * \brief Forwards the call to the ::Declarator class constructor
   */
  ComposableFieldItf(std::shared_ptr<TypeItf> p_type, std::string p_name);

  ComposableFieldItf(const ComposableFieldItf &other) = delete;
  ComposableFieldItf& operator=(const ComposableFieldItf &other) = delete;
  ComposableFieldItf(ComposableFieldItf &&other) = default;
  ComposableFieldItf& operator=(ComposableFieldItf &&other) = default;

  /*!
   * \brief Returns whether the subclasser is a ::ComposableField object
   */
  virtual bool isComposableField() const;

  /*!
   * \brief Cast a ::ComposableFieldItf pointer to a ::ComposableField pointer.
   *
   * \return If this is a pointer to ::ComposableField, returns the casted pointer
   * \return Else returns nullptr
   */
  const ComposableField* asComposableField() const;

  /*!
   * \copydoc ::ComposableFieldItf::asComposableField() const
   * @return
   */
  ComposableField* asComposableField();

  /*!
   * \brief Returns whether the subclasser is a ::ComposableBitfield object
   */
  virtual bool isComposableBitfield() const;

  /*!
   * \brief Cast a ::ComposableFieldItf pointer to a ::ComposableBitfield pointer.
   *
   * \return If this is a pointer to ::ComposableBitfield, returns the casted pointer
   * \return Else returns nullptr
   */
  const ComposableBitfield* asComposableBitfield() const;

  /*!
   * \copydoc ::ComposableFieldItf::asComposableBitfield() const
   * @return
   */
  ComposableBitfield* asComposableBitfield();

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
   * \copydoc ::EasyMock::Hashable::getHash()
   */
  std::size_t getHash() const noexcept override;

  /*!
   * \copydoc ::EasyMock::Hashable::cacheHash()
   */
  void cacheHash() noexcept override;

  virtual ~ComposableFieldItf() {}
private:
  std::string m_name;
  std::size_t m_cachedHash;
};

#endif /* COMPOSABLEFIELDITF_H */
