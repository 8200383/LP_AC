/*
 * Created by Micael Dias on 10/12/20.
 */

#ifndef UTIL_H
#define UTIL_H

/** Reads a file from given path */
char* h_util_file_read(const char* path, int* size);

/** Gets an alphabetical letter from stdin */
char h_util_get_alphabetical_char(const char* msg);

/** Gets an int from stdin */
int h_util_get_int(int min, int max, const char* msg);

int h_util_is_name(const char* str);

int h_util_str_is_digit(const char* str);

/** Gets a float from stdin */
float h_util_get_float(float min, float max, const char* msg);

/** Cleans buffer from stdin */
void h_util_clean_buffer();

#endif //UTIL_H
