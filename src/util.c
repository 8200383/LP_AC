/*
 * Created by Micael Dias on 10/12/20.
 */

#include "util.h"
#include "colors.h"
#include "strs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

char* h_util_file_read(const char* path, int* size)
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

int h_util_regex_compare(const char* str, const char* pattern)
{
	regex_t regex;

	if (regcomp(&regex, pattern, 0) != 0)
		return -1;

	if (regexec(&regex, str, 0, NULL, 0) != 0)
		return -1;

	return 0;
}

char* h_util_format_str(const char* msg)
{
	int i;
	char* buffer;

	if (msg == NULL)
		return H_STRS_PROMPT;

	buffer = malloc(strlen(msg) + strlen(H_STRS_PROMPT_NEW_LINE));
	if (buffer == NULL)
		return NULL;

	for (i = 0; i < sizeof(buffer); i++)
		buffer[i] = '\0';

	strcat(buffer, msg);
	strcat(buffer, H_STRS_PROMPT_NEW_LINE);

	return buffer;
}

char h_util_get_option(char param1, char param2, const char* msg)
{
	char op;

	do
	{
		op = h_util_get_alphabetical_char(msg);
	} while (op != tolower(param1) && op != tolower(param2));

	return op;
}

char h_util_get_alphabetical_char(const char* msg)
{
	char c;

	do
	{
		fprintf(stdout, YELLOW("%s"), h_util_format_str(msg));
		scanf(" %c", &c);
	} while (!isalpha(c));

	return c;
}

unsigned int h_util_get_positive_int(const char* msg)
{
	unsigned int n;

	fprintf(stdout, YELLOW("%s"), h_util_format_str(msg));
	scanf(" %d", &n);

	return n;
}

float h_util_get_float(const char* msg)
{
	float n;

	fprintf(stdout, YELLOW("%s"), h_util_format_str(msg));
	scanf(" %f", &n);

	return n;
}
