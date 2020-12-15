/* 
 * Created by Micael Dias on 14/12/20.
 */

#ifndef _MENU_H_
#define _MENU_H_

#include "irs.h"

void h_menu_irs(
	s_irs* not_married_table,
	int not_married_table_size,
	s_irs* married_unique_holder_table,
	int married_unique_holder_table_size,
	s_irs* married_two_holders_table,
	int married_two_holders_size);

#endif //_MENU_H_
