/* 
 * Created by Micael Dias on 10/12/20.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "irs.h"
#include "colors.h"
#include "strs.h"

/**
 * Alloc n elements into an array of s_irs
 * @param n The size of the array
 * @return s_irs*
 */
s_irs* h_irs_alloc(unsigned int n)
{
	s_irs* irs;
	int i;
	int j;

	if (!n)
		return NULL;

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

	if (data == NULL || str == NULL)
		return;

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
	int i;
	int j;

	if (data == NULL || !size)
		return;

	fprintf(stdout, "%s", H_STRS_IRS_TABLE_HEADER);

	for (i = 0; i < size; i++)
	{
		fprintf(stdout, RED("\n| %d | "), i);
		fprintf(stdout, YELLOW("%.2f€"), data[i].monthly_pay);

		for (j = 0; j < MAX_DEPENDENT_NUMBER; j++)
		{
			fprintf(stdout, BLUE(" | "));
			fprintf(stdout, "%.1f%%", data[i].percentage_per_dependent[j] * 100);
		}
	}
}

/**
 * Edits a single s_irs* struct
 * @param data The s_irs* struct
 */
void h_irs_edit(s_irs* data)
{
	float temp_monthly_pay;
	float temp_dependent;
	int i;

	if (data == NULL)
		return;

	scanf(" %f", &temp_monthly_pay);
	if (temp_monthly_pay)
		data->monthly_pay = temp_monthly_pay;

	for (i = 0; i < MAX_DEPENDENT_NUMBER; i++)
	{
		scanf(" %f", &temp_dependent);
		if (temp_dependent)
			data->percentage_per_dependent[i] = temp_dependent;
	}
}