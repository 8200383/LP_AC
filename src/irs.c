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

void h_irs_build(s_irs* data, char* str, unsigned int line, unsigned int* dependent)
{
	size_t size;
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

s_error* h_irs_parse(s_irs* data, char* str, h_irs_pair_func pair_func)
{
	unsigned int line;
	unsigned int dependent;
	int offset_value;
	int i;

	if (data == NULL || str == NULL)
		return h_error_create(H_ERROR_PARSING, NULL);

	offset_value = -1;
	line = 0;
	dependent = 0;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (offset_value == -1 && isalnum(str[i]))
			offset_value = i;

		if (offset_value != -1 && str[i] == ',')
		{
			str[i] = '\0'; // Remove the ,

			pair_func(data, str + offset_value, line, &dependent);

			offset_value = -1;
		}

		// If new line found move to the next struct
		if (str[i] == '\n')
		{
			line++;
			dependent = 0;
		}
	}

	return NULL;
}

void h_irs_print(s_irs* data, unsigned int size)
{
	int i;

	if (data == NULL || !size)
		fprintf(stderr, RED("[!] Nothing to show\n"));

	fprintf(stdout, "%s", H_STRS_IRS_TABLE_HEADER);
	for (i = 0; i < size; i++)
	{
		fprintf(stdout, RED("\n%d | "), i);

		if (data[i].monthly_pay_type == H_IRS_UP_TO)
			fprintf(stdout, YELLOW("Até "));

		else if (data[i].monthly_pay_type == H_IRS_BEYOND)
			fprintf(stdout, YELLOW("Superior a "));

		fprintf(stdout, YELLOW("%.2f€ | "), data[i].monthly_pay_value);
		fprintf(stdout, CYAN("%.2f%% | "), data[i].dependent_0 * 100);
		fprintf(stdout, CYAN("%.2f%% | "), data[i].dependent_1 * 100);
		fprintf(stdout, CYAN("%.2f%% | "), data[i].dependent_2 * 100);
		fprintf(stdout, CYAN("%.2f%% | "), data[i].dependent_3 * 100);
		fprintf(stdout, CYAN("%.2f%% | "), data[i].dependent_4 * 100);
		fprintf(stdout, CYAN("%.2f%%"), data[i].dependent_5_or_more * 100);
	}
}

void h_irs_edit(s_irs* data, unsigned int size, int position)
{
	char op;

	if (data == NULL || size < position)
		fprintf(stderr, RED("[!] Nothing to edit\n"));

	fprintf(stdout, YELLOW("[A]té ou [S]uperior a\n"));

	scanf(" %c", &op);
	if (op == 'A' || op == 'a')
		data[position].monthly_pay_type = H_IRS_UP_TO;

	else if (op == 'S' || op == 's')
		data[position].monthly_pay_type = H_IRS_BEYOND;

	else
	{
		fprintf(stderr, RED("[!] Opção Invalida"));
		return;
	}

	fprintf(stdout, RED("[!] Use pontos para especificar decimas!\n"));
	fprintf(stdout, YELLOW("> Remuneração Mensal => "));
	data[position].monthly_pay_value = h_util_get_float();

	fprintf(stdout, YELLOW("> Percentagem pelo dependente 0 => "));
	data[position].dependent_0 = h_util_get_float();

	fprintf(stdout, YELLOW("> Percentagem pelo dependente 1 => "));
	data[position].dependent_1 = h_util_get_float();

	fprintf(stdout, YELLOW("> Percentagem pelo dependente 2 => "));
	data[position].dependent_2 = h_util_get_float();

	fprintf(stdout, YELLOW("> Percentagem pelo dependente 3 => "));
	data[position].dependent_3 = h_util_get_float();

	fprintf(stdout, YELLOW("> Percentagem pelo dependente 4 => "));
	data[position].dependent_4 = h_util_get_float();

	fprintf(stdout, YELLOW("> Percentagem pelo dependente 5 ou mais => "));
	data[position].dependent_5_or_more = h_util_get_float();
}

s_error* h_irs_write(s_irs* data, unsigned int size, const char* path)
{
	FILE* fp;
	char* description;
	int i;

	if (data == NULL && size != 0)
		return h_error_create(H_ERROR_UNKNOWN, path);

	fp = fopen(path, "wb");
	if (fp == NULL)
		return h_error_create(H_ERROR_WRITE, path);

	for (i = 0; i < size; i++)
	{
		if (data[i].monthly_pay_type == H_IRS_UP_TO)
			description = "Até";

		else if (data[i].monthly_pay_type == H_IRS_BEYOND)
			description = "Superior a";

		fprintf(
			fp,
			H_STRS_IRS_TEMPLATE_STRING,
			description,
			data[i].monthly_pay_value,
			data[i].dependent_0 * 100,
			data[i].dependent_1 * 100,
			data[i].dependent_2 * 100,
			data[i].dependent_3 * 100,
			data[i].dependent_4 * 100,
			data[i].dependent_5_or_more * 100);
	}

	fclose(fp);

	return NULL;
}