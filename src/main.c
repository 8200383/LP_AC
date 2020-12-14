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
	int not_married_table_size;
	s_irs* not_married_table;

	not_married_table_size = 0;
	not_married_table = irs_init("../assets/table_not_married.csv", &not_married_table_size);

	return 0;
}
