#include "util.h"
#include "table.h"

#include <stdio.h>

int main()
{

	int not_married_str_len = 0;
	char* not_married_str = h_util_file_read("../assets/table_not_married.csv", not_married_str_len);
	if (not_married_str == NULL)
		return 1;

	s_table* not_married_table = h_table_alloc(not_married_str_len);
	if (not_married_table == NULL)
		return 2;

	h_table_init_from_str(not_married_table, not_married_str);

	return 0;
}
