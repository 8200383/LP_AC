/*
 * Created by Micael Dias on 12/26/20.
 */

#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include "file.h"
#include "util.h"

s_files* h_file_alloc()
{
	s_files* array_files;
	int i;
	int j;

	array_files = malloc((N_MONTHS * 2) * sizeof(s_files));
	if (array_files == NULL)
		return NULL;

	for (i = 0; i < (N_MONTHS * 2); i++)
	{
		for (j = 0; j < MAX_BUFFER; j++)
		{
			array_files[i].parent_dir[j] = '\0';
			array_files[i].filename[j] = '\0';
		}
	}

	return array_files;
}

s_error* h_file_ls(s_files* array_files, int* n_elem, const char* path, char* pattern)
{
	DIR* dp;
	struct dirent* dir;
	int i;
	int j;

	dp = opendir(path);
	if (dp == NULL)
		return h_error_create(H_ERROR_READ, path);

	while ((dir = readdir(dp)) != NULL)
	{
		if (h_util_regexcmp(dir->d_name, pattern))
		{
			for (i = 0; i < strlen(path); i++)
				array_files[*n_elem].parent_dir[i] = path[i];

			for (j = 0; j < strlen(dir->d_name); j++)
				array_files[*n_elem].filename[j] = dir->d_name[j];

			(*n_elem)++;
		}
	}

	if (closedir(dp) == -1)
		return h_error_create(H_ERROR_UNKNOWN, "Cannot close");

	return NULL;
}
