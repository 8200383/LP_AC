/* 
 * Created by Micael Dias on 10/12/20.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "table.h"

/**
 * Alloc n elements into an array of s_table
 * @param n The size of the array
 * @return s_table*
 */
s_table* h_table_alloc(int n)
{
	s_table* table = malloc(n * sizeof(*table));
	if (table == NULL)
		return NULL;

	table->monthly_pay = 0.0f;

	table->percentage_per_dependent = malloc(MAX_DEPENDENT_NUMBER * sizeof(float));
	if (table->percentage_per_dependent == NULL)
	{
		free(table);
		return NULL;
	}

	int i = 0;
	while (i < MAX_DEPENDENT_NUMBER)
	{
		table->percentage_per_dependent[i] = 0.0f;
		i++;
	}

	return table;
}

/**
 * Initialize an array of s_table from str
 * @param table The array of s_table*
 * @param str The array of characters
 */
void h_table_init_from_str(s_table* table, char* str)
{
	int offset_value = -1;

	for (int i = 0; str[i] != '\0'; i++)
	{
		char c = str[i];

		if (offset_value == -1 && isalnum(c))
			offset_value = i;

		if (offset_value != -1 && c == ';')
		{
			str[i] = '\0';

			fprintf(stdout, "%s\n", str + offset_value);

			offset_value = -1;
		}

	}
}