//
// Created by Hugo Carvalho on 12/16/2020.
// Updated by Micael Dias on 17/12/2020
//

#ifndef _ERROR_H_
#define _ERROR_H_

typedef enum
{
	H_ERROR_UNKNOWN,
	H_ERROR_ALLOCATION,
	H_ERROR_READ,
	H_ERROR_EDIT,
	H_ERROR_DELETE,
	H_ERROR_WRITE,
	H_ERROR_PARSING
} e_error_type;

typedef struct
{
	char* msg;
	e_error_type error_type;
} s_error;

s_error* h_error_create(e_error_type type, const char* msg);
void h_error_print(s_error* error);
void h_error_free(s_error* error);

#endif //_ERROR_H_