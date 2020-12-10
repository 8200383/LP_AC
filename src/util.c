/*
 * Created by Micael Dias on 10/12/20.
 */

#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Read a file
 * @param path The filepath
 * @param len Save into a variable the len of the file
 * @return char*
 */
char* h_util_file_read(const char* path, long len)
{
	FILE* fp = fopen(path, "r");
	if (fp == NULL)
		return NULL;

	fseek(fp, 0L, SEEK_END);
	len = ftell(fp) + 1;
	fseek(fp, 0L, SEEK_SET);

	char* str = malloc(len);
	if (str == NULL)
	{
		fclose(fp);
		return NULL;
	}

	size_t chucks = fread(str, sizeof(char), len - 1, fp);
	if (chucks < len - 1)
	{
		free(str);
		fclose(fp);
		return NULL;
	}

	fclose(fp);
	str[len - 1] = '\0';
	return str;
}