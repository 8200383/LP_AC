/*
 * Created by Micael Dias on 12/26/20.
 */

#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include "file.h"
#include "util.h"

s_arr_files* h_file_alloc()
{
	s_arr_files* array_files;
	int i;

	array_files = malloc(sizeof(s_arr_files));
	if (array_files == NULL)
		return NULL;

	array_files->max_capacity = N_MONTHS * 2;
	array_files->used = 0;

	array_files->files = malloc(array_files->max_capacity * sizeof(s_files));
	if (array_files->files == NULL)
		return NULL;

	for (i = 0; i < array_files->max_capacity; i++)
	{
		array_files->files[i].parent_dir = NULL;
		array_files->files[i].filename = NULL;
	}

	return array_files;
}

s_arr_files* h_file_ls(const char* path, char* pattern)
{
	DIR* dp;
	struct dirent* dir;
	s_arr_files* array_files;
	int i;

	dp = opendir(path);
	if (dp == NULL)
		return NULL;

	array_files = h_file_alloc();
	if (array_files == NULL)
		return NULL;

	i = 0;
	while ((dir = readdir(dp)) != NULL)
	{
		if (array_files->used == array_files->max_capacity)
		{
			array_files->files = realloc(array_files->files, array_files->max_capacity * 2);
			if (array_files == NULL)
				return NULL;

			array_files->max_capacity *= 2;
		}

		if (h_util_strequal(dir->d_name, ".") || h_util_strequal(dir->d_name, ".."))
			continue;

		if (h_util_regexcmp(dir->d_name, pattern) && dir->d_type == DT_REG)
		{
			array_files->files[i].parent_dir = malloc(sizeof(char) * strlen(path));
			if (array_files->files[i].parent_dir == NULL)
				return NULL;

			array_files->files[i].filename = malloc(sizeof(char) * strlen(dir->d_name));
			if (array_files->files[i].filename == NULL)
				return NULL;

			strcpy(array_files->files[i].parent_dir, path);
			strcpy(array_files->files[i].filename, dir->d_name);
			array_files->used = i;

			i++;
		}
	}

	if (closedir(dp) == -1)
		return NULL;

	return array_files;
}

void h_file_free(s_arr_files* array_files) {
	int i;

	for (i = 0; i <= array_files->used; i++) {
		free(array_files->files[i].filename);
		free(array_files->files[i].parent_dir);
	}

	free(array_files->files);
	free(array_files);
}