#include "util.h"
#include "irs.h"
#include "strs.h"

#include <stdio.h>
#include <stdlib.h>

void menu();
void irs_menu();
int irs_preview();

void menu()
{
	char op;

	fprintf(stdout, "%s", H_STRS_MENU);
	fprintf(stdout, GREEN("> "));
	scanf(" %c", &op);

	switch (op)
	{
	case '1':
		irs_menu();
		break;
	case '9':
		fprintf(stdout, H_STRS_SAVE_MENU);
		break;
	case '0':
		fprintf(stdout, RED("EXITING"));
		exit(0);
	default:
		fprintf(stderr, "Invalid Option\n");
		exit(1);
	}
}

void irs_menu()
{
	char op;

	fprintf(stdout, "%s", H_STRS_IRS_MENU);
	fprintf(stdout, GREEN("> "));
	scanf(" %c", &op);

	switch (op)
	{
	case '1':
		irs_preview();
		break;
	case '0':
		menu();
	default:
		fprintf(stderr, "Invalid Option\n");
		exit(1);
	}
}

int irs_preview()
{
	s_irs* not_married_arr;
	char* not_married_str;
	int not_married_len;

	not_married_str = h_util_file_read("../assets/table_not_married.csv");
	if (not_married_str == NULL)
		return -1;

	not_married_len = h_util_get_lines_from_str(not_married_str);
	not_married_arr = h_irs_alloc(not_married_len);
	if (not_married_arr == NULL)
	{
		free(not_married_str);
		return -2;
	}

	h_irs_init_from_str(not_married_arr, not_married_str);
	h_irs_print(not_married_arr, not_married_len);

	free(not_married_arr);

	return 0;
}

int main()
{
	menu();

	return 0;
}
