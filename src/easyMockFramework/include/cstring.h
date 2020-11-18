/*!
 * \file
 *
 * \brief Simple string implementation
 */
#ifndef CSTRING_H
#define CSTRING_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#ifndef CSTRING_MAX_STACK_SIZE
#define CSTRING_MAX_STACK_SIZE 256
#endif

/*!
 * \brief Struct encapsulating a cstring.
 */
typedef struct
{
  char stack[CSTRING_MAX_STACK_SIZE];
  char *heap;
} cstring;

/*!
 * \brief Macro used to declare a cstring which cleans its memory when it goes
 * out of scope.
 */
#define CSTRING_AUTOCLEAN(varname) cstring varname __attribute__ ((__cleanup__(cstring_free)))

/*!
 * \brief Creates a new empty cstring.
 */
cstring cstring_new();

/*!
 * \brief Creates a cstring with an initial value.
 */
cstring cstring_new_init(const char *initVal);

/*!
 * \brief Append an array of character to a cstring.
 */
void cstring_append(cstring *s, const char *strToAppend);

/*!
 * \brief Returns the length of the string in a similar fashion as strlen.
 */
size_t cstring_length(const cstring *s);

/*!
 * \brief Returns the internal pointer of the cstring
 */
const char* cstring_c_str(const cstring* s);

/*!
 * \brief Compare a cstring with an array of character in a similar fashion as strcmp
 */
int cstring_compare_const_char(const cstring *s, const char* other);

/*!
 * \brief Compare a cstring with another cstring in a similar fashion as strcmp
 */
int cstring_compare_const_cstring(const cstring *s, const cstring* other);

/*!
 * \brief Free the memory allocated allocated by the cstring
 */
void cstring_free(cstring *s);


#ifdef __cplusplus
}
#endif

#endif /* CSTRING_H */

