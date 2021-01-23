/*! \file
 * \brief Contains the class to represent an enum
 */
#ifndef ENUM_H
#define ENUM_H

#include <TypeItf.h>

#include <string>

/*!
 * \brief This class represents any of the C basic types
 *
 * Only the enum name is stored in this class. The different enum
 * values are not stored in this class because they are not useful
 * for mock generation
 */
class Enum  : public TypeItf
{
public:
  /*!
   * \brief Creates an enum
   *
   * \param p_name The enum name
   */
  Enum(const std::string p_name);

  /*!
   * \copydoc Enum(std::string)
   *
   * \param p_typed_def_name The enum typedef alias
   */
  Enum(const std::string p_name, const std::string p_typed_def_name);

  /*!
   * \copydoc TypeItf::clone
   */
  Enum *clone() const override;

  virtual ~Enum();
private:

};

#endif /* ENUM_H */

