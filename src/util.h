/*
 * Created by Micael Dias on 10/12/20.
 */

#ifndef _UTIL_H
#define _UTIL_H

#include <unistd.h>

#define m_util_strequal(x, y) (strcmp(x, y) == 0)
#define m_util_regexcmp(x, y) (h_util_regex_compare(x, y) == 0)
#define m_util_file_exists(x) (access(x, F_OK) == 0)

char* h_util_file_read(const char* path);
int h_util_get_lines_from_str(const char* str);
int h_util_get_positive_int();
float h_util_get_float();
int h_util_regex_compare(char* str, char* pattern);

#endif //_UTIL_H
