/**
 * @file util.h
 * @author Micael Dias
 * @date 10/12/20
 * @brief Helper functions
 */

#ifndef UTIL_H
#define UTIL_H

/**
 * Reads a file from given path
 * @param path The file path
 * @param size Updates the size (num of lines read) of the file from a ptr
 * @return char*
 */
char* h_util_file_read(const char* path, int* size);

/**
 * Gets an alphabetical letter from stdin
 * @param msg Sets a message to display when input
 * @return char
 */
char h_util_get_alphabetical_char(const char* msg);

/**
 * Gets an int from stdin
 * @param min Sets a min value to input
 * @param max Sets a max value to input
 * @param msg Sets a message to display when input
 * @return int
 */
int h_util_get_int(int min, int max, const char* msg);

/**
 * Verifiy if a string is a digit
 * @param str The string to verify
 * @return int Return the number of digits found or 0 returned
 */
int h_util_str_is_digit(const char* str);

/**
 * Gets a float from stdin
 * @param min Sets a min value to input
 * @param max Sets a max value to input
 * @param msg Sets a message to display when input
 * @return float
 */
float h_util_get_float(float min, float max, const char* msg);

/**
 * Cleans buffer from stdin
 */
void h_util_clean_buffer();

#endif //UTIL_H
