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

void h_irs_build(s_irs* data, char key, char* str, int* dependents)
{
	unsigned long size;

	size = strlen(str) - 1;

	// Catch the values without %, that means we catch the monthly_payment
	if (key != '%')
		data[data->counter].monthly_pay = strtof(str, NULL);

	// Catch all values with % sign
	if (key == '%')
	{
		str[size] = '\0'; // Remove the % sign

		data[data->counter].percentage_per_dependent[*dependents] = strtof(str, NULL) / 100.0f;
		*dependents += 1;
	}
}

int h_irs_parse(s_irs* data, char* str, h_irs_pair_func pair_func)
{
	int dependents;
	int offset_value;
	int i;

	if (data == NULL || str == NULL)
		return -1;

	offset_value = -1;
	dependents = 0;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (offset_value == -1 && isalnum(str[i]))
			offset_value = i;

		if (offset_value != -1 && str[i] == ';')
		{
			str[i] = '\0'; // Remove the ;

			pair_func(data, str[i - 1], str + offset_value, &dependents);

			offset_value = -1;
		}

		// If new line found move to the next struct
		if (str[i] == '\n')
		{
			data->counter++;
			dependents = 0;
		}
	}

	return 0;
}

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

void h_irs_edit(s_irs* data, unsigned int data_len, unsigned int position)
{
	float temp_monthly_pay;
	float temp_dependent;
	int i;

	if (data == NULL || data_len < position)
		return;

	fprintf(stdout, RED("[!] Use pontos para especificar decimas!\n"));
	fprintf(stdout, YELLOW("> Remuneração Mensal => "));
	scanf(" %f", &temp_monthly_pay);
	fprintf(stdout, RED("> %.2f € \n"), temp_monthly_pay);

	if (temp_monthly_pay)
		data[position].monthly_pay = temp_monthly_pay;

	for (i = 0; i < MAX_DEPENDENT_NUMBER; i++)
	{
		fprintf(stdout, YELLOW("> %% para dependente %d =>  "), i);
		scanf(" %f", &temp_dependent);
		fprintf(stdout, RED("> %.3f\n"), temp_dependent);

		if (temp_dependent)
			data[position].percentage_per_dependent[i] = temp_dependent;
	}
}