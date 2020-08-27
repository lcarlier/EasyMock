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
  /*
   * \brief Create an enum
   *
   * \param p_name The enum name
   * \param p_typed_def_name The enum typedef alias
   * \param p_is_const Specifies whether the value of the enum is constant.
   */
  Enum(const std::string p_name, const std::string p_typed_def_name, const bool p_is_const = false);

  /*!
   * \copydoc TypeItf::clone
   */
  Enum *clone() const override;

  virtual ~Enum();
private:

};

#endif /* ENUM_H */

