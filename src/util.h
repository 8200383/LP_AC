/*
 * Created by Micael Dias on 10/12/20.
 */

#ifndef _UTIL_H
#define _UTIL_H

#include <unistd.h>

/** Compares the string pointed to X to the string pointed to Y */
#define m_util_strequal(x, y) (strcmp(x, y) == 0)
/** A macro for h_util_regex_compare */
#define m_util_regexcmp(x, y) (h_util_regex_compare(x, y) == 0)

char* h_util_file_read(const char* path, unsigned int* size);
/** Gets an int from stdin */
int h_util_get_positive_int();
/** Gets a float from stdin */
float h_util_get_float();
/** Compare a string to a regular expression */
int h_util_regex_compare(char* str, char* pattern);

#endif //_UTIL_H
