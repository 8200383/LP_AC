//
// Created by Rui Gonçalves on 11/12/2020.
//

#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#include "calendar.h"
#include "util.h"

#define MAX_VALUE 9999
#define CSV_COLUMN_DELIMITER ','
#define CSV_NEW_LINE_DELIMITER '\n'
#define CSV_BUFFER 50
#define MAX_DEPENDENT_NUMBER 5
#define MAX_PHONE_NUMBER 9

typedef enum
{
	COL_CODE_FUNC = 1,
	COL_FIRST_NAME = 2,
	COL_LAST_NAME = 3,
	COL_PHONE_NUMBER = 4,
	COL_MARITAL_STATUS = 5,
	COL_ROLE = 6,
	COL_NUM_DEPENDENTS = 7,
	COL_BIRTHDAY = 8,
	COL_ENTRY_DATE = 9,
	COL_LEAVING_DATE = 10
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
	int role;
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

s_arr_employees* h_employees_alloc(int initial_capacity);
int h_employees_randomize();
int h_employees_ask_status();
void h_employees_add(s_arr_employees* array);
void h_employees_pair(s_employee_record* employee, char* str, int column);
void h_employees_parse(s_arr_employees* array, const char* str);
void h_employees_print(s_arr_employees* array);
void h_employees_edit(s_arr_employees* array);
int h_employees_verify_phone(char* str);


#endif //EMPLOYEES_H
