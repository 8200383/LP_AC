/**
 * @file reports.h
 * @author Micael Dias, Rui Gonçalves, Hugo Carvalho
 * @date 7/1/2021
 * @brief Functions for company reports
 */

#ifndef REPORTS_H
#define REPORTS_H

#include "employees.h"
#include "proc.h"

/** @const EMPLOYEE_SENIORITY Represents the time in years an employee_retention is considered senior */
#define EMPLOYEE_SENIORITY 5

/*
 * TODO Percentage of employees with the largest number of dependents
 */
/**
 * Shows all the senior employees according to EMPLOYEE_SENIORITY
 * @param employees_array The array of employees
 */
void h_reports_senior_employees(s_arr_employees* employees_array);

/**
 * Gets the percentage of married, single, widowed and divorced employees
 * @param employees_array The array of employees
 */
void h_reports_marital_status(s_arr_employees* employees_array);

/**
 * Gets the percentage of employees of earned a bonus
 * @param spreadsheet The spreadsheet referring to a month
 */
void h_reports_bonus(s_spreadsheet* spreadsheet, s_arr_employees *employees_array);

/**
 * Gets the percentage of employees with the higher food allowance
 * @param spreadsheet The spreadsheet referring to a month
 * @param employees_array The array of employees
 */
void h_reports_food_allowance(s_spreadsheet* spreadsheet, s_arr_employees *employees_array);

#endif //REPORTS_H
