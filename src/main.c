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

	char* single_str;
	char* unique_holder_str;
	char* two_holders_str;

	s_irs* single_table;
	s_irs* unique_holder_table;
	s_irs* two_holders_table;

	single_size = 0;
	unique_holder_size = 0;
	two_holders_size = 0;

	/*
	 * IRS: Tabela I - Não Casado
	 * ---------------------------------------------------------------------------------------------------------
	 */
	single_str = h_util_file_read(H_PATH_SINGLE);
	if (single_str == NULL)
	{
		error = h_error_create(H_ERROR_READ, H_PATH_SINGLE);
		return error;
	}

	single_size = h_util_get_lines_from_str(single_str);
	single_table = h_irs_alloc(single_size);
	if (single_table == NULL)
	{
		error = h_error_create(H_ERROR_ALLOCATION, H_PATH_SINGLE);
		free(single_str);
		return error;
	}

	error = h_irs_parse(single_table, single_str, h_irs_build);
	if (error)
	{
		free(single_str);
		free(single_table);
		return error;
	}

	free(single_str);

	/*
	 * IRS: Tabela II - Casado Unico Titular
	 * ---------------------------------------------------------------------------------------------------------
	 */
	unique_holder_str = h_util_file_read(H_PATH_UNIQUE_HOLDER);
	if (unique_holder_str == NULL)
	{
		error = h_error_create(H_ERROR_READ, H_PATH_SINGLE);
		free(single_table);
		return error;
	}

	unique_holder_size = h_util_get_lines_from_str(unique_holder_str);
	unique_holder_table = h_irs_alloc(unique_holder_size);
	if (unique_holder_table == NULL)
	{
		error = h_error_create(H_ERROR_ALLOCATION, H_PATH_SINGLE);
		free(single_table);
		free(unique_holder_str);
		return error;
	}

	error = h_irs_parse(unique_holder_table, unique_holder_str, h_irs_build);
	if (error)
	{
		free(single_table);
		free(unique_holder_str);
		free(unique_holder_table);
		return error;
	}

	free(unique_holder_str);

	/*
	 * IRS: Tabela III - Casado Dois Titulares
	 * ---------------------------------------------------------------------------------------------------------
	 */
	two_holders_str = h_util_file_read(H_PATH_UNIQUE_HOLDER);
	if (two_holders_str == NULL)
	{
		error = h_error_create(H_ERROR_READ, H_PATH_SINGLE);
		free(single_table);
		free(unique_holder_table);
		return error;
	}

	two_holders_size = h_util_get_lines_from_str(two_holders_str);
	two_holders_table = h_irs_alloc(two_holders_size);
	if (two_holders_table == NULL)
	{
		error = h_error_create(H_ERROR_ALLOCATION, H_PATH_SINGLE);
		free(single_table);
		free(unique_holder_table);
		free(two_holders_str);
		return error;
	}

	error = h_irs_parse(two_holders_table, two_holders_str, h_irs_build);
	if (error)
	{
		free(single_table);
		free(unique_holder_table);
		free(two_holders_str);
		free(two_holders_table);
		return error;
	}

	free(two_holders_str);

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
