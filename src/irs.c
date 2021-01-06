/* 
 * Created by Micael Dias on 10/12/20.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "irs.h"
#include "colors.h"
#include "strs.h"
#include "util.h"

s_arr_irs* h_irs_alloc(int initial_capacity)
{
	s_arr_irs* array;
	int i;
	int j;

	if (!initial_capacity)
		return NULL;

	array = malloc(sizeof(s_arr_irs));
	if (array == NULL)
		return NULL;

	array->data = malloc(initial_capacity * sizeof(s_irs));
	if (array->data == NULL)
		return NULL;

	array->used = 0;
	array->max_capacity = initial_capacity;

	for (i = 0; i <= array->max_capacity; i++)
	{
		array->data[i].percentage_per_dependent = malloc(MAX_DEPENDENT_NUMBER * sizeof(float));
		if (array->data[i].percentage_per_dependent == NULL)
			return NULL;
	}

	return array;
}

void h_irs_free(s_arr_irs* array)
{
	if (array == NULL)
		return;

	free(array->data);
	free(array);
}

void h_irs_build(s_irs* data, char* str, int* dependent)
{
	size_t length = strlen(str);

	if (strcmp(str, "Até") == 0)
	{
		data->monthly_pay_type = H_IRS_UP_TO;
	}
	else if (strcmp(str, "Superior a") == 0)
	{
		data->monthly_pay_type = H_IRS_BEYOND;
	}

	if (str[length - 1] == '%')
	{
		data->percentage_per_dependent[*dependent] = strtof(str, NULL) / 100.0f;
		(*dependent)++;
	}
	else
	{
		data->monthly_pay_value = strtof(str, NULL);
	}
}

void h_irs_parse(s_arr_irs* array, const char* str, h_irs_pair_func pair_func)
{
	if (array == NULL || str == NULL)
	{
		fprintf(stdout, RED("[!] CSV parser error"));
		return;
	}

	int i;
	int j;
	int k; // buffer counter
	int delimiter = -1;
	int dependents = 0;
	char buffer[CSV_BUFFER];
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == CSV_COLUMN_DELIMITER || str[i] == CSV_NEW_LINE_DELIMITER)
		{
			for (j = delimiter + 1, k = 0; j < i; j++, k++)
			{
				buffer[k] = str[j];
			}

			pair_func(&array->data[array->used], buffer, &dependents);
			memset(buffer, 0, CSV_BUFFER);

			delimiter = i;
		}

		if (str[i] == CSV_NEW_LINE_DELIMITER)
		{
			array->used++;
			dependents = 0;
		}
	}
}

void h_irs_print_line(s_irs data)
{
	int j;

	fprintf(stdout, YELLOW("%s %.2f€"),
		data.monthly_pay_type == H_IRS_UP_TO ? "Até" : "Superior a",
		data.monthly_pay_value);

	for (j = 0; j < MAX_DEPENDENT_NUMBER; j++)
		fprintf(stdout, CYAN(" | %.1f%%"), data.percentage_per_dependent[j] * 100.0f);

	fprintf(stdout, "\n");
}

void h_irs_print(s_arr_irs* array)
{
	int i;

	fprintf(stdout, "%s", H_STRS_IRS_TABLE_HEADER);
	for (i = 0; i <= array->used; i++)
	{
		fprintf(stdout, RED("[%d] "), i);
		h_irs_print_line(array->data[i]);
	}
}

void h_irs_add(s_arr_irs* array)
{
	int i;
	int j;
	int k;

	if (array->used == array->max_capacity)
	{
		array->max_capacity *= 2;

		array->data = realloc(array->data, array->max_capacity * sizeof(s_irs));
		if (array->data == NULL)
			return;

		for (i = array->used + 1; i <= array->max_capacity; i++)
		{
			array->data[i].percentage_per_dependent = malloc(MAX_DEPENDENT_NUMBER * sizeof(float));
			if (array->data[i].percentage_per_dependent == NULL)
				return;

			for (j = 0; j < MAX_DEPENDENT_NUMBER; j++)
				array->data[i].percentage_per_dependent[j] = 0.0f;
		}
	}

	array->used++;

	char op = h_util_get_alphabetical_char("[A]té [S]uperior a: ");
	if (op == 'A' || op == 'a')
	{
		array->data[array->used].monthly_pay_type = H_IRS_UP_TO;
	}
	else if (op == 'S' || op == 's')
	{
		array->data[array->used].monthly_pay_type = H_IRS_BEYOND;
	}

	array->data[array->used].monthly_pay_value = h_util_get_float(0.0f, 10000.0f, "Remuneração Mensal: ");

	fprintf(stdout, YELLOW("[!] Inserir percentagem para os dependentes de 0 a 5 ou mais\n"));
	for (k = 0; k < MAX_DEPENDENT_NUMBER; k++)
	{
		array->data[array->used].percentage_per_dependent[k] = h_util_get_float(0.0f, 100.0f, "Percentagem: ");
	}
}

void h_irs_edit(s_arr_irs* array, int index)
{
	int j;

	if (array->used < index)
	{
		puts(RED("[!] Linha não existe"));
		return;
	}

	fprintf(stdout, H_STRS_IRS_TABLE_HEADER);
	h_irs_print_line(array->data[index]);

	do
	{
		char op = h_util_get_alphabetical_char("[A]té [S]uperior a: ");
		if (op == 'A' || op == 'a')
		{
			array->data[index].monthly_pay_type = H_IRS_UP_TO;
			break;
		}
		else if (op == 'S' || op == 's')
		{
			array->data[index].monthly_pay_type = H_IRS_BEYOND;
			break;
		}
	} while (1);

	array->data[index].monthly_pay_value = h_util_get_float(0.0f, 10000.0f, "Remuneração Mensal: ");

	fprintf(stdout, YELLOW("[!] Inserir percentagem para os dependentes de 0 a 5 ou mais\n"));
	for (j = 0; j < MAX_DEPENDENT_NUMBER; j++)
	{
		array->data[index].percentage_per_dependent[j] = h_util_get_float(0.0f, 100.0f, "Percentagem: ");
	}
}

void h_irs_delete(s_arr_irs* array, int index)
{
	int i;

	if (array == NULL || array->used < index)
		return;

	for (i = index; i <= array->used - 1; i++)
		array->data[i] = array->data[i + 1];

	array->used--;
}

void h_irs_write(s_arr_irs* array, const char* path)
{
	FILE* fp;
	int i;
	int j;

	fp = fopen(path, "wb");
	if (fp == NULL)
		return;

	for (i = 0; i <= array->used; i++)
	{
		fprintf(fp, "%s,%.2fEUR,",
			array->data[i].monthly_pay_type == H_IRS_UP_TO ? "Até" : "Superior a",
			array->data[i].monthly_pay_value);

		for (j = 0; j < MAX_DEPENDENT_NUMBER; j++)
			fprintf(fp, "%.1f%%,", array->data[i].percentage_per_dependent[j] * 100);

		fprintf(fp, "\n");
	}

	fclose(fp);
}