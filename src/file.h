/*
 * Created by Micael Dias on 12/26/20.
 */

#ifndef _FILE_H_
#define _FILE_H_

#include "error.h"

#define N_MONTHS 12

typedef struct
{
	char* parent_dir;
	char* filename;
} s_files;

typedef struct
{
	s_files* files;
	int used;
	int max_capacity;
} s_arr_files;

s_arr_files* h_file_alloc();

/** Lists files who match pattern from give path (POSIX) */
s_arr_files* h_file_ls(const char* path, char* pattern);

void h_file_free(s_arr_files* array_files);

#endif //_FILE_H_
