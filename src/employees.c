#include <stdio.h>
#include <stdlib.h>
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
		array->employees[i].first_name = calloc(first_name_buffer_size, sizeof(char));
		if (array->employees[array->used].first_name == NULL)
			return NULL;

		array->employees[i].last_name = calloc(last_name_buffer_size, sizeof(char));
		if (array->employees[array->used].last_name == NULL)
			return NULL;

		array->employees[i].birthday = malloc(sizeof(s_date));
		if (array->employees[array->used].birthday == NULL)
			return NULL;

		array->employees[i].entry_date = malloc(sizeof(s_date));
		if (array->employees[array->used].entry_date == NULL)
			return NULL;

		array->employees[i].leaving_date = malloc(sizeof(s_date));
		if (array->employees[array->used].leaving_date == NULL)
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
	if (array == NULL)
	{
		puts(RED("[!] Employees não alocado"));
		return;
	}

	if (array->used == array->max_capacity)
	{
		array->max_capacity *= 2;
		array->employees = realloc(array->employees, array->max_capacity * sizeof(s_employee_record));
		if (array->employees == NULL)
			return;
	}

	array->used++;
	array->employees[array->used].code = h_employees_randomize();

	printf("Primeiro nome: \n");
	scanf("%s", array->employees[array->used].first_name);
	printf("Último nome: \n");
	scanf("%s", array->employees[array->used].last_name);
	printf("Cargo: \n");
	scanf("%d", &array->employees[array->used].role);

	h_calendar_get_date(array->employees[array->used].birthday, "Data de nascimento? ");
	h_calendar_get_date(array->employees[array->used].entry_date, "Data de entrada? ");
	h_calendar_get_date(array->employees[array->used].leaving_date, "Data de saida? ");

	array->employees[array->used].marital_status = h_employees_ask_status();
	array->employees[array->used].number_dependents = h_util_get_int(0, 5, "Numero dependentes: ");
	array->employees[array->used].phone_number = h_util_get_int(1, 9, "Numero Telefone: ");
}

void h_employees_print(s_arr_employees* array)
{
	if (array == NULL || array->used == 0)
	{
		puts(RED("[!] Employees não alocado ou vazio"));
		return;
	}

	printf(H_STRS_EMPLOYEES_TABLE_HEADER);

	int i;
	for (i = 0; i < array->used; i++)
	{
		printf("[%d] %d | %s | %s | %d | %d | %d | %d/%d/%d | %d/%d/%d | %d/%d/%d\n",
			i,
			array->employees[i].code,
			array->employees[i].first_name,
			array->employees[i].last_name,
			array->employees[i].phone_number,
			array->employees[i].number_dependents,
			array->employees[i].role,
			array->employees[i].birthday->day,
			array->employees[i].birthday->month,
			array->employees[i].birthday->year,
			array->employees[i].entry_date->day,
			array->employees[i].entry_date->month,
			array->employees[i].entry_date->year,
			array->employees[i].leaving_date->day,
			array->employees[i].leaving_date->month,
			array->employees[i].leaving_date->year
		);
	}
}

void h_employees_pair(s_employee_record* employee, char* str, int column)
{
	if (h_util_str_is_digit(str) == 4 && column == COL_CODE_FUNC)
		employee->code = atoi(str);

	if (h_util_str_is_digit(str) == 1 && column == COL_NUM_DEPENDENTS)
		employee->number_dependents = atoi(str);

	if (h_util_str_is_digit(str) == 1 && column == COL_ROLE)
		employee->role = atoi(str);

	if (h_util_str_is_digit(str) == 9 && column == COL_PHONE_NUMBER)
		employee->phone_number = atoi(str);

	if (strcmp(str, "MARRIED") == 0 && column == COL_MARITAL_STATUS)
		employee->marital_status = MARRIED;

	else if (strcmp(str, "SINGLE") == 0 && column == COL_MARITAL_STATUS)
		employee->marital_status = SINGLE;

	else if (strcmp(str, "DIVORCED") == 0 && column == COL_MARITAL_STATUS)
		employee->marital_status = DIVORCED;

	if (column == COL_FIRST_NAME)
	{
		if (strlen(str) >= first_name_buffer_size)
		{
			employee->first_name = realloc(employee->first_name, first_name_buffer_size * 2);
			if (employee->first_name == NULL)
				return;

			first_name_buffer_size *= 2;
		}

		strcpy(employee->first_name, str);
	}

	if (column == COL_LAST_NAME)
	{
		if (strlen(str) >= last_name_buffer_size)
		{
			employee->last_name = realloc(employee->last_name, last_name_buffer_size * 2);
			if (employee->last_name == NULL)
				return;

			last_name_buffer_size *= 2;
		}
		strcpy(employee->last_name, str);
	}

	if (column == COL_BIRTHDAY)
	{
		sscanf(str, "%d/%d/%d",
			&employee->birthday->day,
			&employee->birthday->month,
			&employee->birthday->year);
	}

	if (column == COL_ENTRY_DATE)
	{
		sscanf(str, "%d/%d/%d",
			&employee->entry_date->day,
			&employee->entry_date->month,
			&employee->entry_date->year);
	}

	if (column == COL_LEAVING_DATE)
	{
		sscanf(str, "%d/%d/%d",
			&employee->leaving_date->day,
			&employee->leaving_date->month,
			&employee->leaving_date->year);
	}
}

void h_employees_parse(s_arr_employees* array, const char* str)
{
	if (array == NULL || str == NULL)
		return;

	int i;
	int j;
	int k;
	int delimiter = -1;
	int column = 1;
	char buffer[CSV_BUFFER];
	for (i = 0; str[i] != '\0'; i++)
	{

		if (str[i] == CSV_COLUMN_DELIMITER || str[i] == CSV_NEW_LINE_DELIMITER)
		{
			for (j = delimiter + 1, k = 0; j < i; j++, k++)
			{
				buffer[k] = str[j];
			}

			h_employees_pair(&array->employees[array->used], buffer, column);
			memset(buffer, 0, CSV_BUFFER);
			delimiter = i;
			column++;
		}

		if (str[i] == CSV_NEW_LINE_DELIMITER)
		{
			column = 1;
			array->used++;
		}
	}
}