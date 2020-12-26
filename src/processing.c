/*
 * Created by Micael Dias on 12/26/20.
 */

#include <stdio.h>
#include <stdlib.h>
#include "processing.h"
#include "util.h"

s_sheet* h_processing_alloc()
{
	s_sheet* sheet;

	sheet = malloc(sizeof(s_sheet));
	if (sheet == NULL)
		return NULL;

	sheet->func_code = "\0";
	sheet->month = 0;
	sheet->full_days = 0;
	sheet->half_days = 0;
	sheet->weekend_days = 0;

	return sheet;
}

s_error* h_processing_import(s_sheet* sheet, const char* path)
{
	FILE* fp;

	if (sheet == NULL)
		return h_error_create(H_ERROR_ALLOCATION, path);

	fp = fopen(path, "rb");
	if (fp == NULL)
		return h_error_create(H_ERROR_READ, path);

	if (fread(sheet, sizeof(s_sheet), 1, fp) == 0)
		return h_error_create(H_ERROR_READ, path);

	return NULL;
}

s_error* h_processing_export(s_sheet* sheet, const char* path)
{
	FILE* fp;

	fp = fopen(path, "wb");
	if (fp == NULL)
		return h_error_create(H_ERROR_WRITE, path);

	if (fwrite(sheet, sizeof(s_sheet), 1, fp) == 0)
		return h_error_create(H_ERROR_WRITE, path);

	return NULL;
}
