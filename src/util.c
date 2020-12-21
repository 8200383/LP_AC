/*
 * Created by Micael Dias on 10/12/20.
 */

#include "util.h"
#include "colors.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* h_util_file_read(const char* path, unsigned int* size)
{
	FILE* fptr;
	size_t buffer_size;
	char* buffer;
	int counter;
	int ch;

	if (path == NULL)
		return NULL;

	fptr = fopen(path, "r");
	if (fptr == NULL)
		return NULL;

	buffer_size = 256;
	buffer = malloc(buffer_size * sizeof(char));
	if (buffer == NULL)
	{
		free(fptr);
		return NULL;
	}

	counter = 0;
	/* Read a character at a time, resizing the buffer as necessary */
	while ((ch = fgetc(fptr)) && ch != EOF && !feof(fptr))
	{
		buffer[counter++] = (char)ch;

		if (ch == '\n')
			(*size)++;

		if (counter == buffer_size)
		{
			/* Resize twice the value of the buffer */
			buffer_size *= 2;
			buffer = realloc(buffer, buffer_size * sizeof(char));
			if (buffer == NULL)
			{
				free(fptr);
				free(buffer);
				return NULL;
			}
		}
	}

	buffer[counter - 1] = '\0';
	return buffer;
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

int h_util_regex_compare(char* str, char* pattern)
{
	regex_t regex;

	if (regcomp(&regex, pattern, 0) != 0)
		return -1;

	if (regexec(&regex, str, 0, NULL, 0) != 0)
		return -1;

	return 0;
}

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

float h_util_get_float()
{
	float n;

	scanf(" %f", &n);

	return n;
}
