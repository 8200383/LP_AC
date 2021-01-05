/*
 * Created by Hugo Carvalho on 12/24/20.
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "iss.h"
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

	return array;
}

void h_seg_social_parse(s_arr_seg_social* array, char* str)
{
	int i, is_employer = 1, offset = -1;

	for (i = 0; str[i] != '\0'; i++)
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
}

void h_seg_social_print(s_arr_seg_social* array)
{
	int i;

	for (i = 0; i <= array->used; i++)
	{
		printf("%d. Criterio: %c ### Empregador: %.2f%% ### Empregado: %.2f%%\n",
			i,
			array->data[i].criteria,
			array->data[i].employer,
			array->data[i].employee);
	}
}

void h_seg_social_add(s_arr_seg_social* array)
{
	char new_criteria;
	int i;

	if (array->used == array->max_capacity)
	{
		array->max_capacity *= 2;
		array->data = realloc(array->data, array->max_capacity * sizeof(s_seg_social));
		if (array->data == NULL)
			return;
	}

	printf("\nNovo critério: ");
	scanf(" %c", &new_criteria);

	for (i = 0; i <= array->used; i++)
	{
		if (new_criteria == array->data[i].criteria)
			return;
	}

	array->used++;
	array->data[array->used].criteria = new_criteria;
	array->data[array->used].employer = h_util_get_float(0.0f, 100.0f, "Empregador: ");
	array->data[array->used].employee = h_util_get_float(0.0f, 100.0f, "Empregado: ");
}

void h_seg_social_delete(s_arr_seg_social* array)
{
	int num, i;

	if (array == NULL)
		return;

	num = h_util_get_int(0, 100, "Linha a eliminar: ");
	if (num < 0 || num >= array->used)
		return;

	for (i = num; i <= array->used - 1; i++)
		array->data[i] = array->data[i + 1];

	array->used--;
}

void h_seg_social_write(s_arr_seg_social* array, const char* path)
{
	FILE* fp;
	int i;

	if (path == NULL)
		return;

	fp = fopen(path, "w");
	if (fp == NULL)
		return;

	for (i = 0; i <= array->used; i++)
	{
		fprintf(fp, "%c;%.2f%%;%.2f%%;\n",
			array->data[i].criteria,
			array->data[i].employer,
			array->data[i].employee);
	}

	fclose(fp);
}

void h_seg_social_edit(s_arr_seg_social* array)
{
	char new_criteria;
	int num, i;

	num = h_util_get_int(0, 100, "\nLinha a editar: ");

	if (num < 0 || num >= array->used)
		return;

	printf("Critério - Valor atual: %c | ", array->data[num].criteria);
	printf("Novo valor: ");
	scanf(" %c", &new_criteria);

	for (i = 0; i <= array->used; i++)
	{
		if (new_criteria == array->data[i].criteria && i != num)
			return;
	}

	array->data[num].criteria = new_criteria;
	printf("Empregador - Valor atual: %.2f | ", array->data[num].employer);
	array->data[num].employer = h_util_get_float(0.0f, 100.0f, "Novo valor: ");
	printf("Empregado - Valor atual: %.2f | ", array->data[num].employee);
	array->data[num].employee = h_util_get_float(0.0f, 100.0f, "Novo valor: ");
}
