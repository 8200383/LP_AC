/* 
 * Created by Micael Dias on 14/12/20.
 */

#include <stdio.h>

#include "menu.h"
#include "colors.h"
#include "strs.h"
#include "util.h"

void h_menu_irs(
	s_irs* not_married_table,
	int not_married_table_size,
	s_irs* married_unique_holder_table,
	int married_unique_holder_table_size,
	s_irs* married_two_holders_table,
	int married_two_holders_size)
{
	char op;

	fprintf(stdout, "%s", H_STRS_IRS_MENU);
	fprintf(stdout, GREEN("> "));
	scanf(" %c", &op);

	switch (op)
	{
	case '1':
		h_irs_print(not_married_table, not_married_table_size);
		break;
	case '2':
		fprintf(stdout, "%s", H_STRS_IRS_TABLE_EDIT("Tabela I - NÃO CASADO"));
		h_irs_edit(not_married_table, h_util_get_positive_int());
		break;
	case '3':
		h_irs_print(married_unique_holder_table, married_unique_holder_table_size);
		break;
	case '4':
		fprintf(stdout, "%s", H_STRS_IRS_TABLE_EDIT("Tabela II - CASDO UNICO TITULAR"));
		h_irs_edit(married_unique_holder_table, h_util_get_positive_int());
		break;
	case '5':
		h_irs_print(married_two_holders_table, married_two_holders_size);
		break;
	case '6':
		fprintf(stdout, "%s", H_STRS_IRS_TABLE_EDIT("Tabela III - CASDO DOIS TITULARES"));
		h_irs_edit(married_two_holders_table, h_util_get_positive_int());
		break;
	case '0':
		break;
	default:
		fprintf(stderr, "Invalid Option\n");
		break;
	}
}