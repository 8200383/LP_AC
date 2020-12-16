//
// Created by Hugo Carvalho on 12/16/2020.
//

#include "error.h"
#include <stdlib.h>
#include <string.h>

s_error* h_error_create(e_error_type type, const char* msg)
{
	s_error* error;
	error = malloc(sizeof(*error));

	if (error == NULL)
		return NULL;

	error->msg = malloc(sizeof(char) * strlen(msg));
	if(error->msg == NULL)
		return NULL;

	error->error_type = type;
	strcpy(error->msg, msg);

	return error;
}