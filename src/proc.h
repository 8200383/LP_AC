/*
 * Created by Micael Dias on 26/12/20.
 * Edited by Hugo Carvalho on 27/12/20.
 */

#ifndef _PROC_H_
#define _PROC_H_

#include "irs.h"
#include "seg_social.h"
#include "error.h"
#include "calendar.h"

#define MAX_FILENAME 256

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
s_sheet* h_proc_alloc();

/** Import a file sheet from a given path */
s_error* h_proc_import(s_sheet* sheet, const char* path);

/** Exports a file sheet from s_sheet */
s_error* h_proc_export_csv(s_sheet* sheet, const char* path);

/** Generate a filename from a given month and an extension */
char* h_proc_generate_filename(e_month month, const char* extension);

/** Comment */
s_error* h_processing(s_sheet* sheet, s_arr_irs irs_array, s_arr_seg_social ss_array);

#endif //_proc_H_
