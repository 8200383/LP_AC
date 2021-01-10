/**
 * @file reports.h
 * @author Micael Dias, Rui Gonçalves, Hugo Carvalho
 * @date 7/1/2021
 * @brief Functions for company reports
 */

#ifndef REPORTS_H
#define REPORTS_H

#include "employees.h"

/** @const EMPLOYEE_SENIORITY Represents the time in years an employee is considered senior */
#define EMPLOYEE_SENIORITY 5

/*
 * TODO Quem são os trabalhadores com maior número de dependentes
 * TODO Percentagem de trabalhadores casados, solteiros e divorciados
 * TODO Quem são os trabalhadores com mais bônus mensal
 * TODO Quem são os trabalhadores com o subsídio de alimentação mais alto
 *
 * NOTA:
 * Todos os commits devem ser dados com #15 na msg
 */

/**
 * Shows all the senior employees according to EMPLOYEE_SENIORITY
 * @param employees_array The array of employees
 */
void h_reports_senior_employees(s_arr_employees* employees_array);

/**
 *
 * @param employees_array The array of employees
 */
void h_reports_marital_percentage(s_arr_employees* employees_array);

#endif //REPORTS_H
