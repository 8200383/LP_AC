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
char* h_util_file_read(const char* path)
{
	FILE* fp;
	unsigned long total_bytes;
	unsigned long read_bytes;
	char* str;

	fp = fopen(path, "r");
	if (fp == NULL)
		return NULL;

	fseek(fp, 0L, SEEK_END);
	total_bytes = ftell(fp) + 1;
	fseek(fp, 0L, SEEK_SET);

	str = malloc(total_bytes);
	if (str == NULL)
	{
		fclose(fp);
		return NULL;
	}

	read_bytes = fread(str, sizeof(char), total_bytes - 1, fp);
	if (read_bytes < total_bytes - 1)
	{
		free(str);
		fclose(fp);
		return NULL;
	}

	fclose(fp);
	str[total_bytes - 1] = '\0';
	return str;
}

int h_util_get_lines_from_str(const char* str) {
	int i;
	int lines;

	i = 0;
	lines = 0;
	while (str[i] != '\0') {
		if (str[i] == '\n') {
			lines++;
		}
		i++;
	}

	return lines;
}