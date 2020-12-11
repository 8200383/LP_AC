#include "util.h"
#include "table.h"
#include "strs.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
	s_table* not_married_table;
	char* not_married_str;
	int not_married_len;

	fprintf(stdout, "%s", H_STRS_MENU);
	fprintf(stdout, "%s", H_STRS_SAVE_MENU);

	not_married_str = h_util_file_read("../assets/table_not_married.csv");
	if (not_married_str == NULL)
		return 1;

	not_married_len = h_util_get_lines_from_str(not_married_str);
	not_married_table = h_table_alloc(not_married_len);
	if (not_married_table == NULL)
		return 2;


	h_table_init_from_str(not_married_table, not_married_len, not_married_str);


	for (int i = 0; i < not_married_len; i++) {
		fprintf(stdout, "%.2f\n", not_married_table[i].monthly_pay);
	}


	free(not_married_table);


	return 0;
}
