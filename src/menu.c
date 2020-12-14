/* 
 * Created by Micael Dias on 14/12/20.
 */

#include <stdio.h>

#include "menu.h"
#include "colors.h"
#include "strs.h"

void h_menu_irs(s_irs* not_married_table, int not_married_table_size)
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
		printf("edit");
		break;
	case '0':
		break;
	default:
		fprintf(stderr, "Invalid Option\n");
		break;
	}
}