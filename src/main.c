#include <stdio.h>
#include <stdlib.h>

#include "main.h"

s_error* main_menu()
{
	s_error* error;

	unsigned int op;

	int single_size;
	int unique_holder_size;
	int two_holders_size;

	s_irs* single_table;
	s_irs* unique_holder_table;
	s_irs* two_holders_table;

	single_size = 0;
	unique_holder_size = 0;
	two_holders_size = 0;

	single_table = h_irs_init(H_PATH_SINGLE, &single_size);
	if (single_table == NULL)
	{
		error = h_error_create(H_ERROR_READ, H_PATH_SINGLE);
		return error;
	}

	unique_holder_table = h_irs_init(H_PATH_UNIQUE_HOLDER, &unique_holder_size);
	if (unique_holder_table == NULL)
	{
		error = h_error_create(H_ERROR_READ, H_PATH_UNIQUE_HOLDER);
		free(single_table);
		return error;
	}

	two_holders_table = h_irs_init(H_PATH_TWO_HOLDERS, &two_holders_size);
	if (two_holders_table == NULL)
	{
		error = h_error_create(H_ERROR_READ, H_PATH_TWO_HOLDERS);
		free(single_table);
		free(unique_holder_table);
		return error;
	}

	s_irs_tables irs_tables = {
		single_table,
		unique_holder_table,
		two_holders_table
	};

	do
	{
		fprintf(stdout, "%s", H_STRS_MENU);
		fprintf(stdout, GREEN("> "));
		scanf(" %u", &op);

		switch (op)
		{
		case 1:
			h_menu_irs(irs_tables, single_size, unique_holder_size, two_holders_size);
			break;
		case 9:
			h_irs_write(irs_tables.single, single_size, H_PATH_SINGLE);
			h_irs_write(irs_tables.unique_holder, unique_holder_size, H_PATH_UNIQUE_HOLDER);
			h_irs_write(irs_tables.two_holders, two_holders_size, H_PATH_TWO_HOLDERS);
			break;
		default:
			break;
		}
	} while (op != 0);

	free(single_table);
	free(unique_holder_table);
	free(two_holders_table);

	return NULL;
}

int main()
{
	s_error* error;

	error = main_menu();
	if (error)
	{
		h_error_print(error);
		h_error_free(error);
		return -1;
	}

	return 0;
}
