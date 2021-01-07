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
		return NULL;

	spreadsheet->details = malloc(initial_capacity * sizeof(s_details));
	if (spreadsheet->details == NULL)
		return NULL;

	spreadsheet->used = -1;
	spreadsheet->max_capacity = initial_capacity;

	return spreadsheet;
}

void h_proc_free(s_spreadsheet* spreadsheet)
{
	if (spreadsheet == NULL)
		return;

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
		return NULL;

	if (access(filename, F_OK) == -1)
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
		return NULL;

	file_size = 0;
	while (!feof(fp))
		file_size++;

	spreadsheet = h_proc_alloc(file_size);
	if (spreadsheet == NULL)
		return NULL;

	spreadsheet->month = month;
	for (int i = 0; !feof(fp); i++)
	{
		if (spreadsheet->used == spreadsheet->max_capacity)
		{
			spreadsheet = realloc(spreadsheet->details, spreadsheet->max_capacity * 2);
			if (spreadsheet == NULL)
				return NULL;

			spreadsheet->max_capacity *= 2;
		}

		if (fread(&spreadsheet->details[i], sizeof(s_details), 1, fp) != 1)
			return NULL;

		spreadsheet->used++;
	}

	return spreadsheet;
}

void h_proc_add(s_spreadsheet* spreadsheet)
{
	int max_days;

	if (spreadsheet == NULL)
	{
		fprintf(stdout, RED("[!] Mẽs não criado\n"));
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

	// TODO: a soma dos numeros nao pode exeder o max_days, quer dizer que poz mais dias do que o mês tem
	spreadsheet->details[spreadsheet->used].full_days = h_util_get_int(0, max_days, "Dias completos");
	spreadsheet->details[spreadsheet->used].half_days = h_util_get_int(0, max_days, "Meios dias");
	// TODO: Um mês tem 4 fins de semana mais o menos
	spreadsheet->details[spreadsheet->used].weekend_days = h_util_get_int(0, max_days, "Fins de semana");
	spreadsheet->details[spreadsheet->used].absent_days = h_util_get_int(0, max_days, "Faltas");

}

void h_proc_print(s_spreadsheet* spreadsheet)
{
	int i;

	if (spreadsheet == NULL || spreadsheet->used == -1)
	{
		fprintf(stdout, RED("[!] Mês não criado ou vazio\n"));
		return;
	}

	fprintf(stdout, YELLOW("N Registos encontrados: %d\n"), spreadsheet->used);
	fprintf(stdout, H_STRS_PROC_TABLE_HEADER);

	for (i = 0; i <= spreadsheet->used; i++)
	{
		fprintf(stdout, "%d | %d | %d | %d | %d | %d\n",
			i,
			1,
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

	if (spreadsheet == NULL || spreadsheet->used == -1)
	{
		fprintf(stdout, RED("[!] Mês não criado ou vazio\n"));
		return;
	}

	// TODO: Editar por cod employee, fzr pesquisa para encontrar o index
	index = h_util_get_int(0, spreadsheet->used, H_STRS_EDIT);
	if (spreadsheet->used < index)
	{
		fprintf(stdout, RED("[!] Nada para editar\n"));
		return;
	}

	fprintf(stdout, H_STRS_PROC_TABLE_HEADER);
	fprintf(stdout, "%d | %d | %d | %d | %d | %d\n",
		index,
		1,
		spreadsheet->details[index].full_days,
		spreadsheet->details[index].half_days,
		spreadsheet->details[index].weekend_days,
		spreadsheet->details[index].absent_days
	);

	max_days = h_calendar_days_in_month(spreadsheet->month);
	// TODO: dar possiblidade editar mes tbm
	spreadsheet->details[index].full_days = h_util_get_int(0, max_days, "Dias completos");
	spreadsheet->details[index].half_days = h_util_get_int(0, max_days, "Meios dias");
	// TODO: Um mês tem 4 fins de semana mais o menos
	spreadsheet->details[index].weekend_days = h_util_get_int(0, max_days, "Fins de semana");
	spreadsheet->details[index].absent_days = h_util_get_int(0, max_days, "Faltas");
}

void h_proc_delete(s_spreadsheet* spreadsheet)
{
	int index;
	int i;

	if (spreadsheet == NULL || spreadsheet->used == -1)
	{
		fprintf(stdout, RED("[!] Mês não criado ou vazio\n"));
		return;
	}

	// TODO: Eliminar por cod employee, fzr pesquisa para encontrar o index
	index = h_util_get_int(0, spreadsheet->used, H_STRS_DELETE);
	if (spreadsheet->used < index)
	{
		fprintf(stdout, RED("[!] Nada para eliminar\n"));
		return;
	}

	for (i = index; i <= spreadsheet->used - 1; i++)
		spreadsheet->details[i] = spreadsheet->details[i + 1];

	spreadsheet->used--;
}

char* h_proc_generate_filename(e_month month, const char* extension)
{
	const char* month_str;
	char* filename;

	month_str = h_calendar_str_from_month(month);
	if (month_str == NULL)
		return NULL;

	filename = malloc(MAX_FILENAME * sizeof(char));
	if (filename == NULL)
		return NULL;

	if (memset(filename, '\0', MAX_FILENAME) == NULL)
		return NULL;

	if (strcat(filename, "../data/spreadsheet_") == NULL)
		return NULL;

	if (strcat(filename, month_str) == NULL)
		return NULL;

	if (strcat(filename, extension) == NULL)
		return NULL;

	return filename;
}

void h_proc_export_csv(s_spreadsheet* spreadsheet)
{
	int i;
	FILE* fp;
	char* filename;

	if (spreadsheet->used == -1)
	{
		puts(RED("[!] Nada a exportar"));
		return;
	}

	filename = h_proc_generate_filename(spreadsheet->month, ".csv");
	if (filename == NULL)
		return;

	fp = fopen(filename, "w");
	if (fp == NULL)
	{
		puts(RED("[!] Impossivel exportar"));
		return;
	}

	free(filename);

	for (i = 0; i <= spreadsheet->used; i++)
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

void h_proc_perform(s_spreadsheet* spreadsheet, s_arr_irs* irs_array, s_arr_seg_social* ss_array, s_arr_employees* employees_array)
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

	if (irs_array->used == 0 || ss_array->used == 0 || employees_array->used == 0)
		return;

	for (i = 0; i <= spreadsheet->used; i++)
	{
		//Falta definir as constantes do sálario de acordo com o cargo do trabalhador.
		base_salary = (float)spreadsheet->details[i].full_days * 40 +
					  (float)spreadsheet->details[i].half_days * 40 / 2.0f +
					  (float)spreadsheet->details[i].weekend_days * 40 * 1.5f;

		//Falta definir as constantes do subsídio da alimentação de acordo com o cargo do trabalhador.
		food_allowance = (float)spreadsheet->details[i].full_days * 5 +
						 (float)spreadsheet->details[i].weekend_days * 5;

		//Falta aceder aos dados dos trabalhadores para determinar o escalão de IRS.
		irs_retention_percentage = irs_array->data[i].monthly_pay_value / 100.0f;
		irs_retention = (base_salary + food_allowance) * irs_retention_percentage;

		//Falta aceder aos dados dos trabalhadores para determinar as percentagens de descontos da SS.
		ss_retention_employer_percentage = ss_array->data[i].employer / 100.0f;
		ss_retention_employee_percentage = ss_array->data[i].employee / 100.0f;

		ss_retention_employer = (base_salary + food_allowance) * ss_retention_employer_percentage;
		ss_retention_employee = (base_salary + food_allowance) * ss_retention_employee_percentage;

		printf("\nSalário Líquido: %.2f€\n", (base_salary + food_allowance) - irs_retention - ss_retention_employee);
		printf("Encargo Total (Empregador): %.2f€\n",
			(base_salary + food_allowance) + irs_retention + ss_retention_employee + ss_retention_employer);
	}
}
