#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "proc.h"

#define INITIAL_CAPACITY 50

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

	spreadsheet->month_is_set = 0;
	spreadsheet->is_processed = 0;
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

	if (access(filename, F_OK) == -1)
	{
		printf(RED("[!] Ficheiro %s não encontrado\n"), filename);
		free(filename);
		return NULL;
	}

	spreadsheet = h_proc_read(filename, month);
	if (spreadsheet == NULL)
	{
		free(filename);
		return NULL;
	}

	free(filename);
	return spreadsheet;
}

s_spreadsheet* h_proc_read(const char* filename, e_month month)
{
	FILE* fp;
	s_spreadsheet* spreadsheet;

	fprintf(stdout, YELLOW("[!] Importing: %s\n"), filename);

	fp = fopen(filename, "rb");
	if (fp == NULL)
	{
		return NULL;
	}

	spreadsheet = h_proc_alloc(INITIAL_CAPACITY);
	if (spreadsheet == NULL)
	{
		return NULL;
	}

	spreadsheet->month = month;
	spreadsheet->month_is_set = 1;

	while (fread(spreadsheet->details, sizeof(s_details), 1, fp))
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

		spreadsheet->used++;
	}

	return spreadsheet;
}

// TODO: não pode adicionar o mesmo employee duas vezes
void h_proc_add(s_spreadsheet* spreadsheet, s_arr_employees* arr_employees)
{
	int i;
	int max_days;
	int employee_index;

    if (spreadsheet->month_is_set == 0)
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
			arr_employees->employees[i].cod_employee,
			arr_employees->employees[i].first_name,
			arr_employees->employees[i].last_name);
	}

	employee_index = h_util_get_int(0, arr_employees->used - 1, "Adicionar funcionário?");

	spreadsheet->details[spreadsheet->used - 1].cod_employee = arr_employees->employees[employee_index].cod_employee;
	spreadsheet->details[spreadsheet->used - 1].full_days = h_util_get_int(0, max_days, "Dias completos?");
	spreadsheet->details[spreadsheet->used - 1].half_days = h_util_get_int(0, max_days, "Meios dias?");
	spreadsheet->details[spreadsheet->used - 1].weekend_days = h_util_get_int(0, 5, "Fins de semana? (0-5)");
	spreadsheet->details[spreadsheet->used - 1].absent_days = h_util_get_int(0, max_days, "Faltas?");

}

void h_proc_print(s_spreadsheet* spreadsheet)
{
	int i;

    if (spreadsheet->used == 0 || spreadsheet->month_is_set == 0)
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

    if (spreadsheet->used == 0 || spreadsheet->month_is_set == 0)
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

    if (spreadsheet->used == 0 || spreadsheet->month_is_set == 0)
	{
		fprintf(stdout, RED("[!] Mês não criado ou vazio\n"));
		return;
	}

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

    if (spreadsheet->used == 0 || spreadsheet->month_is_set == 0)
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
		fprintf(fp, "%d,%d,%d,%d\n",
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
	s_arr_irs* single_array,
	s_arr_irs* unique_holder_array,
	s_arr_irs* two_holders_array,
	s_arr_iss* iss_array,
	s_arr_employees* employees_array)
{
	int i;
    int emp_index;
	float days_worked;

	if (spreadsheet->used == 0 || spreadsheet->month_is_set == 0)
	{
		puts(RED("[!] Mês não criado ou vazio"));
		return;
	} else if (spreadsheet->is_processed == 1) // Alteração doutras tabelas não deve refletir sobre meses ja processados
    {
        puts(RED("[!] Mês já processado"));
        return;
    }
	else if (single_array->used == 0 || unique_holder_array->used == 0 || two_holders_array->used == 0)
	{
		puts(RED("[!] Tabelas IRS possivelmente não inicializadas"));
		return;
	}
	else if (iss_array->used == 0)
	{
		puts(RED("[!] Tabela ISS não inicializada"));
		return;
	}
	else if (employees_array->used == 0)
	{
		puts(RED("[!] Employees não inicializado"));
		return;
	}

	for (i = 0; i < spreadsheet->used; i++)
	{
        emp_index = h_proc_get_employee_index(employees_array, spreadsheet->details->cod_employee);
        printf("Index: %d\n", emp_index);

	    // Calculo dos Dias Trabalhados e o Bonus Correspondente
		days_worked = (float)spreadsheet->details[i].full_days +
		              (float)spreadsheet->details[i].half_days * 0.5f +
			          (float)spreadsheet->details[i].weekend_days;

		// Calculo do Salário Bruto
		spreadsheet->details[i].gross_pay =
			(float)spreadsheet->details[i].full_days * employees_array->employees[emp_index].hourly_rate +
			(float)spreadsheet->details[i].half_days * employees_array->employees[emp_index].hourly_rate * 0.5f +
			(float)spreadsheet->details[i].weekend_days * employees_array->employees[emp_index].hourly_rate * 1.5f;

		if (days_worked > 20)
		{
			spreadsheet->details[i].bonus = BONUS_20_DAYS;
		}
		else if (days_worked > 17)
		{
			spreadsheet->details[i].bonus = BONUS_17_DAYS;
		}
		else
		{
			spreadsheet->details[i].bonus = BASE_BONUS;
		}

		spreadsheet->details[i].gross_pay *= spreadsheet->details[i].bonus;
        printf("Raw: %.2f€\n", spreadsheet->details[i].gross_pay);

		spreadsheet->details[i].food_allowance =
			(float)spreadsheet->details[i].full_days * employees_array->employees[emp_index].base_food_allowance +
            (float)spreadsheet->details[i].weekend_days * employees_array->employees[emp_index].base_food_allowance;
        printf("Food: %.2f€\n", spreadsheet->details[i].food_allowance);

		spreadsheet->details[i].gross_pay += spreadsheet->details[i].food_allowance;
        printf("Gross: %.2f€\n", spreadsheet->details[i].gross_pay);

		// Calculo da retenção pelo IRS
		switch (employees_array->employees[emp_index].holders)
		{
			case NONE:
				spreadsheet->details[i].irs_retention = h_proc_get_retention_percentage
					(single_array, employees_array->employees[emp_index].dependents, spreadsheet->details[i].gross_pay);
				break;
			case UNIQUE_HOLDER:
				spreadsheet->details[i].irs_retention = h_proc_get_retention_percentage
					(unique_holder_array, employees_array->employees[emp_index].dependents, spreadsheet->details[i].gross_pay);
				break;
			case TWO_HOLDERS:
				spreadsheet->details[i].irs_retention = h_proc_get_retention_percentage
					(two_holders_array, employees_array->employees[emp_index].dependents, spreadsheet->details[i].gross_pay);
				break;
		}

        printf("IRS Percentage: %.2f%%\n", spreadsheet->details[i].irs_retention);
		spreadsheet->details[i].irs_retention *= spreadsheet->details[i].gross_pay;

		// Calculo da retenção pela Segurança social
		spreadsheet->details[i].iss_retention_employer = spreadsheet->details[i].gross_pay *
			iss_array->data[employees_array->employees[emp_index].role].employer / 100.0f;

		spreadsheet->details[i].iss_retention_employee = spreadsheet->details[i].gross_pay *
			iss_array->data[employees_array->employees[emp_index].role].employee / 100.0f;

		// Calculo do Salário Liquido
		spreadsheet->details[i].net_pay = spreadsheet->details[i].gross_pay -
			spreadsheet->details[i].iss_retention_employee - spreadsheet->details[i].irs_retention;

		// Encargo Total do Empregador
		spreadsheet->details[i].employer_charge = spreadsheet->details[i].gross_pay +
			spreadsheet->details[i].iss_retention_employer +
			spreadsheet->details[i].iss_retention_employee +
			spreadsheet->details[i].irs_retention;
	}

    spreadsheet->is_processed = 1;
	puts(GREEN("[!] Mês processado com sucesso"));
}

int h_proc_get_employee_index(s_arr_employees* employees_array, int code)
{
    int i;

    for (i = 0; i < employees_array->used; i++)
    {
        if (code == employees_array->employees[i].cod_employee)
        {
            return i;
        }
    }
}

float h_proc_get_retention_percentage(s_arr_irs* irs_array, int dependents, float raw_salary)
{
	int i;

	for (i = 0; i < irs_array->used; i++)
	{
		if (raw_salary <= irs_array->elements[i].monthly_pay_value
			&& irs_array->elements[i].monthly_pay_type == H_IRS_UP_TO)
		{
			return irs_array->elements[i + 1].percentage_per_dependent[dependents] / 100.0f;
		}
	}

	if (raw_salary > irs_array->elements[irs_array->used - 1].monthly_pay_value &&
		irs_array->elements[irs_array->used - 1].monthly_pay_type == H_IRS_BEYOND)
	{
		return irs_array->elements[irs_array->used - 1].percentage_per_dependent[dependents] / 100.0f;
	}
}

void h_proc_write(s_spreadsheet* spreadsheet, const char* path)
{
	FILE* fp;

    if (spreadsheet->used == 0 || spreadsheet->month_is_set == 0)
	{
	    printf("%s: %s", H_STRS_SAVE_FILE_ERROR, path);
        return;
	}

	fp = fopen(path, "wb");
	if (fp == NULL)
	{
		return;
	}

	fwrite(spreadsheet->details, sizeof(s_details), 1, fp);

	puts(H_STRS_SAVE_SUCCESS);
	fclose(fp);
}

void h_proc_create(s_spreadsheet *spreadsheet)
{
    if (spreadsheet->month_is_set == 1)
    {
        fprintf(stdout, RED("[!] Mês %s já criado\n"), h_calendar_str_from_month(spreadsheet->month));
        return;
    }

    spreadsheet->month = h_util_get_int(1, 12, "Mês: (1-12)") - 1;
    spreadsheet->month_is_set = 1;

    fprintf(stdout, GREEN("[!] Mês de %s criado com sucesso\n"), h_calendar_str_from_month(spreadsheet->month));
}