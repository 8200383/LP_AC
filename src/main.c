#include <stdio.h>
#include <stdlib.h>

#include "main.h"

s_irs* irs_init(const char* path, int* size)
{
	s_irs* data;
	char* str;
	int n_lines;
	int err;

	if (path == NULL || size == NULL)
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
	err = h_irs_parse(data, str, h_irs_build);
	if (err)
	{
		free(str);
		return NULL;
	}

	return data;
}

int main()
{
	char op;

	int single_size;
	int unique_holder_size;
	int two_holders_size;

	s_irs* single_table;
	s_irs* unique_holder_table;
	s_irs* two_holders_table;

	single_size = 0;
	unique_holder_size = 0;
	two_holders_size = 0;

	single_table = irs_init(H_PATH_SINGLE, &single_size);
	if (single_table == NULL)
		return -1;

	unique_holder_table = irs_init(H_PATH_UNIQUE_HOLDER, &unique_holder_size);
	if (unique_holder_table == NULL)
		return -1;

	two_holders_table = irs_init(H_PATH_TWO_HOLDERS, &two_holders_size);
	if (two_holders_table == NULL)
		return -1;

	s_irs_tables irs_tables = {
		single_table,
		unique_holder_table,
		two_holders_table
	};

	do
	{
		fprintf(stdout, "%s", H_STRS_MENU);
		fprintf(stdout, GREEN("> "));
		scanf(" %c", &op);

		switch (op)
		{
		case '1':
			h_menu_irs(irs_tables, single_size, unique_holder_size, two_holders_size);
			break;
		case '9':
			h_irs_write(irs_tables.single, single_size, H_PATH_SINGLE_BIN);
			h_irs_write(irs_tables.unique_holder, unique_holder_size, H_PATH_UNIQUE_HOLDER_BIN);
			h_irs_write(irs_tables.two_holders, two_holders_size, H_PATH_TWO_HOLDERS_BIN);
			break;
		default:
			break;
		}
	} while (op != '0');

	free(single_table);
	free(unique_holder_table);
	free(two_holders_table);

	fprintf(stdout, RED("EXITING"));
	return 0;
}
