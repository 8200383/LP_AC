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

	free(array->data->percentage_per_dependent);
	free(array->data);
	free(array);
}

void h_irs_build(s_irs* data, char* str, int* dependent)
{
	size_t size;

	size = strlen(str) - 1;

	if (h_util_strequal(str, "Até"))
		data->monthly_pay_type = H_IRS_UP_TO;

	else if (h_util_strequal(str, "Superior a"))
		data->monthly_pay_type = H_IRS_BEYOND;

	if (h_util_regexcmp(str, "EUR"))
	{
		str[size - 2] = '\0';
		data->monthly_pay_value = strtof(str, NULL);
		str[size - 2] = 'E';
	}

	if (h_util_regexcmp(str, "%"))
	{
		str[size] = '\0';
		data->percentage_per_dependent[(*dependent)++] = strtof(str, NULL) / 100.0f;
		str[size] = '%';
	}
}

void h_irs_parse(s_arr_irs* array, char* str, h_irs_pair_func pair_func)
{
	int dependent;
	int offset_value;
	int i;

	if (array == NULL || str == NULL)
		return;

	offset_value = -1;
	dependent = 0;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (offset_value == -1 && isalnum(str[i]))
			offset_value = i;

		if (offset_value != -1 && str[i] == ',')
		{
			str[i] = '\0';
			pair_func(&array->data[array->used], str + offset_value, &dependent);
			offset_value = -1;
		}

		// If new line found move to the next struct
		if (str[i] == '\n')
		{
			array->used++;
			dependent = 0;
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

	do
	{
		char op = h_util_get_alphabetical_char("[A]té [S]uperior a: ");
		if (op == 'A' || op == 'a')
		{
			array->data[array->used].monthly_pay_type = H_IRS_UP_TO;
			break;
		}
		else if (op == 'S' || op == 's')
		{
			array->data[array->used].monthly_pay_type = H_IRS_BEYOND;
			break;
		}
	} while (1);

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
		return;

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