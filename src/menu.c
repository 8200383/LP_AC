/* 
 * Created by Micael Dias on 14/12/20.
 */

#include <stdio.h>

#include "menu.h"
#include "colors.h"
#include "strs.h"
#include "util.h"

void h_menu_irs(
	s_irs_tables tables,
	int single_size,
	int unique_holder_size,
	int two_holders_size)
{
	int op;

	fprintf(stdout, "%s", H_STRS_IRS_MENU);
	fprintf(stdout, GREEN("> "));
	scanf(" %d", &op);

	switch (op)
	{
	case 1:
		h_irs_print(tables.single, single_size);
		break;
	case 2:
		fprintf(stdout, "%s", H_STRS_IRS_TABLE_EDIT("Tabela I - NÃO CASADO"));
		h_irs_edit(tables.single, single_size, h_util_get_positive_int());
		break;
	case 3:
		h_irs_print(tables.unique_holder, unique_holder_size);
		break;
	case 4:
		fprintf(stdout, "%s", H_STRS_IRS_TABLE_EDIT("Tabela II - CASADO UNICO TITULAR"));
		h_irs_edit(tables.unique_holder, unique_holder_size, h_util_get_positive_int());
		break;
	case 5:
		h_irs_print(tables.two_holders, two_holders_size);
		break;
	case 6:
		fprintf(stdout, "%s", H_STRS_IRS_TABLE_EDIT("Tabela III - CASADO DOIS TITULARES"));
		h_irs_edit(tables.two_holders, two_holders_size, h_util_get_positive_int());
		break;
	case '0':
		break;
	default:
		fprintf(stderr, "Invalid Option\n");
		break;
	}
}