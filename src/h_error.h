//
// Created by Hugo Carvalho on 12/16/2020.
//

#ifndef _H_ERROR_H_
#define _H_ERROR_H_

typedef enum
{
	H_ERROR_UNKNOWN,
	H_ERROR_ALLOCATION,
	H_ERROR_READ,
	H_ERROR_WRITE
} e_error_type;

typedef struct
{
	char* msg;
	e_error_type error_type;
} s_error;

s_error* h_error_create(e_error_type type, const char* msg);

#endif //_H_ERROR_H_