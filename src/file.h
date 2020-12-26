/*
 * Created by Micael Dias on 12/26/20.
 */

#ifndef _FILE_H_
#define _FILE_H_

#include "error.h"

#define MAX_BUFFER 256

typedef struct
{
	char parent_dir[MAX_BUFFER];
	char filename[MAX_BUFFER];
} s_sheet_file;

s_sheet_file* h_file_allocate();

/** Lists files who match pattern from give path (POSIX) */
s_error* h_file_ls(s_sheet_file* array_files, int* n_elem, const char* path, char* pattern);

#endif //_FILE_H_
