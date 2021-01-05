#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "proc.h"
#include "calendar.h"
#include "util.h"
#include "colors.h"
#include "strs.h"

s_arr_spreadsheets* h_proc_alloc(int initial_capacity)
{
	s_arr_spreadsheets* arr_spreadsheets;
	int i;

	arr_spreadsheets = malloc(sizeof(s_spreadsheet));
	if (arr_spreadsheets == NULL)
		return NULL;

	arr_spreadsheets->spreadsheets = malloc(initial_capacity * sizeof(s_spreadsheet));
	if (arr_spreadsheets->spreadsheets == NULL)
		return NULL;

	arr_spreadsheets->used = 0;
	arr_spreadsheets->max_capacity = initial_capacity;

	for (i = 0; i <= arr_spreadsheets->max_capacity; i++)
	{
		arr_spreadsheets->spreadsheets[i].weekend_days = 0;
		arr_spreadsheets->spreadsheets[i].half_days = 0;
		arr_spreadsheets->spreadsheets[i].full_days = 0;
		arr_spreadsheets->spreadsheets[i].absent_days = 0;
	}

	return arr_spreadsheets;
}

void h_proc_free(s_arr_spreadsheets* array)
{
	if (array == NULL)
		return;

	free(array->spreadsheets);
	free(array);
}

s_arr_spreadsheets* h_proc_open(const char* filename)
{
	FILE* fp;
	s_arr_spreadsheets* array;
	int file_size;

	fprintf(stdout, YELLOW("[!] Importing: %s\n"), filename);

	fp = fopen(filename, "rb");
	if (fp == NULL)
		return NULL;

	file_size = 0;
	while (!feof(fp))
		file_size++;

	array = h_proc_alloc(file_size);
	if (array == NULL)
		return NULL;

	for (int i = 0; !feof(fp); i++)
	{
		if (array->used == array->max_capacity)
		{
			array = realloc(array->spreadsheets, array->max_capacity * 2);
			if (array == NULL)
				return NULL;

			array->max_capacity *= 2;
		}

		if (fread(&array->spreadsheets[i], sizeof(s_spreadsheet), 1, fp) != 1)
			return NULL;

		array->used++;
	}

	return array;
}

void h_proc_scan_fields(s_spreadsheet* spreadsheet, e_month month)
{
	spreadsheet->full_days = h_util_get_int(1, h_calendar_days_in_month(month), "Dias completos");
	spreadsheet->half_days = h_util_get_int(1, h_calendar_days_in_month(month), "Meios dias");
	// TODO: Um mês tem 4 fins de semana mais o menos
	spreadsheet->weekend_days = h_util_get_int(1, h_calendar_days_in_month(month), "Fins de semana");
	spreadsheet->absent_days = h_util_get_int(1, h_calendar_days_in_month(month), "Faltas");
}

void h_proc_add(s_arr_spreadsheets* array, e_month month)
{
	if (array->used == array->max_capacity)
	{
		array->spreadsheets = realloc(array->spreadsheets, (array->max_capacity * 2) * sizeof(s_spreadsheet));
		if (array->spreadsheets == NULL)
		{
			puts("Alloc spreadshhets falhou");
			return;
		}

		array->max_capacity *= 2;
	}

	h_proc_scan_fields(&array->spreadsheets[array->used++], month);
}

void h_proc_print(s_arr_spreadsheets* array)
{
	int i;

	if (array->used == 0)
	{
		puts("Nothing to print");
		return;
	}

	fprintf(stdout, YELLOW("N Registos encontrados: %d\n"), array->used);
	fprintf(stdout, H_STRS_PROC_TABLE_HEADER);

	for (i = 0; i < array->used; i++)
	{
		fprintf(stdout, "%d | %d | %d | %d | %d | %d\n",
			i,
			1,
			array->spreadsheets[i].full_days,
			array->spreadsheets[i].half_days,
			array->spreadsheets[i].weekend_days,
			array->spreadsheets[i].absent_days
		);
	}
}

void h_proc_edit(s_arr_spreadsheets* array, e_month month)
{
	int index;

	if (array->used == 0)
	{
		puts("[!] Nada para editar");
		return;
	}

	index = h_util_get_int(0, array->used, H_STRS_EDIT);

	fprintf(stdout, H_STRS_PROC_TABLE_HEADER);
	// TODO: Mostrar linha antiga

	h_proc_scan_fields(&array->spreadsheets[index], month);
}

void h_proc_delete(s_arr_spreadsheets* array)
{
	int index;
	int i;

	index = h_util_get_int(0, array->used, H_STRS_DELETE);

	if (array->used == 0 || array->used < index)
	{
		puts("[!] Nada para eliminar");
		return;
	}

	for (i = index; i <= array->used - 1; i++)
		array->spreadsheets[i] = array->spreadsheets[i + 1];

	array->used--;
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
}

/*
s_error* h_proc_export_csv(s_sheet* sheet, const char* path)
{
	int i;
	FILE* fp;

	fp = fopen(path, "w");
	if (fp == NULL)
		return h_error_create(H_ERROR_WRITE, path);

	for (i = 0; i <= sheet->used; i++)
	{
		fprintf(fp, "%s;%d;%d;%d;%d;\n",
			sheet->paysheet[i].func_code,
			sheet->paysheet[i].full_days,
			sheet->paysheet[i].half_days,
			sheet->paysheet[i].weekend_days,
			sheet->paysheet[i].absent_days);
	}

	fclose(fp);
	return NULL;
}*/

/*
s_error* h_processing(s_sheet* sheet, s_arr_irs irs_array, s_arr_seg_social ss_array)
{
	int i, j, k;
	float base_salary, food_allowance, irs_retention, ss_retention_employer, ss_retention_employee;
	float irs_retention_percentage = 0, ss_retention_employer_percentage, ss_retention_employee_percentage;

	for (i = 0; i <= sheet->used; i++)
	{
		//Falta definir as constantes do sálario de acordo com o cargo do trabalhador.
		base_salary = sheet->paysheet[i].full_days * 40 + (sheet->paysheet[i].half_days * 40) / 2
					  + (sheet->paysheet[i].weekend_days * 40) * 1.5;
		//Falta definir as constantes do subsídio da alimentação de acordo com o cargo do trabalhador.
		food_allowance = sheet->paysheet[i].full_days * 5 + sheet->paysheet[i].weekend_days * 5;

		//Falta aceder aos dados dos trabalhadores para determinar o escalão de IRS.
		irs_retention_percentage = irs_array.data[i].monthly_pay_value / 100;
		irs_retention = (base_salary + food_allowance) * irs_retention_percentage;

		//Falta aceder aos dados dos trabalhadores para determinar as percentagens de descontos da SS.
		ss_retention_employer_percentage = ss_array.data[i].employer / 100;
		ss_retention_employee_percentage = ss_array.data[i].employee / 100;

		ss_retention_employer = (base_salary + food_allowance) * ss_retention_employer_percentage;
		ss_retention_employee = (base_salary + food_allowance) * ss_retention_employee_percentage;
	}

	printf("\nSalário Ilíquido: %.2f€\n", base_salary);
	printf("Subsídio da Alimentação: %.2f€\n", food_allowance);

	printf("\nRetenção IRS: %.2f€\n", irs_retention);
	printf("Retenção SS (Empregador): %.2f€\n", ss_retention_employer);
	printf("Retenção SS (Empregado): %.2f€\n", ss_retention_employee);

	printf("\nSalário Líquido: %.2f€\n", (base_salary + food_allowance) - irs_retention - ss_retention_employee);
	printf("Encargo Total (Empregador): %.2f€\n",
		(base_salary + food_allowance) + irs_retention + ss_retention_employee + ss_retention_employer);
	return NULL;
}*/