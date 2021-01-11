#include <stdio.h>
#include <stdlib.h>

#include "menu.h"
#include "reports.h"

void h_menu_irs(
	s_arr_irs* single_array,
	s_arr_irs* unique_holder_array,
	s_arr_irs* two_holders_array)
{
	int op;

	int single_size = 0;
	char* single_str;

	int unique_holder_size = 0;
	char* unique_holder_str;

	int two_holders_size = 0;
	char* two_holders_str;

	do
	{
		fprintf(stdout, H_STRS_IRS_MENU);
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
				if (single_array->used > 0)
				{
					fprintf(stdout, RED("[!] Já existe dados na tabela, overide...\n"));
					h_irs_delete_all(single_array);
				}
				h_irs_parse(single_array, single_str, h_irs_pair);
				free(single_str);
				// TODO: mostrar que foi carregada
				break;
			case 2:
				h_irs_print(single_array);
				break;
			case 3:
				h_irs_edit(single_array);
				break;
			case 4:
				h_irs_add(single_array);
				break;
			case 5:
				h_irs_delete(single_array);
				break;
			case 6:
				h_irs_write(single_array, H_PATH_SINGLE);
				break;
			case 7:
				unique_holder_str = h_util_file_read(H_PATH_UNIQUE_HOLDER, &unique_holder_size);
				if (unique_holder_str == NULL)
				{
					fprintf(stdout, RED("[!] Impossivel carregar %s"), H_PATH_UNIQUE_HOLDER);
					return;
				}
				if (unique_holder_array->used > 0)
				{
					fprintf(stdout, RED("[!] Já existe dados na tabela, overide...\n"));
					h_irs_delete_all(unique_holder_array);
				}
				h_irs_parse(unique_holder_array, unique_holder_str, h_irs_pair);
				free(unique_holder_str);
				break;
			case 8:
				h_irs_print(unique_holder_array);
				break;
			case 9:
				h_irs_edit(unique_holder_array);
				break;
			case 10:
				h_irs_add(unique_holder_array);
				break;
			case 11:
				h_irs_delete(unique_holder_array);
				break;
			case 12:
				h_irs_write(unique_holder_array, H_PATH_UNIQUE_HOLDER);
				break;
			case 13:
				two_holders_str = h_util_file_read(H_PATH_TWO_HOLDERS, &two_holders_size);
				if (two_holders_str == NULL)
				{
					fprintf(stdout, RED("[!] Impossivel carregar %s"), H_PATH_TWO_HOLDERS);
					return;
				}
				if (two_holders_array->used > 0)
				{
					fprintf(stdout, RED("[!] Já existe dados na tabela, overide...\n"));
					h_irs_delete_all(two_holders_array);
				}
				h_irs_parse(two_holders_array, two_holders_str, h_irs_pair);
				free(two_holders_str);
				break;
			case 14:
				h_irs_print(two_holders_array);
				break;
			case 15:
				h_irs_edit(two_holders_array);
				break;
			case 16:
				h_irs_add(two_holders_array);
				break;
			case 17:
				h_irs_delete(two_holders_array);
				break;
			case 18:
				h_irs_write(two_holders_array, H_PATH_TWO_HOLDERS);
				break;
			case 0:
				break;
			default:
				fprintf(stdout, RED("%s"), H_STRS_INVALID_IMPUT);
				break;
		}
	} while (op != 0);
}

void h_menu_iss(s_arr_iss* iss_array)
{
	int op;

	do
	{
		fprintf(stdout, H_STRS_SEG_SOCIAL_MENU);
		op = h_util_get_int(0, 6, "Opção?");

		switch (op)
		{
			case 1:
				h_iss_load(iss_array);
				break;
			case 2:
				h_iss_print(iss_array);
				break;
			case 3:
				h_iss_add(iss_array);
				break;
			case 4:
				h_iss_delete(iss_array);
				break;
			case 5:
				h_iss_edit(iss_array);
				break;
			case 6:
				h_iss_write(iss_array, H_PATH_SEG_SOCIAL);
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
	s_arr_irs* single_array,
	s_arr_irs* unique_holder_array,
	s_arr_irs* two_holders_array,
	s_arr_iss* iss_array,
	s_arr_employees* employees_array,
	s_spreadsheet* spreadsheet
)
{
	int op;

	do
	{
		fprintf(stdout, H_STRS_PROC);
		op = h_util_get_int(0, 9, "Opção?");

		switch (op)
		{
			case 1:
				if (spreadsheet)
				{
					fprintf(stdout, RED("[!] Mês %s já criado\n"), h_calendar_str_from_month(spreadsheet->month));
					break;
				}

				spreadsheet = h_proc_alloc(employees_array->used);
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
				h_proc_add(spreadsheet, employees_array);
				break;
			case 4:
				h_proc_edit(spreadsheet);
				break;
			case 5:
				h_proc_delete(spreadsheet);
				break;
			case 6:
				h_proc_perform(spreadsheet,
					single_array,
					unique_holder_array,
					two_holders_array,
					iss_array,
					employees_array);
				break;
			case 7:
				h_proc_export_csv(spreadsheet);
				break;
			case 8:
				h_proc_write(spreadsheet, h_proc_generate_filename(spreadsheet->month, ".bin"));
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
			case 0:
				break;
			default:
				fprintf(stdout, RED("%s"), H_STRS_INVALID_IMPUT);
				break;
		}
	} while (op != 0);

	if (spreadsheet)
	{
		h_proc_free(spreadsheet);
	}
}

void h_menu_employees(s_arr_employees* employees_array, s_arr_iss* iss_array)
{
	int op;
	int employees_size = 0;
	char* employees_str;

	do
	{
		printf(H_STRS_EMPLOYEES_MENU);
		op = h_util_get_int(0, 6, "Opção?");

		switch (op)
		{
			case 1:
				if (iss_array == NULL || iss_array->used == 0)
				{
					puts(YELLOW("[!] A tabela da ISS sera carregada automaticamente"));
					h_iss_load(iss_array);
				}

				employees_str = h_util_file_read(H_PATH_EMPLOYEES, &employees_size);
				if (employees_str == NULL)
				{
					printf(RED("[!] Impossivel carregar %s"), H_PATH_EMPLOYEES);
					break;
				}

				if (employees_array->used > 0)
				{
					printf(RED("[!] Já existem dados na tabela. Os novos dados foram carregados.\n"));
					// TODO: h_employess_delete_all(employees_array);
				}
				h_employees_parse(employees_array, employees_str);
				free(employees_str);
				break;
			case 2:
				h_employees_print(employees_array, iss_array);
				break;
			case 3:
				h_employees_add(employees_array, iss_array);
				break;
			case 4:
				h_employees_delete(employees_array);
				break;
			case 5:
				h_employees_edit(employees_array, iss_array);
				break;
			case 6:
				h_employees_save(employees_array, H_PATH_EMPLOYEES);
				break;
			case 0:
				break;
			default:
				printf(RED("%s"), H_STRS_INVALID_IMPUT);
				break;
		}
	} while (op != 0);
}

void h_menu_reports(s_arr_employees* employees_array, s_spreadsheet* spreadsheet)
{
	int op;

	do
	{
		fprintf(stdout, H_STRS_REPORTS_MENU);
		op = h_util_get_int(0, 2, "Opção?");
		switch (op)
		{
			case 1:
				h_reports_senior_employees(employees_array);
				break;
			case 2:
				h_reports_marital_percentage(employees_array);
				break;
			case 3:
				h_reports_bonus(spreadsheet);
			case 0:
				break;
			default:
				printf(RED("%s"), H_STRS_INVALID_IMPUT);
				break;
		}
	} while (op != 0);
}