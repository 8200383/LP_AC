/*
 * Created by Micael Dias on 12/26/20.
 */

#ifndef _FILE_H_
#define _FILE_H_

#include "error.h"

#define MAX_BUFFER 256
#define N_MONTHS 12

typedef struct
{
	char parent_dir[MAX_BUFFER];
	char filename[MAX_BUFFER];
} s_files;

s_files* h_file_alloc();

/** Lists files who match pattern from give path (POSIX) */
s_error* h_file_ls(s_files* array_files, int* n_elem, const char* path, char* pattern);

#endif //_FILE_H_
