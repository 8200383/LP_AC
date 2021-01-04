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

void h_util_clean_buffer()
{
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);
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

	fprintf(stdout, YELLOW("%s"), h_util_format_str(msg));

	while (scanf("%c", &c) != 1 || !isalpha(c))
	{
		puts(H_STRS_INVALID_IMPUT);
		h_util_clean_buffer();
		fprintf(stdout, YELLOW("%s"), h_util_format_str(msg));
	}

	return c;
}

int h_util_get_int(int min, int max, const char* msg)
{
	int num;

	fprintf(stdout, YELLOW("%s"), h_util_format_str(msg));

	while (scanf("%d", &num) != 1 || num < min || num > max)
	{
		puts(H_STRS_INVALID_IMPUT);
		h_util_clean_buffer();
		fprintf(stdout, RED("%s"), h_util_format_str(msg));
	}
	h_util_clean_buffer();
	return num;
}

float h_util_get_float(float min, float max, const char* msg)
{
	float num;

	fprintf(stdout, YELLOW("%s"), h_util_format_str(msg));

	while (scanf("%f", &num) != 1 || num < min || num > max)
	{
		puts(H_STRS_INVALID_IMPUT);
		h_util_clean_buffer();
		fprintf(stdout, RED("%s"), h_util_format_str(msg));
	}
	h_util_clean_buffer();
	return num;
}

int h_util_str_is_digit(const char* str)
{
	int num;
	int i;

	num = 0;
	for (i = 0; str[i] != '\0'; i++)
	{
		// check for decimal digits
		if (isdigit(str[i]) != 0)
			num++;
	}
	return num;
}

int h_util_is_name(const char* str)
{
	int i;

	if (isupper(str[0]) == 0)
		return -1;

	for (i = 1; str[i] != '\0'; i++)
	{
		if (islower(str[i]) == 0)
			return -1;
	}

	return 0;
}