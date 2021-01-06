#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "menu.h"
#include "colors.h"
#include "strs.h"
#include "util.h"
#include "proc.h"

void h_menu_irs(
	s_arr_irs* single_table,
	s_arr_irs* unique_holder_table,
	s_arr_irs* two_holders_table)
{
	unsigned int op;

	fprintf(stdout, H_STRS_IRS_MENU);
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

void h_menu_seg_social(s_arr_seg_social* seg_social_table)
{
	unsigned int op;

	fprintf(stdout, H_STRS_SEG_SOCIAL_MENU);
	fprintf(stdout, GREEN("%s"), H_STRS_PROMPT);
	scanf(" %u", &op);

	switch (op)
	{
	case 1:
		h_seg_social_print(seg_social_table);
		break;
	case 2:
		h_seg_social_add(seg_social_table);
		break;
	case 3:
		h_seg_social_delete(seg_social_table);
		break;
	case 4:
		h_seg_social_edit(seg_social_table);
		break;
	case 0:
		break;
	default:
		fprintf(stdout, RED("%s"), H_STRS_INVALID_IMPUT);
		break;
	}
}

void h_menu_processing(
	s_arr_irs* single_table,
	s_arr_irs* unique_holder_table,
	s_arr_irs* two_holders_table,
	s_arr_seg_social* seg_social_table
)
{
	int op;
	s_arr_spreadsheets* arr_spreadsheets = NULL;

	do
	{
		fprintf(stdout, H_STRS_PROC);
		fprintf(stdout, GREEN("%s"), H_STRS_PROMPT);
		scanf(" %u", &op);

		switch (op)
		{
		case 1:
			if (arr_spreadsheets)
			{ // TODO: Adicionar opção para apagar mês
				fprintf(stdout, RED("[!] Mês %s já criado\n"), h_calendar_str_from_month(arr_spreadsheets->month));
				break;
			}

			arr_spreadsheets = h_proc_alloc(64); // TODO: alloc com a qte de func
			if (arr_spreadsheets == NULL)
			{
				fprintf(stdout, RED("[!] Memória insuficiente\n"));
				return;
			}

			arr_spreadsheets->month = h_util_get_int(1, 12, "Mês: (1-12)") - 1;
			fprintf(stdout, GREEN("[!] Mês de %s criado com sucesso\n"),
				h_calendar_str_from_month(arr_spreadsheets->month));
			break;
		case 2:
			h_proc_print(arr_spreadsheets);
			break;
		case 3:
			h_proc_add(arr_spreadsheets);
			break;
		case 4:
			h_proc_edit(arr_spreadsheets);
			break;
		case 5:
			h_proc_delete(arr_spreadsheets);
			break;
		case 6:
			break;
		case 7:
			h_proc_export_csv(arr_spreadsheets);
			break;
		case 8:
			break;
		case 9:
			if (arr_spreadsheets)
				free(arr_spreadsheets);

			arr_spreadsheets = h_proc_import();
			break;
		case 0:
			break;
		default:
			fprintf(stdout, RED("%s"), H_STRS_INVALID_IMPUT);
			break;
		}
	} while (op != 0);

	h_proc_free(arr_spreadsheets);
}

void h_menu_employees(s_arr_employees* employees)
{
	int op;

	fprintf(stdout, H_STRS_EMPLOYEES_MENU);
	fprintf(stdout, GREEN("%s"), H_STRS_PROMPT);
	scanf(" %u", &op);

	switch (op)
	{
	case 1:
		h_employees_print(employees);
		break;
	case 2:
		h_employees_add(employees);
		break;
	case 3:
		printf("Remove employee");
		break;
	case 4:
		printf("Edit employee");
		break;
	case 0:
		break;
	default:
		fprintf(stdout, RED("%s"), H_STRS_INVALID_IMPUT);
		break;
	}
}