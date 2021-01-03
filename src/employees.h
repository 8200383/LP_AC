//
// Created by Rui Gonçalves on 11/12/2020.
//

#ifndef GESTAODEFUNCIONARIOS_FUNCIONARIOS_H
#define GESTAODEFUNCIONARIOS_FUNCIONARIOS_H

#include "calendar.h"
#include "error.h"
#include "util.h"

#define PHONE_NUMBER_SIZE 9
#define MAX_VALUE 9999

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
	char role;
	char* first_name;
	char* last_name;
	char* phone;
	e_marital_status marital_status;
	s_date *birthday, *entry_date, *leaving_date;
} s_employee_record;

typedef struct
{
	s_employee_record* employees;
	int used;
	int max_capacity;
} s_arr_employees;

char* get_phone_number();

int random_number();

int ask_status();

void register_employee(s_employee_record* employee);

s_arr_employees* h_employee_alloc(int initial_capacity);

s_arr_employees* h_employees_alloc(int initial_capacity);

s_error* h_employees_parse(s_arr_employees* array, char* str);

#endif //GESTAODEFUNCIONARIOS_FUNCIONARIOS_H
