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
	s_table* table;
	int i;
	int j;

	table = malloc(n * sizeof(*table));
	if (table == NULL)
		return NULL;

	for (i = 0; i < n; i++)
	{
		table[i].counter = 0;
		table[i].monthly_pay = 0.0f;

		for (j = 0; j < MAX_DEPENDENT_NUMBER; j++)
		{
			table[i].percentage_per_dependent[j] = 0.0f;
		}
	}

	return table;
}

/**
 * Initialize an array of s_table from str
 * @param table The array of s_table*
 * @param str The array of characters
 */
void h_table_init_from_str(s_table* data, char* str)
{
	int offset_value;
	int i;

	offset_value = -1;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (offset_value == -1 && isalnum(str[i]))
			offset_value = i;

		if (offset_value != -1 && str[i] == ';')
		{
			str[i] = '\0';

			// Catch the values without %, that means we catch the monthly_payment
			if (str[i - 1] != '%')
			{
				data[data->counter].monthly_pay = strtof(str + offset_value, NULL);
				data->counter++;
			}

			offset_value = -1;
		}
	}
}

	}
}