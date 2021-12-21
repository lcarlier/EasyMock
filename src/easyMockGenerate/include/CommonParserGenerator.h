/*! \file
 *
 * \brief Contains common types in between the parser and the generator.
 */
#ifndef EASYMOCK_COMMONPARSERGENERATOR_H
#define EASYMOCK_COMMONPARSERGENERATOR_H

#include <unordered_set>
#include <string>

/*!
 * \brief Type holding the list of functions to mock.
 */
using MockOnlyList = std::unordered_set<std::string>;
/*!
 * \brief Type holding the list type to ignore fields generation.
 */
using IgnoreTypeFieldList = std::unordered_set<std::string>;
/*!
 * \brief Type holding the list type to ignore fields generation.
 */
using IgnoreFunList = std::unordered_set<std::string>;

#endif //EASYMOCK_COMMONPARSERGENERATOR_H
