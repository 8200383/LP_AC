/*
 * Created by Micael Dias on 10/12/20.
 */

#include "util.h"
#include "colors.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* h_util_file_read(const char* path)
{
	FILE* fp;
	unsigned long total_bytes;
	unsigned long read_bytes;
	char* str;

	if (path == NULL)
		return NULL;

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

int h_util_get_lines_from_str(const char* str)
{
	int i;
	int lines;

	if (str == NULL)
		return -1;

	i = 0;
	lines = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			lines++;
		i++;
	}

	return lines;
}

/**
 * Get a positive integer and return it
 * @return int
 */
int h_util_get_positive_int()
{
	int n;

	do
	{
		fprintf(stdout, YELLOW("> "));
		scanf(" %d", &n);
		if (n < 0)
		{
			fprintf(stdout, RED("> Inteiro Inválido\n"));
		}
	} while (n < 0);

	return n;
}

int h_util_regex_compare(char* str, char* pattern)
{
	regex_t regex;

	if (regcomp(&regex, pattern, 0) != 0)
		return -1;

	if (regexec(&regex, str, 0, NULL, 0) != 0)
		return -1;

	return 0;
}

float h_util_get_float()
{
	float n;

	scanf(" %f", &n);

	return n;
}
