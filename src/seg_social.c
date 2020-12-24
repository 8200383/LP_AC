/*
 * Created by Hugo Carvalho on 12/24/20.
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "seg_social.h"
#include "util.h"

s_arr_seg_social* h_seg_social_alloc(int initial_capacity)
{
	int i;
	s_arr_seg_social* array;

	array = malloc(sizeof(s_arr_seg_social));
	if (array == NULL)
		return NULL;

	array->data = malloc(initial_capacity * sizeof(s_seg_social));
	if (array->data == NULL)
		return NULL;

	array->used = 0;
	array->max_capacity = initial_capacity - 1;

	for (i = 0; i < initial_capacity; i++)
	{
		array->data[i].criteria = '\0';
		array->data[i].employer = 0.0f;
		array->data[i].employee = 0.0f;
	}

	return array;
}

s_error* h_seg_social_parse(s_arr_seg_social* array, char* str)
{
	if (array == NULL || str == NULL)
		return h_error_create(H_ERROR_PARSING, "h_irs_parse()");

	int is_employer = 1, offset = -1;

	for (int i = 0; str[i] != '\0'; i++)
	{
		if (offset == -1 && isalnum(str[i]))
			offset = i;

		if (offset != -1 && str[i] == ';')
		{
			str[i] = '\0';
			if (str[i - 1] == '%')
			{
				str[i - 1] = '\0';
				if (is_employer == 1)
				{
					array->data[array->used].employer = strtof(str + offset, NULL);
					is_employer = 0;
				}
				else
				{
					array->data[array->used].employee = strtof(str + offset, NULL);
					is_employer = 1;
				}
				offset = -1;
			}
			else
			{
				array->data[array->used].criteria = str[offset];
				offset = -1;
			}
		}

		if (str[i] == '\n')
			array->used++;
	}

	return NULL;
}

void h_seg_social_print(s_arr_seg_social* array)
{
	for (int i = 0; i <= array->used; i++)
	{
		printf("%d. Criterio: %c ### Empregador: %.2f%% ### Empregado: %.2f%%\n",
			i,
			array->data[i].criteria,
			array->data[i].employer,
			array->data[i].employee);
	}
}
/*
s_social_sec* social_sec_add(s_social_sec* data, int* len)
{
	char new_criteria;
	printf("\nNovo critério: ");
	scanf(" %c", &new_criteria);

	for (int i = 0; i < (*len); i++)
	{
		if (new_criteria == data[i].criteria)
		{
			printf("O critério já existe.\n");
			return data;
		}
	}

	data[*len].criteria = new_criteria;
	data[*len].employer = h_util_get_float(0.0f, 100.0f, "Empregador: ");
	data[*len].employee = h_util_get_float(0.0f, 100.0f, "Empregado: ");

	(*len)++;
	return data;
}

s_social_sec* social_sec_del(s_social_sec* data, int* len)
{
	int num = h_util_get_int(0, 100, "\nLinha a eliminar: ");

	if (num < 0 || num >= *len)
	{
		printf("A linha escolhida não existe.\n");
		return data;
	}

	(*len)--;

	for (int i = num; i < (*len); i++)
	{
		data[i].criteria = data[i + 1].criteria;
		data[i].employer = data[i + 1].employer;
		data[i].employee = data[i + 1].employee;
	}

	return data;
}

*/

s_error* h_seg_social_write(s_arr_seg_social* array, const char* path)
{
	FILE* fp;
	int i;

	if (path == NULL)
		h_error_create(H_ERROR_UNKNOWN, "h_seg_social_write()");

	fp = fopen(path, "w");
	if (fp == NULL)
		h_error_create(H_ERROR_WRITE, "h_seg_social_write()");

	for (i = 0; i <= array->used; i++)
	{
		fprintf(fp, "%c;%.2f%%;%.2f%%;\n",
			array->data[i].criteria,
			array->data[i].employer,
			array->data[i].employee);
	}

	fclose(fp);

	return NULL;
}

void h_seg_social_edit(s_arr_seg_social* array)
{
	int num = h_util_get_int(0, 100, "\nLinha a editar: ");

	if (num < 0 || num >= array->used)
	{
		printf("A linha escolhida não existe.\n");
		return;
	}

	char new_criteria;
	printf("Critério - Valor atual: %c | ", array->data[num].criteria);
	printf("Novo valor: ");
	scanf(" %c", &new_criteria);

	for (int i = 0; i <= array->used; i++)
	{
		if (new_criteria == array->data[i].criteria && i != num)
		{
			printf("O critério já existe.\n");
			return;
		}
	}

	array->data[num].criteria = new_criteria;
	printf("Empregador - Valor atual: %.2f | ", array->data[num].employer);
	array->data[num].employer = h_util_get_float(0.0f, 100.0f, "Novo valor: ");
	printf("Empregado - Valor atual: %.2f | ", array->data[num].employee);
	array->data[num].employee = h_util_get_float(0.0f, 100.0f, "Novo valor: ");
}
