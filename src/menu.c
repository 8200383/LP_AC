/* 
 * Created by Micael Dias on 14/12/20.
 */

#include <stdio.h>

#include "menu.h"
#include "colors.h"
#include "strs.h"
#include "util.h"

void h_menu_irs(
	s_arr_irs* single_table,
	s_arr_irs* unique_holder_table,
	s_arr_irs* two_holders_table)
{
	unsigned int op;

	fprintf(stdout, "%s", H_STRS_IRS_MENU);
	fprintf(stdout, GREEN("%s"), H_STRS_PROMPT);
	scanf(" %u", &op);

	switch (op)
	{
	case 1:
		h_irs_print(single_table);
		break;
	case 2:
		h_irs_edit(single_table, h_util_get_int(0, 100, H_STRS_EDIT));
		break;
	case 3:
		h_irs_add(single_table);
		break;
	case 4:
		h_irs_delete(single_table, h_util_get_int(0, 100, H_STRS_DELETE));
		break;
	case 5:
		h_irs_print(unique_holder_table);
		break;
	case 6:
		h_irs_edit(unique_holder_table, h_util_get_int(0, 100, H_STRS_EDIT));
		break;
	case 7:
		h_irs_add(unique_holder_table);
		break;
	case 8:
		h_irs_delete(unique_holder_table, h_util_get_int(0, 100, H_STRS_DELETE));
		break;
	case 9:
		h_irs_print(two_holders_table);
		break;
	case 10:
		h_irs_edit(two_holders_table, h_util_get_int(0, 100, H_STRS_EDIT));
		break;
	case 11:
		h_irs_add(two_holders_table);
		break;
	case 12:
		h_irs_delete(two_holders_table, h_util_get_int(0, 100, H_STRS_DELETE));
		break;
	case 0:
		break;
	default:
		fprintf(stdout, RED("%s"), H_STRS_INVALID_IMPUT);
		break;
	}
}

void h_menu_seg_social(s_arr_seg_social* seg_social_table) {
	unsigned int op;

	fprintf(stdout, "%s", H_STRS_SEG_SOCIAL_MENU);
	fprintf(stdout, GREEN("%s"), H_STRS_PROMPT);
	scanf(" %u", &op);

	switch (op)
	{
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 0:
		break;
	default:
		fprintf(stdout, RED("%s"), H_STRS_INVALID_IMPUT);
		break;
	}
}