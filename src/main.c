#include "util.h"
#include "table.h"
#include "strs.h"

#include <stdio.h>
#include <stdlib.h>

void menu()
{
	fprintf(stdout, "%s", H_STRS_MENU);

	switch (getchar())
	{
	case 'B':
		system("clear");
		fprintf(stdout, "%s", H_STRS_TABLES_MENU);
		break;
	default:
		fprintf(stderr, "Invalid Option\n");
	}

/*
	fprintf(stdout, "%s", H_STRS_SAVE_MENU);
	fprintf(stdout, "%s", H_STRS_TABLES_MENU);
	fprintf(stdout, "%s", H_STRS_VIEW_TABLES_MENU);
 */
}

int test_tables()
{
	s_table* not_married_table;
	char* not_married_str;
	int not_married_len;

	not_married_str = h_util_file_read("../assets/table_not_married.csv");
	if (not_married_str == NULL)
		return 1;

	not_married_len = h_util_get_lines_from_str(not_married_str);
	not_married_table = h_table_alloc(not_married_len);
	if (not_married_table == NULL)
		return 2;

	h_table_init_from_str(not_married_table, not_married_str);

	for (int i = 0; i < not_married_len; i++)
	{
		fprintf(stdout, "\n%.2f€\n", not_married_table[i].monthly_pay);

		int j = 0;
		while (not_married_table[i].percentage_per_dependent[j] != '\0')
		{
			fprintf(stdout, "%f%%\n", not_married_table[i].percentage_per_dependent[j]);
			j++;
		}
	}

	free(not_married_table);

	return 0;
}

int main()
{
	menu();

	return 0;
}
