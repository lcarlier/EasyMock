/*! \file
 *
 * \brief Contains the implemention of ::ComposableBitfield which implements
 * the representation of a C bitfield.
 */
#ifndef COMPOSABLEBITFIELD_H
#define COMPOSABLEBITFIELD_H

#include "ComposableFieldItf.h"
#include "EasyMockGenerateTypes.h"

#include <cstdint>

class CType;
class TypedefType;

/*!
 * \brief Class representing a bitfield in C
 */
class ComposableBitfield : public ComposableFieldItf
{
public:
  /*!
   * \brief Create a C bitfield
   *
   * \param p_type The type of the bitfield.
   * \param p_name The name of the bitfield. If it is empty, the bitfield is anonymous.
   * \param p_size The number of bits that the field has.
   */
  ComposableBitfield(std::shared_ptr<TypeItf> p_type, std::string p_name, uint8_t p_size);

  /*!
   * \copydoc ::ComposableBitfield::ComposableBitfield(std::shared_ptr<TypeItf>, std::string, uint8_t)
   */
  ComposableBitfield(easyMock_cTypes_t p_type, std::string p_name, uint8_t p_size);

  ComposableBitfield(const ComposableBitfield &other) = delete;
  ComposableBitfield &operator=(const ComposableBitfield& other) = delete;
  ComposableBitfield(ComposableBitfield &&other) = default;
  ComposableBitfield& operator=(ComposableBitfield &&other) = default;

  /*!
   * \brief Compares 2 ComposableBitfield objects.
   *
   * \copydetails ::Declarator::operator==()
   */
  bool operator==(const ComposableBitfield &other) const;
  bool operator!=(const ComposableBitfield &other) const;

  /*!
   * \copydoc ::ComposableFieldItf::isComposableBitfield() const
   */
  bool isComposableBitfield() const override;

  /*!
   * \brief Get the number of bit that the bitfield has.
   */
  uint8_t getSize() const;

  /*!
   * \copydoc ::EasyMock::Hashable::getHash()
   */
  std::size_t getHash() const noexcept override;

  virtual ~ComposableBitfield() override;
private:
  /*!
   * \copydoc ::Declarator::isEqual
   */
  bool isEqual(const Declarator& p_other) const override;

  uint8_t m_size;

  friend void swap(ComposableBitfield &first, ComposableBitfield &second);
};

#endif /* COMPOSABLEBITFIELD_H */
