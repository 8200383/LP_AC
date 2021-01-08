#include <stdio.h>
#include <stdlib.h>

#include "menu.h"
#include "colors.h"
#include "strs.h"
#include "util.h"
#include "proc.h"
#include "paths.h"

void h_menu_irs(
	s_arr_irs* single_table,
	s_arr_irs* unique_holder_table,
	s_arr_irs* two_holders_table)
{
	int op;

	int single_size = 0;
	char* single_str;

	int unique_holder_size = 0;
	char* unique_holder_str;

	int two_holders_size = 0;
	char* two_holders_str;

	fprintf(stdout, H_STRS_IRS_MENU);

	do
	{
		fprintf(stdout, GREEN("%s"), H_STRS_PROMPT);
		op = h_util_get_int(0, 18, "Opção?");

		switch (op)
		{
		case 1:
			single_str = h_util_file_read(H_PATH_SINGLE, &single_size);
			if (single_str == NULL)
			{
				fprintf(stdout, RED("[!] Impossivel carregar %s"), H_PATH_SINGLE);
				return;
			}
			if (single_table->used > 0)
			{
				fprintf(stdout, RED("[!] Já existe dados na tabela, overide...\n"));
				h_irs_delete_all(single_table);
			}
			h_irs_parse(single_table, single_str, h_irs_pair);
			free(single_str);
			break;
		case 2:
			h_irs_print(single_table);
			break;
		case 3:
			h_irs_edit(single_table);
			break;
		case 4:
			h_irs_add(single_table);
			break;
		case 5:
			h_irs_delete(single_table);
			break;
		case 6:
			h_irs_write(single_table, H_PATH_SINGLE);
			break;
		case 7:
			unique_holder_str = h_util_file_read(H_PATH_UNIQUE_HOLDER, &unique_holder_size);
			if (unique_holder_str == NULL)
			{
				fprintf(stdout, RED("[!] Impossivel carregar %s"), H_PATH_UNIQUE_HOLDER);
				return;
			}
			if (single_table->used > 0)
			{
				fprintf(stdout, RED("[!] Já existe dados na tabela, overide...\n"));
				h_irs_delete_all(single_table);
			}
			h_irs_parse(unique_holder_table, unique_holder_str, h_irs_pair);
			free(unique_holder_str);
			break;
		case 8:
			h_irs_print(unique_holder_table);
			break;
		case 9:
			h_irs_edit(unique_holder_table);
			break;
		case 10:
			h_irs_add(unique_holder_table);
			break;
		case 11:
			h_irs_delete(unique_holder_table);
			break;
		case 12:
			h_irs_write(unique_holder_table, H_PATH_UNIQUE_HOLDER);
			break;
		case 13:
			two_holders_str = h_util_file_read(H_PATH_TWO_HOLDERS, &two_holders_size);
			if (unique_holder_str == NULL)
			{
				fprintf(stdout, RED("[!] Impossivel carregar %s"), H_PATH_TWO_HOLDERS);
				return;
			}
			if (single_table->used > 0)
			{
				fprintf(stdout, RED("[!] Já existe dados na tabela, overide...\n"));
				h_irs_delete_all(single_table);
			}
			h_irs_parse(two_holders_table, two_holders_str, h_irs_pair);
			free(two_holders_str);
			break;
		case 14:
			h_irs_print(two_holders_table);
			break;
		case 15:
			h_irs_edit(two_holders_table);
			break;
		case 16:
			h_irs_add(two_holders_table);
			break;
		case 17:
			h_irs_delete(two_holders_table);
			break;
		case 18:
			h_irs_write(two_holders_table, H_PATH_TWO_HOLDERS);
			break;
		case 0:
			break;
		default:
			fprintf(stdout, RED("%s"), H_STRS_INVALID_IMPUT);
			break;
		}
	} while (op != 0);
}

void h_menu_seg_social(s_arr_iss* seg_social_table)
{
	int op;
	int social_sec_size = 0;
	char* social_sec_str;

	do
	{
		fprintf(stdout, H_STRS_SEG_SOCIAL_MENU);
		op = h_util_get_int(0, 6, "Opção: ");

		switch (op)
		{
		case 1:
			social_sec_str = h_util_file_read(H_PATH_SEG_SOCIAL, &social_sec_size);
			if (social_sec_str == NULL)
			{
				printf(RED("[!] Impossivel carregar %s"), H_PATH_SEG_SOCIAL);
				return;
			}
			if (seg_social_table->used > 0)
			{
				printf(RED("[!] Já existem dados na tabela. Os novos dados foram carregados.\n"));
				h_iss_delete_all(seg_social_table);
			}
			h_iss_parse(seg_social_table, social_sec_str);
			free(social_sec_str);
			break;
		case 2:
			h_iss_print(seg_social_table);
			break;
		case 3:
			h_iss_add(seg_social_table);
			break;
		case 4:
			h_iss_delete(seg_social_table);
			break;
		case 5:
			h_iss_edit(seg_social_table);
			break;
		case 6:
			h_iss_write(seg_social_table, H_PATH_SEG_SOCIAL);
			break;
		case 0:
			break;
		default:
			fprintf(stdout, RED("%s"), H_STRS_INVALID_IMPUT);
			break;
		}
	} while (op != 0);
}

void h_menu_processing(
	s_arr_irs* single_table,
	s_arr_irs* unique_holder_table,
	s_arr_irs* two_holders_table,
	s_arr_iss* seg_social_table,
	s_arr_employees* employees
)
{
	int op;
	s_spreadsheet* spreadsheet = NULL;


	fprintf(stdout, H_STRS_PROC);
	do
	{
		op = h_util_get_int(0, 10, "Opção?");

		switch (op)
		{
		case 1:
			if (spreadsheet)
			{
				fprintf(stdout, RED("[!] Mês %s já criado\n"), h_calendar_str_from_month(spreadsheet->month));
				break;
			}

			spreadsheet = h_proc_alloc(64); // TODO: alloc com a qte de func
			if (spreadsheet == NULL)
			{
				fprintf(stdout, RED("[!] Memória insuficiente\n"));
				return;
			}

			spreadsheet->month = h_util_get_int(1, 12, "Mês: (1-12)") - 1;
			fprintf(stdout, GREEN("[!] Mês de %s criado com sucesso\n"),
				h_calendar_str_from_month(spreadsheet->month));
			break;
		case 2:
			h_proc_print(spreadsheet);
			break;
		case 3:
			h_proc_add(spreadsheet, employees);
			break;
		case 4:
			h_proc_edit(spreadsheet);
			break;
		case 5:
			h_proc_delete(spreadsheet);
			break;
		case 6:
			break;
		case 7:
			h_proc_export_csv(spreadsheet);
			break;
		case 8:
			break;
		case 9:
			if (spreadsheet)
			{
				fprintf(stdout, RED("[!] Já existia %s, este sera eliminado\n"),
					h_calendar_str_from_month(spreadsheet->month));
				free(spreadsheet);
			}
			spreadsheet = h_proc_import();
			break;
		case 10:
			fprintf(stdout, RED("[!] Apagar mês de %s...\n"), h_calendar_str_from_month(spreadsheet->month));
			h_proc_free(spreadsheet);
			break;
		case 0:
			break;
		default:
			fprintf(stdout, RED("%s"), H_STRS_INVALID_IMPUT);
			break;
		}
	} while (op != 0);

	if (spreadsheet)
		h_proc_free(spreadsheet);
}

void h_menu_employees(s_arr_employees* employees)
{
	int op;

	fprintf(stdout, H_STRS_EMPLOYEES_MENU);
	do
	{
		op = h_util_get_int(0, 5, "Opção?");

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
	} while (op != 0);
}
