/*
 * Created by Micael Dias on 12/26/20.
 */

#ifndef _PROCESSING_H_
#define _PROCESSING_H_

#include "error.h"

typedef struct
{
	char* func_code;
	int month;
	int full_days;
	int half_days;
	int weekend_days;
} s_sheet;

/** Allocs memory for s_sheet */
s_sheet* h_processing_alloc();

/** Import a file sheet from a given path */
s_error* h_processing_import(s_sheet* sheet, const char* path);

/** Exports a file sheet from s_sheet */
s_error* h_processing_export(s_sheet* sheet, const char* path);

#endif //_PROCESSING_H_
