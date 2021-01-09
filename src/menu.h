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

void h_menu_irs(
	s_arr_irs* single_table,
	s_arr_irs* unique_holder_table,
	s_arr_irs* two_holders_table);

void h_menu_seg_social(s_arr_iss* seg_social_table);

void h_menu_processing(
	s_arr_irs* single_table,
	s_arr_irs* unique_holder_table,
	s_arr_irs* two_holders_table,
	s_arr_iss* seg_social_table,
	s_arr_employees* employees
);

void h_menu_employees(s_arr_employees* employees, s_arr_iss* iss_array);

void h_load_single (s_arr_irs* single_table);
void h_load_unique_holder (s_arr_irs* unique_holder_table);
void h_load_two_holders (s_arr_irs* two_holders_table);
void h_load_seg_social (s_arr_iss* seg_social_table);
void h_load_employees (s_arr_employees* employees_table);

#endif //MENU_H
