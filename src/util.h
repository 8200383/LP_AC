/*
 * Created by Micael Dias on 10/12/20.
 */

/** @file */

#ifndef UTIL_H
#define UTIL_H

/** Compares the string pointed to X to the string pointed to Y */
#define h_util_strequal(x, y) (strcmp(x, y) == 0)

/** A macro for h_util_regex_compare */
#define h_util_regexcmp(x, y) (h_util_regex_compare(x, y) == 0)

/** Reads a file from given path */
char* h_util_file_read(const char* path, int* size);

/** Gets an alphabetical letter from stdin */
char h_util_get_alphabetical_char(const char* msg);

/** Gets an int from stdin */
int h_util_get_int(int min, int max, const char* msg);

/** Gets a float from stdin */
float h_util_get_float(float min, float max, const char* msg);

/** Compare a string to a regular expression */
int h_util_regex_compare(const char* str, const char* pattern);

/** Cleans buffer from stdin */
void h_util_clean_buffer();

#endif //UTIL_H
