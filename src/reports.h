/**
 * @file reports.h
 * @author Micael Dias, Rui Gonçalves, Hugo Carvalho
 * @date 7/1/2021
 * @brief Functions for company analsys/reports
 */

#ifndef REPORTS_H
#define REPORTS_H

#include "employees.h"

/** @const EMPLOYEE_SENIORITY Represents the time in years an employee is considered senior */
#define EMPLOYEE_SENIORITY 5

/*
 * TODO: Quem são os trabalhadores mais antigos da empresa
 * TODO: Quem são os trabalhadores com maior numero de dependentes
 * TODO: Quem são os trabalhadores mais jovens
 * TODO: Qual a percentagem de trabalhodores casados, solteiros e divorciados
 *
 * NOTA:
 * Uma função para cada um, no final juntar tudo numa função
 *
 * NOTA:
 * Todos os commits devem ser dados com #15 na menssagem pff
 */

/**
 *
 * @param arr_employees
 */
void h_reports_senior_employees(s_arr_employees* arr_employees);

#endif //REPORTS_H
