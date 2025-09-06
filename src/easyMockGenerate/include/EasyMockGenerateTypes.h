/*! \file
 * \brief Contains some helper enum and variable for the CType class.
 */
#ifndef EASYMOCKGENERATETYPES_H
#define EASYMOCKGENERATETYPES_H

/*!
 * \brief enum listing all the possible C Type
 */
typedef enum
{
  /*!
   * \brief @c char type
   */
  CTYPE_CHAR,
  /*!
   * \brief <tt> unsigned char </tt> type
   */
  CTYPE_UCHAR,
  /*!
   * \brief <tt> signed char </tt> type
   */
  CTYPE_SCHAR,
  /*!
   * \brief @c short type
   */
  CTYPE_SHORT,
  /*!
   * \brief <tt> unsigned short </tt> type
   */
  CTYPE_USHORT,
  /*!
   * \brief @c int type
   */
  CTYPE_INT,
  /*!
   * \brief <tt> unsigned int </tt> type
   */
  CTYPE_UINT,
  /*!
   * \brief @c long type
   */
  CTYPE_LONG,
  /*!
   * \brief <tt> unsigned long </tt> type
   */
  CTYPE_ULONG,
  /*!
   * \brief <tt> long long </tt> type
   */
  CTYPE_LONG_LONG,
  /*!
   * \brief <tt> unsigned long long </tt> type
   */
  CTYPE_ULONG_LONG,
  /*!
   * \brief @c float type
   */
  CTYPE_FLOAT,
  /*!
   * \brief @c double type
   */
  CTYPE_DOUBLE,
  /*!
   * \brief <tt> long double </tt> type
   */
  CTYPE_LONG_DOUBLE,
  /*!
   * \brief <tt> __int128 </tt> type
   */
  CTYPE_INT128,
  /*!
   * \brief <tt> unsigned __int128 </tt> type
   */
  CTYPE_UINT128,
  /*!
   * \brief @c void type
   */
  CTYPE_VOID,
  /*!
   * \brief An invalid C type
   */
  CTYPE_BOOL,
  CTYPE_INVALID
} easyMock_cTypes_t;

/*!
 * Array to be indexed with the values of ::easyMock_cTypes_t.
 *
 * The element contains the string which can be used to declare a variable of the
 * type given as index.
 *
 * E.g: <tt>easyMock_arrayCTypeStr[CTYPE_UINT]</tt> returns <tt>"unsigned int"</tt>
 */
extern const char *easyMock_arrayCTypeStr[];

/*!
 * Array to be indexed with the values of ::easyMock_cTypes_t.
 *
 * The element contains the string which can be used to print a variable of the
 * type given as index into a printf format string without the %.
 *
 * E.g: <tt>easyMock_arrayCTypeStr[CTYPE_FLOAT]</tt> returns <tt>"f"</tt>
 */
extern const char *easyMock_printfFormat[];

#endif /* EASYMOCKGENERATETYPES_H */

