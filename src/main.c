#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "irs.h"
#include "menu.h"
#include "strs.h"
#include "error.h"

s_irs* irs_init(const char* path, int* size);

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
	s_error* error;

	char op;
	int not_married_size;
	int married_unique_holder_size;
	int married_two_holders_size;
	s_irs* not_married_table;
	s_irs* married_unique_holder_table;
	s_irs* married_two_holders_table;

	error = NULL;
	not_married_size = 0;
	married_unique_holder_size = 0;
	married_two_holders_size = 0;

	not_married_table = irs_init("../data/table_not_married.csv", &not_married_size);
	if (not_married_table == NULL)
		error = h_error_create(H_ERROR_READ, "Can't read file table_not_married.csv");

	married_unique_holder_table = irs_init("../data/table_married_unique_holder.csv", &married_unique_holder_size);
	if (married_unique_holder_table == NULL)
		error = h_error_create(H_ERROR_READ, "Can't read file table_married_unique_holder.csv");

	married_two_holders_table = irs_init("../data/table_married_two_holders.csv", &married_two_holders_size);
	if (married_unique_holder_table == NULL)
		error = h_error_create(H_ERROR_READ, "Can't read file table_married_two_holders.csv");

	if (error != NULL) {
		fprintf(stderr, RED("TYPE: %d\t"), error->error_type);
		fprintf(stderr, RED("MSG: %s\n"), error->msg);
		return -1;
	}

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

	free(not_married_table);
	free(married_unique_holder_table);
	free(married_two_holders_table);

	fprintf(stdout, RED("EXITING"));
	return 0;
}
