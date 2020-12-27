/* 
 * Created by Micael Dias on 14/12/20.
 */

#include <stdio.h>

#include "menu.h"
#include "colors.h"
#include "strs.h"
#include "util.h"
#include "file.h"

void h_menu_irs(
	s_arr_irs* single_table,
	s_arr_irs* unique_holder_table,
	s_arr_irs* two_holders_table)
{
	s_error* error = NULL;
	unsigned int op;

	fprintf(stdout, "%s", H_STRS_IRS_MENU);
	fprintf(stdout, GREEN("%s"), H_STRS_PROMPT);
	scanf(" %u", &op);

	switch (op)
	{
	case 1:
		error = h_irs_print(single_table);
		if (error)
			h_error_print(error);
		break;
	case 2:
		error = h_irs_edit(single_table, h_util_get_int(0, 100, H_STRS_EDIT));
		if (error)
			h_error_print(error);
		break;
	case 3:
		error = h_irs_add(single_table);
		if (error)
			h_error_print(error);
		break;
	case 4:
		error = h_irs_delete(single_table, h_util_get_int(0, 100, H_STRS_DELETE));
		if (error)
			h_error_print(error);
		break;
	case 5:
		error = h_irs_print(unique_holder_table);
		if (error)
			h_error_print(error);
		break;
	case 6:
		error = h_irs_edit(unique_holder_table, h_util_get_int(0, 100, H_STRS_EDIT));
		if (error)
			h_error_print(error);
		break;
	case 7:
		error = h_irs_add(unique_holder_table);
		if (error)
			h_error_print(error);
		break;
	case 8:
		error = h_irs_delete(unique_holder_table, h_util_get_int(0, 100, H_STRS_DELETE));
		if (error)
			h_error_print(error);
		break;
	case 9:
		error = h_irs_print(two_holders_table);
		if (error)
			h_error_print(error);
		break;
	case 10:
		error = h_irs_edit(two_holders_table, h_util_get_int(0, 100, H_STRS_EDIT));
		if (error)
			h_error_print(error);
		break;
	case 11:
		error = h_irs_add(two_holders_table);
		if (error)
			h_error_print(error);
		break;
	case 12:
		error = h_irs_delete(two_holders_table, h_util_get_int(0, 100, H_STRS_DELETE));
		if (error)
			h_error_print(error);
		break;
	case 0:
		break;
	default:
		fprintf(stdout, RED("%s"), H_STRS_INVALID_IMPUT);
		break;
	}

	h_error_free(error);
}

void h_menu_seg_social(s_arr_seg_social* seg_social_table)
{
	s_error* error = NULL;
	unsigned int op;

	fprintf(stdout, "%s", H_STRS_SEG_SOCIAL_MENU);
	fprintf(stdout, GREEN("%s"), H_STRS_PROMPT);
	scanf(" %u", &op);

	switch (op)
	{
	case 1:
		error = h_seg_social_print(seg_social_table);
		if (error)
			h_error_print(error);
		break;
	case 2:
		error = h_seg_social_add(seg_social_table);
		if (error)
			h_error_print(error);
		break;
	case 3:
		error = h_seg_social_delete(seg_social_table);
		if (error)
			h_error_print(error);
		break;
	case 4:
		error = h_seg_social_edit(seg_social_table);
		if (error)
			h_error_print(error);
		break;
	case 0:
		break;
	default:
		fprintf(stdout, RED("%s"), H_STRS_INVALID_IMPUT);
		break;
	}

	h_error_free(error);
}

void h_menu_processing(
	s_arr_irs* single_table,
	s_arr_irs* unique_holder_table,
	s_arr_irs* two_holders_table,
	s_arr_seg_social* seg_social_table
)
{
	int i;

	s_arr_files* array_files;
	s_error* error;

	array_files = h_file_ls("../data", "spreadsheet_");
	if (array_files == NULL) {
		error = h_error_create(H_ERROR_READ, "Nothing found");
		h_error_print(error);
	}

	for (i = 0; i <= array_files->used; i++)
		fprintf(stdout, RED("%s/%s\n"), array_files->files[i].parent_dir, array_files->files[i].filename);

	h_error_free(error);
}