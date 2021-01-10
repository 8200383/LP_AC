/**
 * @file menu.h
 * @author Micael Dias, Hugo Carvalho, Rui Gonçalves
 * @date 8/1/2020
 * @brief Menus
 */

#ifndef MENU_H
#define MENU_H

#include "proc.h"
#include "strs.h"
#include "util.h"
#include "paths.h"
#include "colors.h"

/**
 * IRS Menu
 * @param single_array Single Table
 * @param unique_holder_array Married Unique Holder Table
 * @param two_holders_array Married Two Holders Table
 */
void h_menu_irs(
	s_arr_irs* single_array,
	s_arr_irs* unique_holder_array,
	s_arr_irs* two_holders_array);

/**
 * ISS Menu
 * @param iss_array The ISS array
 */
void h_menu_iss(s_arr_iss* iss_array);

/**
 * Salary Processing Menu
 * @param single_array Single Table
 * @param unique_holder_array Married Unique Holder Table
 * @param two_holders_array Married Two Holders Table
 * @param iss_array The ISS array
 * @param employees_array The array of employees
 */
void h_menu_processing(
	s_arr_irs* single_array,
	s_arr_irs* unique_holder_array,
	s_arr_irs* two_holders_array,
	s_arr_iss* iss_array,
	s_arr_employees* employees_array
);

/**
 * Employees Menu
 * @param employees_array The array of employees
 * @param iss_array The ISS array
 */
void h_menu_employees(s_arr_employees* employees_array, s_arr_iss* iss_array);

/**
 * Reports Menu
 * @param employees_array The array of employees
 */
void h_menu_reports(s_arr_employees* employees_array);

/*
 TODO: Otima idea mas n sei se existe tempo pra isto
void h_iss_load (s_arr_irs* irs_array);
void h_employees_load (s_arr_employees* employees_table);
 */

#endif //MENU_H
