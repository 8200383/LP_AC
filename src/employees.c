#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "employees.h"
#include "colors.h"
#include "strs.h"
#include "util.h"

int first_name_buffer_size = 64;
int last_name_buffer_size = 64;

s_arr_employees* h_employees_alloc(int initial_capacity)
{
	s_arr_employees* array;
	int i;

	if (!initial_capacity)
		return NULL;

	array = malloc(sizeof(s_arr_employees));
	if (array == NULL)
		return NULL;

	array->employees = malloc(initial_capacity * sizeof(s_employee_record));
	if (array->employees == NULL)
		return NULL;

	array->used = 0;
	array->max_capacity = initial_capacity;

	for (i = 0; i <= array->max_capacity; i++)
	{
		array->employees[i].role = calloc(1, sizeof(char));
		if (array->employees[i].role == NULL)
			return NULL;

		array->employees[i].first_name = calloc(first_name_buffer_size, sizeof(char));
		if (array->employees[array->used].first_name == NULL)
			return NULL;

		array->employees[i].last_name = calloc(last_name_buffer_size, sizeof(char));
		if (array->employees[array->used].last_name == NULL)
			return NULL;
	}

	return array;
}

int h_employees_randomize()
{
	srand(1);

	return rand() % MAX_VALUE;
}

int h_employees_ask_status()
{

	switch (h_util_get_int(0, 3, "Estado Civil: (0-3)\n0 - Solteiro\n1 - Casado\n2 - Divorciado\n3 - Viuvo"))
	{
	case 0:
		return SINGLE;
	case 1:
		return MARRIED;
	case 2:
		return DIVORCED;
	case 3:
		return WIDOWED;
	default:
		puts("Civil status invalid! Let's assume civil status: SINGLE.");
	}

	return SINGLE;
}

void h_employees_add(s_arr_employees* array)
{
	if (array->used == array->max_capacity)
	{
		array->max_capacity *= 2;
		array->employees = realloc(array->employees, array->max_capacity * sizeof(s_employee_record));
		if (array->employees == NULL)
			return;
	}

	array->used++;
	array->employees[array->used].code = h_employees_randomize();

	array->employees[array->used].entry_date = h_calendar_get_date("Data de entrada? ");

	array->employees[array->used].birthday = h_calendar_get_date("Data de nascimento? ");

	array->employees[array->used].leaving_date = NULL;
	array->employees[array->used].marital_status = h_employees_ask_status();

	printf("Primeiro nome: \n");
	scanf("%s", array->employees[array->used].first_name);
	printf("Último nome: \n");
	scanf("%s", array->employees[array->used].last_name);
	printf("Cargo: \n");
	scanf("%s", array->employees[array->used].role);

	array->employees[array->used].number_dependents = h_util_get_int(0, 5, "Numero dependentes: ");
	array->employees[array->used].phone_number = h_util_get_int(1, 9, "Numero Telefone: s");
}

void h_employees_print(s_arr_employees* array)
{
	int i;

	if (array->used == 0)
	{
		puts(RED("Tabela vazia"));
		return;
	}

	printf(H_STRS_EMPLOYEES_TABLE_HEADER);
	for (i = 0; i <= array->used; i++)
	{
		printf("[%d] %d | %s | %s | %s | %d \n",
			i,
			array->employees[i].code,
			array->employees[i].first_name,
			array->employees[i].last_name,
			array->employees[i].role,
			array->employees[i].phone_number
		);
	}
}

void h_employees_parse(s_arr_employees* array, char* str)
{
	int i;
	int offset;
	int column;

	if (array == NULL || str == NULL)
		return;

	offset = -1;
	column = 0;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (offset == -1 && isalnum(str[i]))
			offset = i;

		if (offset != -1 && str[i] == ',')
		{
			str[i] = '\0';

			// Code func 4 digits
			if (h_util_str_is_digit(str + offset) == 4 && column == COL_CODE_FUNC)
				array->employees[array->used].code = atoi(str + offset);

			if (h_util_str_is_digit(str + offset) == 1 && column == COL_NUM_DEPENDENTS)
				array->employees[array->used].number_dependents = atoi(str + offset);

			if (column == COL_ROLE) // TODO: check if is upper
				strcpy(array->employees[array->used].role, str + offset);

			// Phone number 9 digits
			if (h_util_str_is_digit(str + offset) == 9 && column == COL_PHONE_NUMBER)
				array->employees[array->used].phone_number = atoi(str + offset);

			if (strcmp(str + offset, "MARRIED") == 0 && column == COL_MARITAL_STATUS)
				array->employees[array->used].marital_status = MARRIED;

			if (strcmp(str + offset, "SINGLE") == 0 && column == COL_MARITAL_STATUS)
				array->employees[array->used].marital_status = SINGLE;

			if (strcmp(str + offset, "DIVORCED") == 0&& column == COL_MARITAL_STATUS)
				array->employees[array->used].marital_status = DIVORCED;

			if (h_util_is_name(str + offset) == 0 && column == COL_FIRST_NAME)
			{
				if (strlen(str + offset) >= first_name_buffer_size)
				{
					array->employees[array->used].first_name =
						realloc(array->employees[array->used].first_name, first_name_buffer_size * 2);

					if (array->employees[array->used].first_name == NULL)
						return;

					first_name_buffer_size *= 2;
				}

				strcpy(array->employees[array->used].first_name, str + offset);
			}

			if (h_util_is_name(str + offset) == 0 && column == COL_LAST_NAME)
			{
				if (strlen(str + offset) >= last_name_buffer_size)
				{
					array->employees[array->used].last_name =
						realloc(array->employees[array->used].last_name, last_name_buffer_size * 2);

					if (array->employees[array->used].last_name == NULL)
						return;

					last_name_buffer_size *= 2;
				}
				strcpy(array->employees[array->used].last_name, str + offset);
			}

			if (column == COL_BIRTHDAY)
			{
				array->employees[array->used].birthday = h_calendar_init(str + offset);

				if (array->employees[array->used].birthday == NULL)
					return;
			}

			if (column == COL_ENTRY_DATE)
			{
				array->employees[array->used].entry_date = h_calendar_init(str + offset);

				if (array->employees[array->used].entry_date == NULL)
					return;
			}

			if (column == COL_LEAVING_DATE)
			{
				array->employees[array->used].leaving_date = h_calendar_init(str + offset);

				if (array->employees[array->used].leaving_date == NULL)
					return;
			}

			column++;
			offset = -1;
		}

		if (str[i] == '\n')
			array->used++;
	}
}