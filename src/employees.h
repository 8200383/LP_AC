//
// Created by Rui Gonçalves on 11/12/2020.
//

#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#include "calendar.h"
#include "util.h"

#define MAX_VALUE 9999

typedef enum
{
	COL_CODE_FUNC,
	COL_NUM_DEPENDENTS,
	COL_ROLE,
	COL_FIRST_NAME,
	COL_LAST_NAME,
	COL_PHONE_NUMBER,
	COL_MARITAL_STATUS,
	COL_BIRTHDAY,
	COL_ENTRY_DATE,
	COL_LEAVING_DATE
} e_columns;

typedef enum
{
	SINGLE,
	MARRIED,
	DIVORCED,
	WIDOWED
} e_marital_status;

typedef struct
{
	int code;
	int number_dependents;
	char* role;
	char* first_name;
	char* last_name;
	int phone_number;
	e_marital_status marital_status;
	s_date* birthday, * entry_date, * leaving_date;
} s_employee_record;

typedef struct
{
	s_employee_record* employees;
	int used;
	int max_capacity;
} s_arr_employees;

int h_employees_randomize();

int h_employees_ask_status();

void h_employees_add(s_arr_employees* array);

s_arr_employees* h_employees_alloc(int initial_capacity);

void h_employees_parse(s_arr_employees* array, char* str);

void h_employees_print(s_arr_employees* array);

#endif //EMPLOYEES_H
