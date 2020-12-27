/*
 * Created by Micael Dias on 26/12/20.
 * Edited by Hugo Carvalho on 27/12/20.
 */

#ifndef _PROCESSING_H_
#define _PROCESSING_H_

#include "error.h"

typedef struct
{
	char* func_code;
	int full_days;
	int half_days;
	int weekend_days;
	int absent_days;
} s_paysheet;

typedef struct
{
	s_paysheet* paysheet;
	int month;
	int used;
	int max_capacity;
} s_sheet;

/** Allocs memory for s_sheet */
s_sheet* h_processing_alloc();

/** Import a file sheet from a given path */
s_error* h_processing_import(s_sheet* sheet, const char* path);

/** Exports a file sheet from s_sheet */
s_error* h_processing_export_csv(s_sheet* sheet, const char* path);

#endif //_PROCESSING_H_
