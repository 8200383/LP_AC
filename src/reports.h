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
 * TODO Quem são os trabalhadores mais antigos da empresa
 * TODO Quem são os trabalhadores com maior número de dependentes
 * TODO Qual a percentagem de trabalhadores casados, solteiros e divorciados
 * TODO Quem são os trabalhadores com mais bônus mensal
 * TODO Quem são os trabalhadores com o subsídio de alimentação mais alto
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
