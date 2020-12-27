//
// Created by Rui Gonçalves on 11/12/2020.
//

#ifndef GESTAODEFUNCIONARIOS_FUNCIONARIOS_H
#define GESTAODEFUNCIONARIOS_FUNCIONARIOS_H

#include "calendar.h"

#define MAX_STRING 100
#define PHONE_NUMBER_SIZE 9
#define MAX_VALUE 9999

typedef enum {
    SINGLE,
    MARRIED,
    DIVORCED,
    WIDOWED
} e_marital_status;

typedef struct {
    int code, number_dependents, role;
    char name[MAX_STRING];
    char *phone;
    float value_hour, food_allowance;
    e_marital_status marital_status;
    s_date *birthday, *entry_date, *leaving_date;
} s_employee_record;

char *get_phone_number();

int random_number();

int ask_status();

void register_employee(s_employee_record *employee);

#endif //GESTAODEFUNCIONARIOS_FUNCIONARIOS_H
