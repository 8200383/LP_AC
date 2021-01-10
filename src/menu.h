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

/*
 TODO: Otima idea mas n sei se existe tempo pra isto
void h_iss_load (s_arr_irs* irs_array);
void h_employees_load (s_arr_employees* employees_table);
 */

#endif //MENU_H
