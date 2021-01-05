#include <stdio.h>
#include <stdlib.h>

#include "main.h"

void main_menu()
{
	unsigned int op;

	int single_size;
	int unique_holder_size;
	int two_holders_size;
	int seg_social_size;

	char* single_str;
	char* unique_holder_str;
	char* two_holders_str;
	char* seg_social_str;

	s_arr_irs* single_table;
	s_arr_irs* unique_holder_table;
	s_arr_irs* two_holders_table;
	s_arr_seg_social* seg_social_table;

	/*
	 * IRS: Tabela I - Não Casado
	 * ---------------------------------------------------------------------------------------------------------
	 */
	single_size = 0;
	single_str = h_util_file_read(H_PATH_SINGLE, &single_size);
	single_table = h_irs_alloc(single_size);

	h_irs_parse(single_table, single_str, h_irs_build);

	free(single_str);

	/*
	 * IRS: Tabela II - Casado Unico Titular
	 * ---------------------------------------------------------------------------------------------------------
	 */
	unique_holder_size = 0;
	unique_holder_str = h_util_file_read(H_PATH_UNIQUE_HOLDER, &unique_holder_size);
	unique_holder_table = h_irs_alloc(unique_holder_size);

	h_irs_parse(unique_holder_table, unique_holder_str, h_irs_build);

	free(unique_holder_str);

	/*
	 * IRS: Tabela III - Casado Dois Titulares
	 * ---------------------------------------------------------------------------------------------------------
	 */
	two_holders_size = 0;
	two_holders_str = h_util_file_read(H_PATH_TWO_HOLDERS, &two_holders_size);
	two_holders_table = h_irs_alloc(two_holders_size);

	h_irs_parse(two_holders_table, two_holders_str, h_irs_build);

	free(two_holders_str);

	/*
	 * Segurança Social
	 * ---------------------------------------------------------------------------------------------------------
	 */
	seg_social_size = 0;
	seg_social_str = h_util_file_read(H_PATH_SEG_SOCIAL, &seg_social_size);
	seg_social_table = h_seg_social_alloc(seg_social_size);

	h_seg_social_parse(seg_social_table, seg_social_str);

	free(seg_social_str);

	do
	{
		fprintf(stdout, "%s", H_STRS_MENU);
		fprintf(stdout, GREEN("%s"), H_STRS_PROMPT);
		scanf(" %u", &op);

		switch (op)
		{
		case 1:
			h_menu_irs(single_table, unique_holder_table, two_holders_table);
			break;
		case 2:
			h_menu_seg_social(seg_social_table);
			break;
		case 3:
			h_menu_processing(single_table, unique_holder_table, two_holders_table, seg_social_table);
			break;
		case 9:
			h_irs_write(single_table, H_PATH_SINGLE);
			h_irs_write(unique_holder_table, H_PATH_UNIQUE_HOLDER);
			h_irs_write(two_holders_table, H_PATH_TWO_HOLDERS);
			h_seg_social_write(seg_social_table, H_PATH_SEG_SOCIAL);
			fprintf(stdout, GREEN("[!] Guardado com sucesso\n"));
			break;
		default:
			break;
		}
	} while (op != 0);

	h_irs_free(single_table);
	h_irs_free(unique_holder_table);
	h_irs_free(two_holders_table);
	h_seg_social_free(seg_social_table);
}

int main()
{
	main_menu();

	return 0;
}
