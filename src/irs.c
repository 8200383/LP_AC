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
	array->max_capacity = initial_capacity - 1;

	for (i = 0; i < initial_capacity; i++)
	{
		array->data[i].monthly_pay_type = H_IRS_UP_TO;
		array->data[i].monthly_pay_value = 0.0f;

		array->data[i].percentage_per_dependent = malloc(MAX_DEPENDENT_NUMBER * sizeof(float));
		if (array->data[i].percentage_per_dependent == NULL)
			return NULL;

		for (j = 0; j < MAX_DEPENDENT_NUMBER; j++)
			array->data[i].percentage_per_dependent[j] = 0.0f;
	}

	return array;
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

s_error* h_irs_parse(s_arr_irs* array, char* str, h_irs_pair_func pair_func)
{
	int dependent;
	int offset_value;
	int i;

	if (array == NULL || str == NULL)
		return h_error_create(H_ERROR_PARSING, "h_irs_parse()");

	offset_value = -1;
	dependent = 0;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (offset_value == -1 && isalnum(str[i]))
			offset_value = i;

		if (offset_value != -1 && str[i] == ',')
		{
			str[i] = '\0'; // Remove the ,
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

	return NULL;
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

s_error* h_irs_print(s_arr_irs* array)
{
	int i;

	if (array == NULL)
		return h_error_create(H_ERROR_READ, "[!] Nothing to show\n");

	fprintf(stdout, "%s", H_STRS_IRS_TABLE_HEADER);
	for (i = 0; i <= array->used; i++)
	{
		fprintf(stdout, RED("[%d] "), i);
		h_irs_print_line(array->data[i]);
	}
}

void h_irs_scan_fields(s_irs* data)
{
	int j;

	data->monthly_pay_type = (h_util_get_option('A', 'S', "[A]té\n[S]uperior a") == 'A')
							 ? H_IRS_UP_TO : H_IRS_BEYOND;

	data->monthly_pay_value = h_util_get_float(0.0f, 100.0f, "Remuneração Mensal");

	for (j = 0; j < MAX_DEPENDENT_NUMBER; j++)
	{
		fprintf(stdout, YELLOW("Percentagem para o dependente %d\n"), j);
		data->percentage_per_dependent[j] = h_util_get_float(0.0f, 100.0f, NULL);
	}
}

s_error* h_irs_add(s_arr_irs* array)
{
	int i;
	int j;

	if (array->used == array->max_capacity)
	{
		array->max_capacity *= 2;

		array->data = realloc(array->data, array->max_capacity * sizeof(s_irs));
		if (array->data == NULL)
			return h_error_create(H_ERROR_ALLOCATION, "h_irs_add(): array->data");

		for (i = array->used + 1; i <= array->max_capacity; i++)
		{
			array->data[i].percentage_per_dependent = malloc(MAX_DEPENDENT_NUMBER * sizeof(float));
			if (array->data[i].percentage_per_dependent == NULL)
				return h_error_create(H_ERROR_ALLOCATION, "h_irs_add(): percentage_per_dependent");

			for (j = 0; j < MAX_DEPENDENT_NUMBER; j++)
				array->data[i].percentage_per_dependent[j] = 0.0f;
		}
	}

	h_irs_scan_fields(&array->data[++array->used]);

	return NULL;
}

s_error* h_irs_edit(s_arr_irs* array, int index)
{
	if (array == NULL || array->used < index)
		return h_error_create(H_ERROR_EDIT, "[!] Nothing to edit\n");

	fprintf(stdout, H_STRS_IRS_TABLE_HEADER);
	h_irs_print_line(array->data[index]);

	h_irs_scan_fields(&array->data[index]);
}

s_error* h_irs_delete(s_arr_irs* array, int index)
{
	int i;

	if (array == NULL || array->used < index)
		return h_error_create(H_ERROR_DELETE, "[!] Empty Table\n");

	for (i = index; i <= array->used - 1; i++)
		array->data[i] = array->data[i + 1];

	array->used--;

	return NULL;
}

s_error* h_irs_write(s_arr_irs* array, const char* path)
{
	FILE* fp;
	int i;
	int j;

	if (array == NULL)
		return h_error_create(H_ERROR_UNKNOWN, path);

	fp = fopen(path, "wb");
	if (fp == NULL)
		return h_error_create(H_ERROR_WRITE, path);

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

	return NULL;
}