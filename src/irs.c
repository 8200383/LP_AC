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
#include "util.h"

s_irs* h_irs_alloc(unsigned int n)
{
	s_irs* irs;
	int i;

	if (!n)
		return NULL;

	irs = malloc(n * sizeof(*irs));
	if (irs == NULL)
		return NULL;

	for (i = 0; i < n; i++)
	{
		irs[i].monthly_pay_type = H_IRS_UP_TO;
		irs[i].monthly_pay_value = 0.0f;
		irs[i].dependent_0 = 0.0f;
		irs[i].dependent_1 = 0.0f;
		irs[i].dependent_2 = 0.0f;
		irs[i].dependent_3 = 0.0f;
		irs[i].dependent_4 = 0.0f;
		irs[i].dependent_5_or_more = 0.0f;
	}

	return irs;
}

void h_irs_build(s_irs* data, char key, char* str, int line, int* dependent)
{
	unsigned long size;
	float percentage;

	size = strlen(str) - 1;

	if (m_util_strequal(str, "Até"))
		data[line].monthly_pay_type = H_IRS_UP_TO;

	else if (m_util_strequal(str, "Superior a"))
		data[line].monthly_pay_type = H_IRS_BEYOND;

	if (m_util_regexcmp(str, "EUR"))
	{
		str[size - 2] = '\0';
		data[line].monthly_pay_value = strtof(str, NULL);
		str[size - 2] = 'E';
	}

	if (m_util_regexcmp(str, "%"))
	{
		str[size] = '\0';

		percentage = strtof(str, NULL) / 100.0f;

		if (*dependent == 0)
			data[line].dependent_0 = percentage;
		else if (*dependent == 1)
			data[line].dependent_1 = percentage;
		else if (*dependent == 2)
			data[line].dependent_2 = percentage;
		else if (*dependent == 3)
			data[line].dependent_3 = percentage;
		else if (*dependent == 4)
			data[line].dependent_4 = percentage;
		else if (*dependent == 5)
			data[line].dependent_5_or_more = percentage;

		*dependent += 1;

		str[size] = '%';
	}
}

int h_irs_parse(s_irs* data, char* str, h_irs_pair_func pair_func)
{
	int line;
	int dependent;
	int offset_value;
	int i;

	if (data == NULL || str == NULL)
		return -1;

	offset_value = -1;
	line = 0;
	dependent = 0;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (offset_value == -1 && isalnum(str[i]))
			offset_value = i;

		if (offset_value != -1 && str[i] == ';')
		{
			str[i] = '\0'; // Remove the ;

			pair_func(data, str[i - 1], str + offset_value, line, &dependent);

			offset_value = -1;
		}

		// If new line found move to the next struct
		if (str[i] == '\n')
		{
			line++;
			dependent = 0;
		}
	}

	return 0;
}

void h_irs_print(s_irs* data, int size)
{
	int i;

	if (data == NULL || !size)
		return;

	fprintf(stdout, "%s", H_STRS_IRS_TABLE_HEADER);
	for (i = 0; i < size; i++)
	{
		fprintf(stdout, RED("\n%d | "), i);

		if (data[i].monthly_pay_type == H_IRS_UP_TO)
			fprintf(stdout, YELLOW("Até "));

		else if (data[i].monthly_pay_type == H_IRS_BEYOND)
			fprintf(stdout, YELLOW("Superior a "));

		fprintf(stdout, YELLOW("%.2f€ | "), data[i].monthly_pay_value);
		fprintf(stdout, CYAN("%.1f%% | "), data[i].dependent_0);
		fprintf(stdout, CYAN("%.1f%% | "), data[i].dependent_1);
		fprintf(stdout, CYAN("%.1f%% | "), data[i].dependent_2);
		fprintf(stdout, CYAN("%.1f%% | "), data[i].dependent_3);
		fprintf(stdout, CYAN("%.1f%% | "), data[i].dependent_4);
		fprintf(stdout, CYAN("%.1f%%"), data[i].dependent_5_or_more);
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
} */

int h_irs_free(s_irs* data)
{
	if (data == NULL)
		return -1;

	data->monthly_pay_type = H_IRS_UP_TO;
	data->monthly_pay_value = 0.0f;
	data->dependent_0 = 0.0f;
	data->dependent_1 = 0.0f;
	data->dependent_2 = 0.0f;
	data->dependent_3 = 0.0f;
	data->dependent_4 = 0.0f;
	data->dependent_5_or_more = 0.0f;

	return 0;
}