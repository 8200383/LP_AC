#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "proc.h"
#include "calendar.h"
#include "util.h"
#include "colors.h"
#include "strs.h"
#include "employees.h"

s_spreadsheet* h_proc_alloc(int initial_capacity)
{
	s_spreadsheet* spreadsheet;

	spreadsheet = malloc(sizeof(s_details));
	if (spreadsheet == NULL)
	{
		return NULL;
	}

	spreadsheet->details = malloc(initial_capacity * sizeof(s_details));
	if (spreadsheet->details == NULL)
	{
		return NULL;
	}

	spreadsheet->used = 0;
	spreadsheet->max_capacity = initial_capacity;

	return spreadsheet;
}

void h_proc_free(s_spreadsheet* spreadsheet)
{
	if (spreadsheet == NULL)
	{
		return;
	}

	free(spreadsheet->details);
	free(spreadsheet);
}

s_spreadsheet* h_proc_import()
{
	int month;
	char* filename;
	s_spreadsheet* spreadsheet;

	month = h_util_get_int(1, 12, "Importar Mês? (1-12)") - 1;
	filename = h_proc_generate_filename(month, ".bin");
	if (filename == NULL)
	{
		return NULL;
	}

	if (access(filename, F_OK) == 0)
	{
		puts(RED("[!] Nenhum ficheiro encontrado, nada importado"));
		free(filename);
		return NULL;
	}

	spreadsheet = h_proc_open(filename, month);
	if (spreadsheet == NULL)
	{
		free(filename);
		return NULL;
	}

	free(filename);
	return spreadsheet;
}

s_spreadsheet* h_proc_open(const char* filename, e_month month)
{
	FILE* fp;
	s_spreadsheet* spreadsheet;
	int file_size;

	fprintf(stdout, YELLOW("[!] Importing: %s\n"), filename);

	fp = fopen(filename, "rb");
	if (fp == NULL)
	{
		return NULL;
	}

	file_size = 0;
	while (!feof(fp))
	{
		file_size++;
	}

	spreadsheet = h_proc_alloc(file_size);
	if (spreadsheet == NULL)
	{
		return NULL;
	}

	spreadsheet->month = month;
	for (int i = 0; !feof(fp); i++)
	{
		if (spreadsheet->used == spreadsheet->max_capacity)
		{
			spreadsheet = realloc(spreadsheet->details, spreadsheet->max_capacity * 2);
			if (spreadsheet == NULL)
			{
				return NULL;
			}

			spreadsheet->max_capacity *= 2;
		}

		if (fread(&spreadsheet->details[i], sizeof(s_details), 1, fp) != 1)
		{
			return NULL;
		}

		spreadsheet->used++;
	}

	return spreadsheet;
}

void h_proc_add(s_spreadsheet* spreadsheet, s_arr_employees* arr_employees)
{
	int i;
	int max_days;
	int employee_index;

	if (spreadsheet == NULL)
	{
		fprintf(stdout, RED("[!] Mẽs não criado\n"));
		return;
	}

	if (arr_employees == NULL || arr_employees->used == 0)
	{
		fprintf(stdout, RED("[!] Nenhum funcionário encontrado\n"));
		return;
	}

	if (spreadsheet->used == spreadsheet->max_capacity)
	{
		spreadsheet->details = realloc(spreadsheet->details, (spreadsheet->max_capacity * 2) * sizeof(s_details));
		if (spreadsheet->details == NULL)
		{
			puts("[!] Realloc spreadshhets falhou");
			return;
		}

		spreadsheet->max_capacity *= 2;
	}

	max_days = h_calendar_days_in_month(spreadsheet->month);

	spreadsheet->used++;

	for (i = 0; i < arr_employees->used; i++)
	{
		fprintf(stdout, "[%d] %d | %s %s\n",
			i,
			arr_employees->employees[i].code,
			arr_employees->employees[i].first_name,
			arr_employees->employees[i].last_name);
	}

	employee_index = h_util_get_int(0, arr_employees->used, "Adicionar funcionário?");

	spreadsheet->details[spreadsheet->used - 1].cod_employee = arr_employees->employees[employee_index].code;
	spreadsheet->details[spreadsheet->used - 1].full_days = h_util_get_int(0, max_days, "Dias completos?");
	spreadsheet->details[spreadsheet->used - 1].half_days = h_util_get_int(0, max_days, "Meios dias?");
	spreadsheet->details[spreadsheet->used - 1].weekend_days = h_util_get_int(0, 5, "Fins de semana? (0-5)");
	spreadsheet->details[spreadsheet->used - 1].absent_days = h_util_get_int(0, max_days, "Faltas?");

}

void h_proc_print(s_spreadsheet* spreadsheet)
{
	int i;

	if (spreadsheet == NULL || spreadsheet->used == 0)
	{
		fprintf(stdout, RED("[!] Mês não criado ou vazio\n"));
		return;
	}

	fprintf(stdout, YELLOW("N Registos encontrados: %d\n"), spreadsheet->used);
	fprintf(stdout, H_STRS_PROC_TABLE_HEADER);

	for (i = 0; i < spreadsheet->used; i++)
	{
		fprintf(stdout, "[%d] %d | %d | %d | %d | %d\n",
			i,
			spreadsheet->details[i].cod_employee,
			spreadsheet->details[i].full_days,
			spreadsheet->details[i].half_days,
			spreadsheet->details[i].weekend_days,
			spreadsheet->details[i].absent_days
		);
	}
}

void h_proc_edit(s_spreadsheet* spreadsheet)
{
	int index;
	int max_days;
	int op;

	if (spreadsheet == NULL || spreadsheet->used == 0)
	{
		fprintf(stdout, RED("[!] Mês não criado ou vazio\n"));
		return;
	}

	index = h_util_get_int(0, spreadsheet->used, H_STRS_EDIT);

	fprintf(stdout, H_STRS_PROC_TABLE_HEADER);
	fprintf(stdout, "Mês: %s\n", h_calendar_str_from_month(spreadsheet->month));
	fprintf(stdout, "%d | %d | %d | %d | %d | %d\n",
		index,
		spreadsheet->details[index].cod_employee,
		spreadsheet->details[index].full_days,
		spreadsheet->details[index].half_days,
		spreadsheet->details[index].weekend_days,
		spreadsheet->details[index].absent_days
	);

	op = h_util_get_int(0, 1, "Quer editar o mês correpondente?\n 1. Sim\n 0. Não");
	if (op == 1)
	{
		spreadsheet->month = h_util_get_int(1, 12, "Novo mês?") - 1;
	}

	max_days = h_calendar_days_in_month(spreadsheet->month);
	spreadsheet->details[index].full_days = h_util_get_int(0, max_days, "Dias completos");
	spreadsheet->details[index].half_days = h_util_get_int(0, max_days, "Meios dias");
	spreadsheet->details[index].weekend_days = h_util_get_int(0, 5, "Fins de semana");
	spreadsheet->details[index].absent_days = h_util_get_int(0, max_days, "Faltas");
}

void h_proc_delete(s_spreadsheet* spreadsheet)
{
	int index;
	int i;

	if (spreadsheet == NULL || spreadsheet->used == 0)
	{
		fprintf(stdout, RED("[!] Mês não criado ou vazio\n"));
		return;
	}

	// TODO: Eliminar por cod employee, fzr pesquisa para encontrar o index
	fprintf(stdout, "Registos: %d\n", spreadsheet->used);
	index = h_util_get_int(0, spreadsheet->used, H_STRS_DELETE);

	for (i = index; i < spreadsheet->used - 1; i++)
	{
		spreadsheet->details[i] = spreadsheet->details[i + 1];
	}

	spreadsheet->used--;
}

char* h_proc_generate_filename(e_month month, const char* extension)
{
	const char* month_str;
	char* filename;

	month_str = h_calendar_str_from_month(month);
	if (month_str == NULL)
	{
		return NULL;
	}

	filename = malloc(MAX_FILENAME * sizeof(char));
	if (filename == NULL)
	{
		return NULL;
	}

	if (memset(filename, '\0', MAX_FILENAME) == NULL)
	{
		return NULL;
	}

	if (strcat(filename, "../data/spreadsheet_") == NULL)
	{
		return NULL;
	}

	if (strcat(filename, month_str) == NULL)
	{
		return NULL;
	}

	if (strcat(filename, extension) == NULL)
	{
		return NULL;
	}

	return filename;
}

void h_proc_export_csv(s_spreadsheet* spreadsheet)
{
	int i;
	FILE* fp;
	char* filename;

	if (spreadsheet->used == 0)
	{
		puts(RED("[!] Nada a exportar"));
		return;
	}

	filename = h_proc_generate_filename(spreadsheet->month, ".csv");
	if (filename == NULL)
	{
		return;
	}

	fp = fopen(filename, "w");
	if (fp == NULL)
	{
		puts(RED("[!] Impossivel exportar"));
		return;
	}

	free(filename);

	for (i = 0; i < spreadsheet->used; i++)
	{
		fprintf(fp, "%d;%d;%d;%d\n",
			spreadsheet->details[i].full_days,
			spreadsheet->details[i].half_days,
			spreadsheet->details[i].weekend_days,
			spreadsheet->details[i].absent_days);
	}

	fclose(fp);

	fprintf(stdout, YELLOW("[!] Ficheiro exportado com sucesso\n"));
}

void h_proc_perform(
	s_spreadsheet* spreadsheet,
	s_arr_irs* single_table,
	s_arr_irs* unique_holder_table,
	s_arr_irs* two_holders_table,
	s_arr_iss* seg_social_table,
	s_arr_employees* employees)
{
	int i;

	float base_salary;
	float food_allowance;

	float irs_retention;
	float ss_retention_employer;
	float ss_retention_employee;

	float ss_retention_employer_percentage; //
	float ss_retention_employee_percentage; //
	float irs_retention_percentage; //

	/*
	 * TODO
	 * Se o employee for divorciado usar single_table
	 * Se o employee for casado e unico titular usar unique_holder_table
	 * Se o employee for casado e dois titular usar two_holders_table
	 */
	// TODO: Atenção que as tabelas podem não estar carregadas
	/*
	if (irs_array->used == 0 || ss_array->used == 0 || employees->used == 0)
	{
		return;
	} */

	for (i = 0; i < spreadsheet->used; i++)
	{
		//Falta definir as constantes do sálario de acordo com o cargo do trabalhador.
		base_salary = (float)spreadsheet->details[i].full_days * 40 +
			(float)spreadsheet->details[i].half_days * 40 / 2.0f +
			(float)spreadsheet->details[i].weekend_days * 40 * 1.5f;

		//Falta definir as constantes do subsídio da alimentação de acordo com o cargo do trabalhador.
		food_allowance = (float)spreadsheet->details[i].full_days * 5 +
			(float)spreadsheet->details[i].weekend_days * 5;

		//Falta aceder aos dados dos trabalhadores para determinar o escalão de IRS.
		//irs_retention_percentage = irs_array->elements[i].monthly_pay_value / 100.0f;
		//irs_retention = (base_salary + food_allowance) * irs_retention_percentage;

		//Falta aceder aos dados dos trabalhadores para determinar as percentagens de descontos da SS.
		ss_retention_employer_percentage = seg_social_table->data[i].employer / 100.0f;
		ss_retention_employee_percentage = seg_social_table->data[i].employee / 100.0f;

		ss_retention_employer = (base_salary + food_allowance) * ss_retention_employer_percentage;
		ss_retention_employee = (base_salary + food_allowance) * ss_retention_employee_percentage;

		//printf("\nSalário Líquido: %.2f€\n", (base_salary + food_allowance) - irs_retention - ss_retention_employee);
		//printf("Encargo Total (Empregador): %.2f€\n", (base_salary + food_allowance) + irs_retention + ss_retention_employee + ss_retention_employer);
	}
}
