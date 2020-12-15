#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "irs.h"
#include "menu.h"
#include "strs.h"

s_irs* irs_init(const char* path, int* size);

s_irs* irs_init(const char* path, int* size)
{
	s_irs* data;
	char* str;
	int n_lines;

	if (path == NULL)
		return NULL;

	str = h_util_file_read(path);
	if (str == NULL)
		return NULL;

	n_lines = h_util_get_lines_from_str(str);
	data = h_irs_alloc(n_lines);
	if (data == NULL)
	{
		free(str);
		return NULL;
	}

	*size = n_lines;
	h_irs_init_from_str(data, str);

	return data;
}

int main()
{
	char op;
	int not_married_size;
	int married_unique_holder_size;
	int married_two_holders_size;
	s_irs* not_married_table;
	s_irs* married_unique_holder_table;
	s_irs* married_two_holders_table;

	not_married_size = 0;
	married_unique_holder_size = 0;
	married_two_holders_size = 0;

	not_married_table = irs_init("../assets/table_not_married.csv", &not_married_size);
	if (not_married_table == NULL)
		return -1;

	married_unique_holder_table = irs_init("../assets/table_married_unique_holder.csv", &married_unique_holder_size);
	if (married_unique_holder_table == NULL)
		return -1;

	married_two_holders_table = irs_init("../assets/table_married_two_holders.csv", &married_two_holders_size);
	if (married_unique_holder_table == NULL)
		return -1;

	do
	{
		fprintf(stdout, "%s", H_STRS_MENU);
		fprintf(stdout, GREEN("> "));
		scanf(" %c", &op);

		switch (op)
		{
		case '1':
			h_menu_irs(
				not_married_table,
				not_married_size,
				married_unique_holder_table,
				married_unique_holder_size,
				married_two_holders_table,
				married_two_holders_size);
			break;
		case '9':
			fprintf(stdout, H_STRS_SAVE_MENU);
			break;
		default:
			break;
		}
	} while (op != '0');

	fprintf(stdout, RED("EXITING"));
	return 0;
}
