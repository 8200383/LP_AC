/**
 * @file employees.h
 * @author Rui Gonçalves, Micael Dias
 * @date 11/12/2020
 * @brief Functions to handle employees
 */

#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#include "calendar.h"
#include "iss.h"
#include "colors.h"

#define BUFFER_SIZE 64
#define MAX_VALUE 9999
#define CSV_COLUMN_DELIMITER ','
#define CSV_NEW_LINE_DELIMITER '\n'
#define CSV_BUFFER 50
#define PHONE_NUMBER_SIZE 9
#define MAX_HOURLY_RATE 20
#define MAX_FOOD_ALLOWANCE 20

#define PRINT_TEMPLATE_STRING \
"[%d] %d | %s | %s | %d | %d Dependentes | %s | %s | " \
"%d/%d/%d | %d/%d/%d | %d/%d/%d | %.2f€ | %.2f€ | %d Titular(es) %s\n"

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
	COL_HOURLY_RATE = 11,
	COL_BASE_FOOD_ALLOWANCE = 12,
	COL_HOLDERS = 13
} e_columns;

/**
 * @enum e_holders
 */
typedef enum
{
	NONE = 0,
	UNIQUE_HOLDER = 1,
	TWO_HOLDERS = 2
} e_holders;

/**
 * @enum e_marial_status
 */
typedef enum
{
	SINGLE = 0,
	MARRIED = 1,
	DIVORCED = 2,
	WIDOWED = 3
} e_marital_status;

/**
 * @struct
 */
typedef struct
{
	int code;
	int role;
	int dependents;
	int phone_number;
	float hourly_rate;
	float base_food_allowance;
	char* first_name;
	char* last_name;
	e_holders holders;
	e_marital_status marital_status;
	s_date* birthday, * entry_date, * leaving_date;
	int removed;
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
void h_employees_get_fields(s_employee* employee, s_arr_iss* iss_array);

/**
 *
 * @param array
 */
void h_employees_add(s_arr_employees* array, s_arr_iss* iss_array);

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
 * @param iss_array
 */
void h_employees_print(s_arr_employees* array, s_arr_iss* iss_array);

/**
 *
 * @param array
 * @param iss_array
 */
void h_employees_edit(s_arr_employees* array, s_arr_iss* iss_array);
/**
 *
 * @param str
 * @return
 */
int h_employees_verify_phone(char* str);

/**
 *
 * @param status
 * @return
 */
char* h_employees_str_from_marital_status(e_marital_status status);

/**
 *
 * @param array
 * @return
 */

void h_employees_delete(s_arr_employees* array);

/**
 *
 * @param array, path
 * @return
 */

void h_employees_save(s_arr_employees* array, const char* path);

/**
 *
 * @param holders
 * @return
 */

char* h_employees_str_from_holders(e_holders holders);

#endif //EMPLOYEES_H