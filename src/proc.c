#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "proc.h"
#include "calendar.h"

/*
s_sheet* h_proc_alloc()
{
	s_sheet* sheet;
	int i;

	sheet = malloc(sizeof(s_sheet));
	if (sheet == NULL)
		return NULL;

	sheet->max_capacity = 50;
	sheet->month = 0;
	sheet->used = 0;

	sheet->paysheet = malloc(sizeof(s_paysheet) * sheet->max_capacity);
	if (sheet->paysheet == NULL)
		return NULL;

	for (i = 0; i < sheet->max_capacity; i++)
	{
		sheet->paysheet[i].func_code = NULL;
		sheet->paysheet[i].full_days = 0;
		sheet->paysheet[i].half_days = 0;
		sheet->paysheet[i].weekend_days = 0;
	}

	return sheet;
}

s_error* h_proc_import(s_sheet* sheet, const char* path)
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

s_error* h_proc_export(s_sheet* sheet, const char* path)
{
	FILE* fp;

	fp = fopen(path, "wb");
	if (fp == NULL)
		return h_error_create(H_ERROR_WRITE, path);

	if (fwrite(sheet, sizeof(s_sheet), 1, fp) == 0)
		return h_error_create(H_ERROR_WRITE, path);

	return NULL;
}

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

	if (strcat(filename, "spreadsheet_") == NULL)
		return NULL;

	if (strcat(filename, month_str) == NULL)
		return NULL;

	if (strcat(filename, extension) == NULL)
		return NULL;
}
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