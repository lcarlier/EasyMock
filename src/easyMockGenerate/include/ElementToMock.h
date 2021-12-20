/*! \file
 * \brief Contains the interface that an ElementToMock proposes.
 */
#ifndef ELEMENTTOMOCK_H
#define ELEMENTTOMOCK_H

#include "Parameter.h"
#include "ReturnValue.h"

#include "EasyMock_Hashable.h"

/*!
 * \brief Types of supported mock
 */
enum ElementToMock_Type
{
  /*!
   * The mocked element is a function
   */
  ETS_function
};

/*!
 * \brief Interface of an ElementToMock.
 *
 * Currently only C function are supported but it is the purpose
 * to add more. I.e. C++ classes.
 */
class ElementToMock : virtual public EasyMock::Hashable
{
public:
  /*!
   * \brief Returns the mock type
   *
   * See ::ElementToMock_Type enum to see which types is supported
   */
  virtual ElementToMock_Type getMockType() const = 0;

  /*!
   * \copydoc ::EasyMock::Hashable::getHash()
   */
  virtual size_t getHash() const noexcept override;

  virtual ~ElementToMock();
};

#endif /* ELEMENTTOMOCK_H */
