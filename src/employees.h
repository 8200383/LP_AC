/**
 * @file employees.h
 * @author Rui Gonçalves, Micael Dias
 * @date 11/12/2020
 * @brief Functions to handle employees
 */

#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#include "calendar.h"

#define MAX_VALUE 9999
#define CSV_COLUMN_DELIMITER ','
#define CSV_NEW_LINE_DELIMITER '\n'
#define CSV_BUFFER 50
#define PHONE_NUMBER_SIZE 9

/**
 * @enum e_columns
 */
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
	COL_LEAVING_DATE = 10,
	COL_BASE_SALARY = 11
} e_columns;

/**
 * @enum e_marial_status
 */
typedef enum
{
	SINGLE,
	MARRIED,
	DIVORCED,
	WIDOWED
} e_marital_status;

/**
 * @struct
 */
typedef struct
{
	int code;
	int number_dependents;
	int role;
	char* first_name;
	char* last_name;
	int phone_number;
	float hourly_rate;
	e_marital_status marital_status;
	s_date* birthday, * entry_date, * leaving_date;
} s_employee;

/**
 * @struct
 */
typedef struct
{
	s_employee* employees;
	int used;
	int max_capacity;
} s_arr_employees;

/**
 *
 * @param initial_capacity
 * @return
 */
s_arr_employees* h_employees_alloc(int initial_capacity);

/**
 *
 * @return
 */
int h_employees_randomize();

/**
 *
 * @return
 */
int h_employees_get_marital_status();

/**
 *
 * @return
 */
int h_employees_get_phone_number();

/**
 *
 * @param employee
 */
void h_employees_get_fields(s_employee* employee);

/**
 *
 * @param array
 */
void h_employees_add(s_arr_employees* array);

/**
 *
 * @param employee
 * @param str
 * @param column
 */
void h_employees_pair(s_employee* employee, char* str, int column);

/**
 *
 * @param array
 * @param str
 */
void h_employees_parse(s_arr_employees* array, const char* str);

/**
 *
 * @param array
 */
void h_employees_print(s_arr_employees* array);

/**
 *
 * @param array
 */
void h_employees_edit(s_arr_employees* array);

/**
 *
 * @param str
 * @return
 */
int h_employees_verify_phone(char* str);

#endif //EMPLOYEES_H