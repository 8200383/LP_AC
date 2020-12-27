
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "employees.h"
#include "util.h"

char *get_phone_number() {
    char *phone_number;

    phone_number = malloc(PHONE_NUMBER_SIZE + 1);
    if (phone_number == NULL)
        return NULL;

        fgets(phone_number, PHONE_NUMBER_SIZE + 1, stdin);

    return phone_number;
}

int random_number() {
    time_t t;

    srand((unsigned) time(&t));

    return rand() % MAX_VALUE;
}


int ask_status() {

    switch (h_util_get_int(0, 3, "Civil Status:")) {
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

void register_employee(s_employee_record *employee) {
    employee->code = random_number();
    printf("Code: %d\n", employee->code);

    printf("Phone Number: ");
    employee->phone = get_phone_number();

    employee->role = h_util_get_int(0, 100, "Role");

    employee->number_dependents = h_util_get_int(0, 5, "Dependents");

    employee->marital_status = ask_status();

    employee->value_hour = h_util_get_float(0.0f, 100.0f, "Value/hour");

    employee->food_allowance = h_util_get_float(0.0f, 100.0f, "Food Allowance");

    printf("Birthday: \n");
    employee->birthday = get_date();

    printf("Entry date: ");
    employee->entry_date = get_date();
    employee->leaving_date = NULL;
}