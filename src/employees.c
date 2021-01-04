
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "employees.h"

s_arr_employees* h_employees_alloc(int initial_capacity)
{
	s_arr_employees* array_employees;
	int i;

	if (!initial_capacity)
		return NULL;

	array_employees = malloc(sizeof(s_arr_employees));
	if (array_employees == NULL)
		return NULL;

	array_employees->employees = malloc(sizeof(s_employee_record) * initial_capacity);
	if (array_employees->employees == NULL)
		return NULL;

	array_employees->used = 0;
	array_employees->max_capacity = initial_capacity;

	for (i = 0; i <= array_employees->max_capacity; i++)
	{
		array_employees->employees[i].code = 0;
		array_employees->employees[i].number_dependents = 0;
		array_employees->employees[i].role = '\0';
		array_employees->employees[i].first_name = NULL;
		array_employees->employees[i].last_name = NULL;
		array_employees->employees[i].phone = NULL;
		array_employees->employees[i].marital_status = SINGLE;
		array_employees->employees[i].birthday = NULL;
		array_employees->employees[i].entry_date = NULL;
		array_employees->employees[i].leaving_date = NULL;
	}

	return array_employees;
}

char* get_phone_number()
{
	char* phone_number;

	phone_number = malloc(PHONE_NUMBER_SIZE + 1);
	if (phone_number == NULL)
		return NULL;

	fgets(phone_number, PHONE_NUMBER_SIZE + 1, stdin);

	return phone_number;
}

int random_number()
{
	srand(1);

	return rand() % MAX_VALUE;
}

int ask_status()
{

	switch (h_util_get_int(0, 3, "Civil Status:"))
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

s_error* h_employees_parse(s_arr_employees* array, char* str)
{
	int i, column = 0, offset = -1;

	if (array == NULL || str == NULL)
		return h_error_create(H_ERROR_PARSING, "h_employees_parse()");

	for (i = 0; str[i] != '\0'; i++)
	{
		if (offset == -1 && isalnum(str[i]))
			offset = i;

		if (offset != -1 && str[i] == ',')
		{
			str[i] = '\0';
			printf("%s - %lu\n", str + offset, strlen(str + offset));

			if (isdigit(atoi(str + offset)) != 0)
				puts("É um nr");

			/* switch (column)
			{
			case 0:
				array->employees[array->used].code = atoi(str + offset); // atoi converte strings para inteiros
				column++;
				break;
			case 1:
				array->employees[array->used].number_dependents = atoi(str + offset);
				column++;
				break;
			case 2:
				// array->employees[array->used].role = str[offset];
				column++;
				break;
			case 3:
				// array->employees[array->used].first_name = str[offset];
				column++;
				break;
			case 4:
				// array->employees[array->used].last_name = str[offset];
				column++;
				break;
			case 5:
				// array->employees[array->used].phone = str[offset];
				column++;
				break;
			case 6:
				// array->employees[array->used].marital_status = str[offset];
				column++;
				break;
			case 7:
				sscanf(str + offset, "%d/%d/%d", &array->employees[array->used].birthday->day, &array->employees[array
					->used].birthday->month, &array->employees[array->used].birthday->year);
				column++;
				break;
			case 8:
				sscanf(str + offset, "%d/%d/%d", &array->employees[array->used].entry_date->day, &array->employees[array
					->used].entry_date->month, &array->employees[array->used].entry_date->year);
				column++;
				break;
			case 9:
				sscanf(
					str + offset, "%d/%d/%d", &array->employees[array->used].leaving_date->day, &array->employees[array
						->used].leaving_date->month, &array->employees[array->used].leaving_date->year);
				column = 0;
				break;
			} */
			offset = -1;
		}

		if (str[i] == '\n')
			array->used++;
	}

	return NULL;

}