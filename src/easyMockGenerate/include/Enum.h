/*! \file
 * \brief Contains the class to represent an enum
 */
#ifndef ENUM_H
#define ENUM_H

#include <TypeItf.h>

#include <cstdint>
#include <string>
#include <map>

/*!
 * \brief This class represents an enum and the values it contains
 *
 */
class Enum : public TypeItf
{
public:
  Enum(const Enum &other) = delete;
  Enum& operator=(const Enum &other) = delete;
  Enum(Enum &&other) = default;
  Enum& operator=(Enum &&other) = default;

  /*!
   * \brief Type used to store enum values
   */
  using listOfValuesType = std::map<unsigned int, std::string>;

  /*!
   * \brief Creates an enum
   *
   * \param p_name The enum name
   */
  Enum(const std::string p_name);

  /*!
   * \brief Adds a new enum value inside the enum type.
   */
  void addEnumValue(int64_t p_value, const std::string& p_enumStr);

  /*!
   * \brief Returns the list of enum values that the enum type contains.
   */
  const listOfValuesType& getValues() const;

  /*!
   * \copydoc ::TypeItf::getDeclarationPrefix
   */
  virtual std::string getDeclarationPrefix(bool p_naked = false) const override;

  /*!
   * \copydoc ::EasyMock::Hashable::getHash()
   */
  std::size_t getHash() const noexcept override;

  /*!
   * \copydoc ::EasyMock::Hashable::cacheHash()
   */
  void cacheHash() noexcept override;

  virtual ~Enum() = default;
protected:
   /*!
   * \copydoc TypeItf::isEqual
   */
  bool isEqual(const TypeItf& p_other) const override;

private:
  listOfValuesType m_listOfValues;
  std::size_t m_cachedHash;
};

#endif /* ENUM_H */
