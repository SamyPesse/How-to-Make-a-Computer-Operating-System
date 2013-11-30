

#ifndef TRIO_TRIOSTR_H
#define TRIO_TRIOSTR_H

/*
 * Documentation is located in triostr.c
 */

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "triodef.h"
#include "triop.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
  TRIO_HASH_NONE = 0,
  TRIO_HASH_PLAIN,
  TRIO_HASH_TWOSIGNED
};

#if !defined(TRIO_PUBLIC_STRING)
# if !defined(TRIO_PUBLIC)
#  define TRIO_PUBLIC
# endif
# define TRIO_PUBLIC_STRING TRIO_PUBLIC
#endif

/*************************************************************************
 * Dependencies
 */

#if defined(TRIO_EMBED_STRING)

/*
 * The application that triostr is embedded in must define which functions
 * it uses.
 *
 * The following resolves internal dependencies.
 */
  
# if defined(TRIO_FUNC_XSTRING_SET)
#  if !defined(TRIO_FUNC_DUPLICATE)
#   define TRIO_FUNC_DUPLICATE
#  endif
# endif

# if defined(TRIO_FUNC_DUPLICATE) \
  || defined(TRIO_FUNC_DUPLICATE_MAX) \
  || defined(TRIO_FUNC_STRING_DUPLICATE) \
  || defined(TRIO_FUNC_XSTRING_DUPLICATE)
#  if !defined(TRIO_FUNC_CREATE)
#   define TRIO_FUNC_CREATE
#  endif
#  if !defined(TRIO_FUNC_COPY_MAX)
#   define TRIO_FUNC_COPY_MAX
#  endif
# endif

# if defined(TRIO_FUNC_STRING_CREATE)
#  if !defined(TRIO_FUNC_STRING_DESTROY)
#   define TRIO_FUNC_STRING_DESTROY
#  endif
# endif

# if defined(TRIO_FUNC_STRING_DESTROY) \
  || defined(TRIO_FUNC_XSTRING_SET)
#  if !defined(TRIO_FUNC_DESTROY)
#   define TRIO_FUNC_DESTROY
#  endif
# endif

# if defined(TRIO_FUNC_EQUAL_LOCALE) \
  || defined(TRIO_FUNC_STRING_EQUAL) \
  || defined(TRIO_FUNC_XSTRING_EQUAL)
#  if !defined(TRIO_FUNC_EQUAL)
#   define TRIO_FUNC_EQUAL
#  endif
# endif

# if defined(TRIO_FUNC_EQUAL_CASE) \
  || defined(TRIO_FUNC_STRING_EQUAL_CASE) \
  || defined(TRIO_FUNC_XSTRING_EQUAL_CASE)
#  if !defined(TRIO_FUNC_EQUAL_CASE)
#   define TRIO_FUNC_EQUAL_CASE
#  endif
# endif

# if defined(TRIO_FUNC_SUBSTRING_MAX) \
  || defined(TRIO_FUNC_STRING_EQUAL_MAX) \
  || defined(TRIO_FUNC_XSTRING_EQUAL_MAX)
#  if !defined(TRIO_FUNC_EQUAL_MAX)
#   define TRIO_FUNC_EQUAL_MAX
#  endif
# endif

# if defined(TRIO_FUNC_TO_DOUBLE) \
  || defined(TRIO_FUNC_TO_FLOAT)
#  if !defined(TRIO_FUNC_TO_LONG_DOUBLE)
#   define TRIO_FUNC_TO_LONG_DOUBLE
#  endif
# endif

# if defined(TRIO_FUNC_STRING_TERMINATE)
#  if !defined(TRIO_FUNC_XSTRING_APPEND_CHAR)
#   define TRIO_FUNC_XSTRING_APPEND_CHAR
#  endif
# endif

# if defined(TRIO_FUNC_XSTRING_APPEND_CHAR)
#  if !defined(TRIO_FUNC_STRING_SIZE)
#   define TRIO_FUNC_STRING_SIZE
#  endif
# endif

#else

/*
 * When triostr is not embedded all functions are defined.
 */

# define TRIO_FUNC_APPEND
# define TRIO_FUNC_APPEND_MAX
# define TRIO_FUNC_CONTAINS
# define TRIO_FUNC_COPY
# define TRIO_FUNC_COPY_MAX
# define TRIO_FUNC_CREATE
# define TRIO_FUNC_DESTROY
# define TRIO_FUNC_DUPLICATE
# define TRIO_FUNC_DUPLICATE_MAX
# define TRIO_FUNC_EQUAL
# define TRIO_FUNC_EQUAL_CASE
# define TRIO_FUNC_EQUAL_CASE_MAX
# define TRIO_FUNC_EQUAL_LOCALE
# define TRIO_FUNC_EQUAL_MAX
# define TRIO_FUNC_ERROR
# if !defined(TRIO_PLATFORM_WINCE)
#  define TRIO_FUNC_FORMAT_DATE_MAX
# endif
# define TRIO_FUNC_HASH
# define TRIO_FUNC_INDEX
# define TRIO_FUNC_INDEX_LAST
# define TRIO_FUNC_LENGTH
# define TRIO_FUNC_LENGTH_MAX
# define TRIO_FUNC_LOWER
# define TRIO_FUNC_MATCH
# define TRIO_FUNC_MATCH_CASE
# define TRIO_FUNC_SPAN_FUNCTION
# define TRIO_FUNC_SUBSTRING
# define TRIO_FUNC_SUBSTRING_MAX
# define TRIO_FUNC_TO_DOUBLE
# define TRIO_FUNC_TO_FLOAT
# define TRIO_FUNC_TO_LONG
# define TRIO_FUNC_TO_LONG_DOUBLE
# define TRIO_FUNC_TO_LOWER
# define TRIO_FUNC_TO_UNSIGNED_LONG
# define TRIO_FUNC_TO_UPPER
# define TRIO_FUNC_TOKENIZE
# define TRIO_FUNC_UPPER

# define TRIO_FUNC_STRING_APPEND
# define TRIO_FUNC_STRING_CONTAINS
# define TRIO_FUNC_STRING_COPY
# define TRIO_FUNC_STRING_CREATE
# define TRIO_FUNC_STRING_DESTROY
# define TRIO_FUNC_STRING_DUPLICATE
# define TRIO_FUNC_STRING_EQUAL
# define TRIO_FUNC_STRING_EQUAL_CASE
# define TRIO_FUNC_STRING_EQUAL_CASE_MAX
# define TRIO_FUNC_STRING_EQUAL_MAX
# define TRIO_FUNC_STRING_EXTRACT
# if !defined(TRIO_PLATFORM_WINCE)
#  define TRIO_FUNC_STRING_FORMAT_DATE_MAX
# endif
# define TRIO_FUNC_STRING_GET
# define TRIO_FUNC_STRING_INDEX
# define TRIO_FUNC_STRING_INDEX_LAST
# define TRIO_FUNC_STRING_LENGTH
# define TRIO_FUNC_STRING_LOWER
# define TRIO_FUNC_STRING_MATCH
# define TRIO_FUNC_STRING_MATCH_CASE
# define TRIO_FUNC_STRING_SIZE
# define TRIO_FUNC_STRING_SUBSTRING
# define TRIO_FUNC_STRING_TERMINATE
# define TRIO_FUNC_STRING_UPPER

# define TRIO_FUNC_XSTRING_APPEND
# define TRIO_FUNC_XSTRING_APPEND_CHAR
# define TRIO_FUNC_XSTRING_CONTAINS
# define TRIO_FUNC_XSTRING_COPY
# define TRIO_FUNC_XSTRING_DUPLICATE
# define TRIO_FUNC_XSTRING_EQUAL
# define TRIO_FUNC_XSTRING_EQUAL_CASE
# define TRIO_FUNC_XSTRING_EQUAL_CASE_MAX
# define TRIO_FUNC_XSTRING_EQUAL_MAX
# define TRIO_FUNC_XSTRING_MATCH
# define TRIO_FUNC_XSTRING_MATCH_CASE
# define TRIO_FUNC_XSTRING_SET
# define TRIO_FUNC_XSTRING_SUBSTRING

#endif


/*************************************************************************
 * String functions
 */

#if defined(TRIO_FUNC_APPEND)
TRIO_PUBLIC_STRING int
trio_append
TRIO_PROTO((char *target, TRIO_CONST char *source));
#endif

#if defined(TRIO_FUNC_APPEND_MAX)
TRIO_PUBLIC_STRING int
trio_append_max
TRIO_PROTO((char *target, size_t max, TRIO_CONST char *source));
#endif

#if defined(TRIO_FUNC_CONTAINS)
TRIO_PUBLIC_STRING int
trio_contains
TRIO_PROTO((TRIO_CONST char *string, TRIO_CONST char *substring));
#endif

#if defined(TRIO_FUNC_COPY)
TRIO_PUBLIC_STRING int
trio_copy
TRIO_PROTO((char *target, TRIO_CONST char *source));
#endif

#if defined(TRIO_FUNC_COPY_MAX)
TRIO_PUBLIC_STRING int
trio_copy_max
TRIO_PROTO((char *target, size_t max, TRIO_CONST char *source));
#endif

#if defined(TRIO_FUNC_CREATE)
TRIO_PUBLIC_STRING char *
trio_create
TRIO_PROTO((size_t size));
#endif

#if defined(TRIO_FUNC_DESTROY)
TRIO_PUBLIC_STRING void
trio_destroy
TRIO_PROTO((char *string));
#endif

#if defined(TRIO_FUNC_DUPLICATE)
TRIO_PUBLIC_STRING char *
trio_duplicate
TRIO_PROTO((TRIO_CONST char *source));
#endif

#if defined(TRIO_FUNC_DUPLICATE_MAX)
TRIO_PUBLIC_STRING char *
trio_duplicate_max
TRIO_PROTO((TRIO_CONST char *source, size_t max));
#endif

#if defined(TRIO_FUNC_EQUAL)
TRIO_PUBLIC_STRING int
trio_equal
TRIO_PROTO((TRIO_CONST char *first, TRIO_CONST char *second));
#endif

#if defined(TRIO_FUNC_EQUAL_CASE)
TRIO_PUBLIC_STRING int
trio_equal_case
TRIO_PROTO((TRIO_CONST char *first, TRIO_CONST char *second));
#endif

#if defined(TRIO_FUNC_EQUAL_CASE_MAX)
TRIO_PUBLIC_STRING int
trio_equal_case_max
TRIO_PROTO((TRIO_CONST char *first, size_t max, TRIO_CONST char *second));
#endif

#if defined(TRIO_FUNC_EQUAL_LOCALE)
TRIO_PUBLIC_STRING int
trio_equal_locale
TRIO_PROTO((TRIO_CONST char *first, TRIO_CONST char *second));
#endif

#if defined(TRIO_FUNC_EQUAL_MAX)
TRIO_PUBLIC_STRING int
trio_equal_max
TRIO_PROTO((TRIO_CONST char *first, size_t max, TRIO_CONST char *second));
#endif

#if defined(TRIO_FUNC_ERROR)
TRIO_PUBLIC_STRING TRIO_CONST char *
trio_error
TRIO_PROTO((int));
#endif

#if defined(TRIO_FUNC_FORMAT_DATE_MAX)
TRIO_PUBLIC_STRING size_t
trio_format_date_max
TRIO_PROTO((char *target, size_t max, TRIO_CONST char *format, TRIO_CONST struct tm *datetime));
#endif

#if defined(TRIO_FUNC_HASH)
TRIO_PUBLIC_STRING unsigned long
trio_hash
TRIO_PROTO((TRIO_CONST char *string, int type));
#endif

#if defined(TRIO_FUNC_INDEX)
TRIO_PUBLIC_STRING char *
trio_index
TRIO_PROTO((TRIO_CONST char *string, int character));
#endif

#if defined(TRIO_FUNC_INDEX_LAST)
TRIO_PUBLIC_STRING char *
trio_index_last
TRIO_PROTO((TRIO_CONST char *string, int character));
#endif

#if defined(TRIO_FUNC_LENGTH)
TRIO_PUBLIC_STRING size_t
trio_length
TRIO_PROTO((TRIO_CONST char *string));
#endif

#if defined(TRIO_FUNC_LENGTH_MAX)
TRIO_PUBLIC_STRING size_t
trio_length_max
TRIO_PROTO((TRIO_CONST char *string, size_t max));
#endif

#if defined(TRIO_FUNC_LOWER)
TRIO_PUBLIC_STRING int
trio_lower
TRIO_PROTO((char *target));
#endif

#if defined(TRIO_FUNC_MATCH)
TRIO_PUBLIC_STRING int
trio_match
TRIO_PROTO((TRIO_CONST char *string, TRIO_CONST char *pattern));
#endif

#if defined(TRIO_FUNC_MATCH_CASE)
TRIO_PUBLIC_STRING int
trio_match_case
TRIO_PROTO((TRIO_CONST char *string, TRIO_CONST char *pattern));
#endif

#if defined(TRIO_FUNC_SPAN_FUNCTION)
TRIO_PUBLIC_STRING size_t
trio_span_function
TRIO_PROTO((char *target, TRIO_CONST char *source, int (*Function) TRIO_PROTO((int))));
#endif

#if defined(TRIO_FUNC_SUBSTRING)
TRIO_PUBLIC_STRING char *
trio_substring
TRIO_PROTO((TRIO_CONST char *string, TRIO_CONST char *substring));
#endif

#if defined(TRIO_FUNC_SUBSTRING_MAX)
TRIO_PUBLIC_STRING char *
trio_substring_max
TRIO_PROTO((TRIO_CONST char *string, size_t max, TRIO_CONST char *substring));
#endif

#if defined(TRIO_FUNC_TO_DOUBLE)
TRIO_PUBLIC_STRING double
trio_to_double
TRIO_PROTO((TRIO_CONST char *source, char **endp));
#endif

#if defined(TRIO_FUNC_TO_FLOAT)
TRIO_PUBLIC_STRING float
trio_to_float
TRIO_PROTO((TRIO_CONST char *source, char **endp));
#endif

#if defined(TRIO_FUNC_TO_LONG)
TRIO_PUBLIC_STRING long
trio_to_long
TRIO_PROTO((TRIO_CONST char *source, char **endp, int base));
#endif

#if defined(TRIO_FUNC_TO_LOWER)
TRIO_PUBLIC_STRING int
trio_to_lower
TRIO_PROTO((int source));
#endif

#if defined(TRIO_FUNC_TO_LONG_DOUBLE)
TRIO_PUBLIC_STRING trio_long_double_t
trio_to_long_double
TRIO_PROTO((TRIO_CONST char *source, char **endp));
#endif

#if defined(TRIO_FUNC_TO_UNSIGNED_LONG)
TRIO_PUBLIC_STRING unsigned long
trio_to_unsigned_long
TRIO_PROTO((TRIO_CONST char *source, char **endp, int base));
#endif

#if defined(TRIO_FUNC_TO_UPPER)
TRIO_PUBLIC_STRING int
trio_to_upper
TRIO_PROTO((int source));
#endif

#if defined(TRIO_FUNC_TOKENIZE)
TRIO_PUBLIC_STRING char *
trio_tokenize
TRIO_PROTO((char *string, TRIO_CONST char *delimiters));
#endif

#if defined(TRIO_FUNC_UPPER)
TRIO_PUBLIC_STRING int
trio_upper
TRIO_PROTO((char *target));
#endif

/*************************************************************************
 * Dynamic string functions
 */

/*
 * Opaque type for dynamic strings
 */

typedef struct _trio_string_t trio_string_t;

#if defined(TRIO_FUNC_STRING_APPEND)
TRIO_PUBLIC_STRING int
trio_string_append
TRIO_PROTO((trio_string_t *self, trio_string_t *other));
#endif

#if defined(TRIO_FUNC_STRING_CONTAINS)
TRIO_PUBLIC_STRING int
trio_string_contains
TRIO_PROTO((trio_string_t *self, trio_string_t *other));
#endif

#if defined(TRIO_FUNC_STRING_COPY)
TRIO_PUBLIC_STRING int
trio_string_copy
TRIO_PROTO((trio_string_t *self, trio_string_t *other));
#endif

#if defined(TRIO_FUNC_STRING_CREATE)
TRIO_PUBLIC_STRING trio_string_t *
trio_string_create
TRIO_PROTO((int initial_size));
#endif

#if defined(TRIO_FUNC_STRING_DESTROY)
TRIO_PUBLIC_STRING void
trio_string_destroy
TRIO_PROTO((trio_string_t *self));
#endif

#if defined(TRIO_FUNC_STRING_DUPLICATE)
TRIO_PUBLIC_STRING trio_string_t *
trio_string_duplicate
TRIO_PROTO((trio_string_t *other));
#endif

#if defined(TRIO_FUNC_STRING_EQUAL)
TRIO_PUBLIC_STRING int
trio_string_equal
TRIO_PROTO((trio_string_t *self, trio_string_t *other));
#endif

#if defined(TRIO_FUNC_STRING_EQUAL_MAX)
TRIO_PUBLIC_STRING int
trio_string_equal_max
TRIO_PROTO((trio_string_t *self, size_t max, trio_string_t *second));
#endif

#if defined(TRIO_FUNC_STRING_EQUAL_CASE)
TRIO_PUBLIC_STRING int
trio_string_equal_case
TRIO_PROTO((trio_string_t *self, trio_string_t *other));
#endif

#if defined(TRIO_FUNC_STRING_EQUAL_CASE_MAX)
TRIO_PUBLIC_STRING int
trio_string_equal_case_max
TRIO_PROTO((trio_string_t *self, size_t max, trio_string_t *other));
#endif

#if defined(TRIO_FUNC_STRING_EXTRACT)
TRIO_PUBLIC_STRING char *
trio_string_extract
TRIO_PROTO((trio_string_t *self));
#endif

#if defined(TRIO_FUNC_STRING_FORMAT_DATE_MAX)
TRIO_PUBLIC_STRING size_t
trio_string_format_date_max
TRIO_PROTO((trio_string_t *self, size_t max, TRIO_CONST char *format, TRIO_CONST struct tm *datetime));
#endif

#if defined(TRIO_FUNC_STRING_GET)
TRIO_PUBLIC_STRING char *
trio_string_get
TRIO_PROTO((trio_string_t *self, int offset));
#endif

#if defined(TRIO_FUNC_STRING_INDEX)
TRIO_PUBLIC_STRING char *
trio_string_index
TRIO_PROTO((trio_string_t *self, int character));
#endif

#if defined(TRIO_FUNC_STRING_INDEX_LAST)
TRIO_PUBLIC_STRING char *
trio_string_index_last
TRIO_PROTO((trio_string_t *self, int character));
#endif

#if defined(TRIO_FUNC_STRING_LENGTH)
TRIO_PUBLIC_STRING int
trio_string_length
TRIO_PROTO((trio_string_t *self));
#endif

#if defined(TRIO_FUNC_STRING_LOWER)
TRIO_PUBLIC_STRING int
trio_string_lower
TRIO_PROTO((trio_string_t *self));
#endif

#if defined(TRIO_FUNC_STRING_MATCH)
TRIO_PUBLIC_STRING int
trio_string_match
TRIO_PROTO((trio_string_t *self, trio_string_t *other));
#endif

#if defined(TRIO_FUNC_STRING_MATCH_CASE)
TRIO_PUBLIC_STRING int
trio_string_match_case
TRIO_PROTO((trio_string_t *self, trio_string_t *other));
#endif

#if defined(TRIO_FUNC_STRING_SIZE)
TRIO_PUBLIC_STRING int
trio_string_size
TRIO_PROTO((trio_string_t *self));
#endif

#if defined(TRIO_FUNC_STRING_SUBSTRING)
TRIO_PUBLIC_STRING char *
trio_string_substring
TRIO_PROTO((trio_string_t *self, trio_string_t *other));
#endif

#if defined(TRIO_FUNC_STRING_TERMINATE)
TRIO_PUBLIC_STRING void
trio_string_terminate
TRIO_PROTO((trio_string_t *self));
#endif

#if defined(TRIO_FUNC_STRING_UPPER)
TRIO_PUBLIC_STRING int
trio_string_upper
TRIO_PROTO((trio_string_t *self));
#endif

#if defined(TRIO_FUNC_XSTRING_APPEND)
TRIO_PUBLIC_STRING int
trio_xstring_append
TRIO_PROTO((trio_string_t *self, TRIO_CONST char *other));
#endif

#if defined(TRIO_FUNC_XSTRING_APPEND_CHAR)
TRIO_PUBLIC_STRING int
trio_xstring_append_char
TRIO_PROTO((trio_string_t *self, char character));
#endif

#if defined(TRIO_FUNC_XSTRING_CONTAINS)
TRIO_PUBLIC_STRING int
trio_xstring_contains
TRIO_PROTO((trio_string_t *self, TRIO_CONST char *other));
#endif

#if defined(TRIO_FUNC_XSTRING_COPY)
TRIO_PUBLIC_STRING int
trio_xstring_copy
TRIO_PROTO((trio_string_t *self, TRIO_CONST char *other));
#endif

#if defined(TRIO_FUNC_XSTRING_DUPLICATE)
TRIO_PUBLIC_STRING trio_string_t *
trio_xstring_duplicate
TRIO_PROTO((TRIO_CONST char *other));
#endif

#if defined(TRIO_FUNC_XSTRING_EQUAL)
TRIO_PUBLIC_STRING int
trio_xstring_equal
TRIO_PROTO((trio_string_t *self, TRIO_CONST char *other));
#endif

#if defined(TRIO_FUNC_XSTRING_EQUAL_MAX)
TRIO_PUBLIC_STRING int
trio_xstring_equal_max
TRIO_PROTO((trio_string_t *self, size_t max, TRIO_CONST char *other));
#endif

#if defined(TRIO_FUNC_XSTRING_EQUAL_CASE)
TRIO_PUBLIC_STRING int
trio_xstring_equal_case
TRIO_PROTO((trio_string_t *self, TRIO_CONST char *other));
#endif

#if defined(TRIO_FUNC_XSTRING_EQUAL_CASE_MAX)
TRIO_PUBLIC_STRING int
trio_xstring_equal_case_max
TRIO_PROTO((trio_string_t *self, size_t max, TRIO_CONST char *other));
#endif

#if defined(TRIO_FUNC_XSTRING_MATCH)
TRIO_PUBLIC_STRING int
trio_xstring_match
TRIO_PROTO((trio_string_t *self, TRIO_CONST char *other));
#endif

#if defined(TRIO_FUNC_XSTRING_MATCH_CASE)
TRIO_PUBLIC_STRING int
trio_xstring_match_case
TRIO_PROTO((trio_string_t *self, TRIO_CONST char *other));
#endif

#if defined(TRIO_FUNC_XSTRING_SET)
TRIO_PUBLIC_STRING void
trio_xstring_set
TRIO_PROTO((trio_string_t *self, char *buffer));
#endif

#if defined(TRIO_FUNC_XSTRING_SUBSTRING)
TRIO_PUBLIC_STRING char *
trio_xstring_substring
TRIO_PROTO((trio_string_t *self, TRIO_CONST char *other));
#endif

#ifdef __cplusplus
}
#endif

#endif /* TRIO_TRIOSTR_H */
