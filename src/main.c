#include <stdio.h>

#include "util.h"
#include "irs.h"
#include "iss.h"
#include "menu.h"
#include "strs.h"
#include "paths.h"

#define INITIAL_CAPACITY 50

int main_menu()
{
	int op;

	int employees_size;
	char* employees_str;

	s_arr_irs* single_table;
	s_arr_irs* unique_holder_table;
	s_arr_irs* two_holders_table;
	s_arr_iss* seg_social_table;
	s_arr_employees* employees_table;

	/*
	 * IRS
	 * ---------------------------------------------------------------------------------------------------------
	 */

	single_table = h_irs_alloc(INITIAL_CAPACITY);
	if (single_table == NULL)
	{
		return -1;
	}

	unique_holder_table = h_irs_alloc(INITIAL_CAPACITY);
	if (unique_holder_table == NULL)
	{
		free(single_table);
		return -1;
	}

	two_holders_table = h_irs_alloc(INITIAL_CAPACITY);
	if (two_holders_table == NULL)
	{
		free(single_table);
		free(unique_holder_table);
		return -1;
	}

	/*
	 * Segurança Social
	 * ---------------------------------------------------------------------------------------------------------
	 */

	seg_social_table = h_iss_alloc(INITIAL_CAPACITY);
	if (seg_social_table == NULL)
	{
		free(single_table);
		free(unique_holder_table);
		free(two_holders_table);
		return -1;
	}

	/*
	 * Gestão de Funcionários
	 * ---------------------------------------------------------------------------------------------------------
	 */

	employees_size = 0;
	employees_str = h_util_file_read(H_PATH_EMPLOYEES, &employees_size);

	employees_table = h_employees_alloc(employees_size);

	h_employees_parse(employees_table, employees_str);

	do
	{
		fprintf(stdout, "%s", H_STRS_MENU);
		op = h_util_get_int(0, 9, "Opção?");

		switch (op)
		{
			case 1:
				h_menu_irs(single_table, unique_holder_table, two_holders_table);
				break;
			case 2:
				h_menu_seg_social(seg_social_table);
				break;
			case 3:
				h_menu_employees(employees_table);
				break;
			case 4:
				h_menu_processing(single_table,
					unique_holder_table,
					two_holders_table,
					seg_social_table,
					employees_table);
				break;
			case 9:
				// TODO: Guardar todas
				break;
			default:
				break;
		}
	} while (op != 0);

	h_irs_free(single_table);
	h_irs_free(unique_holder_table);
	h_irs_free(two_holders_table);
	h_iss_free(seg_social_table);

	return 0;
}

int main()
{
	return main_menu();
}
