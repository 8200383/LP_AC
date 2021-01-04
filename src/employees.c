#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "employees.h"
#include "util.h"

int first_name_buffer_size = 64;
int last_name_buffer_size = 64;

s_arr_employees* h_employees_alloc(int initial_capacity)
{
	s_arr_employees* array;
	int i, j;

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
		array->employees[i].code = 0;
		array->employees[i].number_dependents = 0;
		array->employees[i].role = '\0';
		array->employees[i].marital_status = SINGLE;

		array->employees[i].first_name = malloc(first_name_buffer_size * sizeof(char));
		if (array->employees[array->used].first_name == NULL)
			return NULL;

		memset(array->employees[i].first_name, '\0', first_name_buffer_size);

		array->employees[i].last_name = malloc(last_name_buffer_size * sizeof(char));
		if (array->employees[array->used].last_name == NULL)
			return NULL;

		memset(array->employees[i].last_name, '\0', last_name_buffer_size);


		for (j = 0; j < 10; j++)
			array->employees[i].phone[j] = '\0';
	}

	return array;
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
	int i;
	int offset;
	int column;

	if (array == NULL || str == NULL)
		return h_error_create(H_ERROR_PARSING, "h_employees_parse()");

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
				strcpy(&array->employees[array->used].role, str + offset);

			// Phone number 9 digits
			if (h_util_str_is_digit(str + offset) == 9 && column == COL_PHONE_NUMBER)
				strcpy(array->employees[array->used].phone, str + offset);

			if (h_util_strequal(str + offset, "MARRIED") && column == COL_MARITAL_STATUS)
				array->employees[array->used].marital_status = MARRIED;

			if (h_util_strequal(str + offset, "SINGLE") && column == COL_MARITAL_STATUS)
				array->employees[array->used].marital_status = SINGLE;

			if (h_util_strequal(str + offset, "DIVORCED") && column == COL_MARITAL_STATUS)
				array->employees[array->used].marital_status = DIVORCED;

			if (h_util_is_name(str + offset) == 0 && column == COL_FIRST_NAME)
			{
				if (strlen(str + offset) >= first_name_buffer_size)
				{
					array->employees[array->used].first_name =
						realloc(array->employees[array->used].first_name, first_name_buffer_size * 2);

					if (array->employees[array->used].first_name == NULL)
						return h_error_create(H_ERROR_ALLOCATION, "Cannot reallocate first_name");

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
						return h_error_create(H_ERROR_ALLOCATION, "Cannot reallocate first_name");

					last_name_buffer_size *= 2;
				}
				strcpy(array->employees[array->used].last_name, str + offset);
			}

			if (h_calendar_check_str(str + offset) == 1 && column == COL_BIRTHDAY)
			{
				array->employees[array->used].birthday = h_calendar_init(str + offset);

				if (array->employees[array->used].birthday == NULL)
					return h_error_create(H_ERROR_ALLOCATION, "Cannot initialize birthday");
			}

			if (h_calendar_check_str(str + offset) == 1 && column == COL_ENTRY_DATE)
			{
				array->employees[array->used].entry_date = h_calendar_init(str + offset);

				if (array->employees[array->used].entry_date == NULL)
					return h_error_create(H_ERROR_ALLOCATION, "Cannot initialize entry_date");
			}

			if (h_calendar_check_str(str + offset) == 1 && column == COL_LEAVING_DATE)
			{
				array->employees[array->used].leaving_date = h_calendar_init(str + offset);

				if (array->employees[array->used].leaving_date == NULL)
					return h_error_create(H_ERROR_ALLOCATION, "Cannot initialize leaving_date");
			}

			column++;
			offset = -1;
		}

		if (str[i] == '\n')
			array->used++;
	}

	return NULL;
}