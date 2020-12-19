//
// Created by Hugo Carvalho on 12/16/2020.
// Updated by Micael Dias on 17/12/2020
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "colors.h"

s_error* h_error_create(e_error_type type, const char* msg)
{
	s_error* error;
	error = malloc(sizeof(*error));

	if (error == NULL)
		return NULL;

	error->msg = malloc(sizeof(char) * strlen(msg));
	if (error->msg == NULL)
		return NULL;

	error->error_type = type;
	strcpy(error->msg, msg);

	return error;
}

void h_error_print(s_error* error)
{
	switch (error->error_type)
	{
	case H_ERROR_ALLOCATION:
		fprintf(stderr, RED("TYPE: Alloc"));
		break;
	case H_ERROR_READ:
		fprintf(stderr, RED("TYPE: File Read"));
		break;
	case H_ERROR_WRITE:
		fprintf(stderr, RED("TYPE: File Write"));
		break;
	case H_ERROR_PARSING:
		fprintf(stderr, RED("TYPE: Parsing"));
	default:
		fprintf(stderr, RED("TYPE: Unknown"));
	}

	fprintf(stderr, CYAN(" | MSG: %s\n"), error->msg);
}

void h_error_free(s_error* error)
{
	if (error == NULL)
		return;

	free(error->msg);
	free(error);
}
