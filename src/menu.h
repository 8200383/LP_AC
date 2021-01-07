#ifndef MENU_H
#define MENU_H

#include "irs.h"
#include "iss.h"
#include "employees.h"

void h_menu_irs(
	s_arr_irs* single_table,
	s_arr_irs* unique_holder_table,
	s_arr_irs* two_holders_table);

void h_menu_seg_social(s_arr_seg_social* seg_social_table);

void h_menu_processing(
	s_arr_irs* single_table,
	s_arr_irs* unique_holder_table,
	s_arr_irs* two_holders_table,
	s_arr_seg_social* seg_social_table
);

void h_menu_employees(s_arr_employees* employees);

#endif //MENU_H
