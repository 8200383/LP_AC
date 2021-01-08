/*
 * Created by Hugo Carvalho on 12/24/20.
 */

#include "iss.h"

s_arr_iss* h_iss_alloc(int initial_capacity)
{
	int i;
	s_arr_iss* array;

	array = malloc(sizeof(s_arr_iss));
	if (array == NULL)
	{
		return NULL;
	}

	array->data = malloc(initial_capacity * sizeof(s_iss));
	if (array->data == NULL)
	{
		return NULL;
	}

	array->used = 0;
	array->max_capacity = initial_capacity;

	for (i = 0; i <= array->max_capacity; i++)
	{
		array->data[i].criteria = malloc(BUFFER_SIZE * sizeof(char));
		if (array->data[i].criteria == NULL)
		{
			return NULL;
		}
	}
	return array;
}

void h_iss_free(s_arr_iss* array)
{
	if (array == NULL)
	{
		return;
	}

	free(array->data);
	free(array);
}

void h_iss_parse(s_arr_iss* array, char* str)
{
	int i;
	int offset = -1;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (offset == -1 && isalnum(str[i]))
		{
			offset = i;
		}

		if (offset != -1)
		{
			if (str[i] == ',')
			{
				str[i] = '\0';
				if (str[i - 1] == '%')
				{
					str[i - 1] = '\0';
					array->data[array->used].employer = strtof(str + offset, NULL);
				}
				else
				{
					str[i] = '\0';

					if (strlen(str + offset) > BUFFER_SIZE)
					{
						array->data[array->used].criteria = realloc(array->data[array->used].criteria,
							(BUFFER_SIZE * 2) * sizeof(char));

						if (array->data[array->used].criteria == NULL)
						{
							return;
						}
					}
					strcpy(array->data[array->used].criteria, str + offset);
				}
				offset = -1;
			}
			else if (str[i] == '\n')
			{
				str[i - 1] = '\0';
				array->data[array->used].employee = strtof(str + offset, NULL);
				array->used++;
				offset = -1;
			}
		}
	}
}

void h_iss_delete_all(s_arr_iss* array)
{
	int i;

	if (array->used == 0)
	{
		printf(H_STRS_EMPTY_TABLE);
		return;
	}

	for (i = 0; i < array->used; array->used--)
	{
		array->data[i] = array->data[i + 1];
	}
}

void h_iss_print(s_arr_iss* array)
{
	int i;

	if (array->used == 0)
	{
		printf(H_STRS_EMPTY_TABLE);
		return;
	}

	printf("%s", H_STRS_SS_TABLE_HEADER);
	for (i = 0; i < array->used; i++)
	{
		printf(RED("[%d] "), i);
		printf(YELLOW("%s "), array->data[i].criteria);
		printf(BLUE("| %.2f%% | %.2f%%\n"), array->data[i].employer, array->data[i].employee);
	}
}

void h_iss_add(s_arr_iss* array)
{
	int i;
	char* new_criteria;

	if (array->used == array->max_capacity)
	{
		array->max_capacity *= 2;
		array->data = realloc(array->data, array->max_capacity * sizeof(s_iss));
		if (array->data == NULL)
		{
			return;
		}
	}

	new_criteria = malloc(sizeof(char) * 64);
	if (new_criteria == NULL)
	{
		return;
	}

	printf("\nNovo critério: ");
	scanf("%s", new_criteria);

	for (i = 0; i < array->used; i++)
	{
		if (strcmp(new_criteria, array->data[i].criteria) == 0)
		{
			printf(H_STRS_CRITERIA_DUPLICATE);
			return;
		}
	}

	array->data[array->used].criteria = new_criteria;
	array->data[array->used].employer = h_util_get_float(0.0f, 100.0f, "Empregador: ");
	array->data[array->used].employee = h_util_get_float(0.0f, 100.0f, "Empregado: ");
	array->used++;
}

void h_iss_delete(s_arr_iss* array)
{
	int i;
	int num;

	if (array->used == 0)
	{
		printf(H_STRS_EMPTY_TABLE);
		return;
	}

	num = h_util_get_int(0, (array->used) - 1, "Linha a eliminar: ");

	for (i = num; i < array->used; i++)
	{
		array->data[i] = array->data[i + 1];
	}

	array->used--;
}

void h_iss_edit(s_arr_iss* array)
{
	int i;
	int num;
	char* new_criteria;

	if (array->used == 0)
	{
		printf(H_STRS_EMPTY_TABLE);
		return;
	}

	printf(YELLOW("Número de Registos: %d\n"), array->used);
	num = h_util_get_int(0, (array->used) - 1, "Linha a editar: ");

	new_criteria = malloc(sizeof(char) * 64);
	if (new_criteria == NULL)
	{
		return;
	}

	printf("Critério - Valor atual: %s | ", array->data[num].criteria);
	printf("Novo valor: ");
	scanf("%s", new_criteria);

	for (i = 0; i <= array->used; i++)
	{
		if (strcmp(new_criteria, array->data[i].criteria) == 0 && i != num)
		{
			printf(H_STRS_CRITERIA_DUPLICATE);
			return;
		}
	}

	array->data[num].criteria = new_criteria;
	printf("Empregador - Valor atual: %.2f | ", array->data[num].employer);
	array->data[num].employer = h_util_get_float(0.0f, 100.0f, "Novo valor: ");
	printf("Empregado - Valor atual: %.2f | ", array->data[num].employee);
	array->data[num].employee = h_util_get_float(0.0f, 100.0f, "Novo valor: ");
}

void h_iss_write(s_arr_iss* array, const char* path)
{
	int i;
	FILE* fp;

	fp = fopen(path, "w");
	if (fp == NULL)
	{
		return;
	}

	for (i = 0; i <= array->used; i++)
	{
		fprintf(fp, "%s,%.2f%%,%.2f%%,\n",
			array->data[i].criteria,
			array->data[i].employer,
			array->data[i].employee);
	}

	printf(H_STRS_SAVE_SUCCESS);
	fclose(fp);
}