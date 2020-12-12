/* 
 * Created by Micael Dias on 10/12/20.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "irs.h"

/**
 * Alloc n elements into an array of s_irs
 * @param n The size of the array
 * @return s_irs*
 */
s_irs* h_irs_alloc(int n)
{
	s_irs* irs;
	int i;
	int j;

	irs = malloc(n * sizeof(*irs));
	if (irs == NULL)
		return NULL;

	for (i = 0; i < n; i++)
	{
		irs[i].monthly_pay = 0.0f;
		irs[i].counter = 0;

		for (j = 0; j < MAX_DEPENDENT_NUMBER; j++)
		{
			irs[i].percentage_per_dependent[j] = 0.0f;
		}
	}

	return irs;
}

/**
 * Initialize an array of s_irs from str
 * @param data The array of s_irs*
 * @param str The array of characters
 */
void h_irs_init_from_str(s_irs* data, char* str)
{
	int dependents_counter;
	int offset_value;
	int i;

	offset_value = -1;
	dependents_counter = 0;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (offset_value == -1 && isalnum(str[i]))
			offset_value = i;

		if (offset_value != -1 && str[i] == ';')
		{
			str[i] = '\0'; // Remove the ;

			// Catch the values without %, that means we catch the monthly_payment
			if (str[i - 1] != '%')
				data[data->counter].monthly_pay = strtof(str + offset_value, NULL);

			// Catch all values with % sign
			if (str[i - 1] == '%')
			{
				str[i - 1] = '\0'; // Remove the % sign

				data[data->counter].percentage_per_dependent[dependents_counter++] =
					strtof(str + offset_value, NULL) / 100.0f;
			}

			offset_value = -1;
		}

		// If new line found move to the next struct
		if (str[i] == '\n')
		{
			data->counter++;
			dependents_counter = 0;
		}
	}
}

/**
 * Print an array of s_irs*
 * @param data The array
 * @param size The size of the array
 */
void h_irs_print(s_irs* data, int size)
{
	for (int i = 0; i < size; i++)
	{
		fprintf(stdout, "\n%.2f€\n", data[i].monthly_pay);

		fprintf(stdout, "1 dependent %f\n", data[i].percentage_per_dependent[0]);
		fprintf(stdout, "2 dependent %f\n", data[i].percentage_per_dependent[1]);
		fprintf(stdout, "3 dependent %f\n", data[i].percentage_per_dependent[2]);
		fprintf(stdout, "4 dependent %f\n", data[i].percentage_per_dependent[3]);
		fprintf(stdout, "5 dependent %f\n", data[i].percentage_per_dependent[4]);
	}
}