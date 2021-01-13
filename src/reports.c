#include <time.h>

#include "reports.h"
#include "calendar.h"

void h_reports_senior_employees(s_arr_employees* employees_array)
{
	int i;
	int year_now;
	int years_difference;
	int senior_employees = 0;
	int total_employees = 0;
	struct tm* local_time;

	if (employees_array->used == 0)
	{
		puts(RED("[!] Employees vazio ou não inicializado"));
		return;
	}

	local_time = h_calendar_init_local_time();
	year_now = h_calendar_get_year(local_time);

	printf(YELLOW("Antiguidade dos funcionários\n"));
	for (i = 0; i < employees_array->used; i++)
	{
		years_difference = year_now - employees_array->employees[i].entry_date->year;

		if (employees_array->employees[i].removed == 0 &&
			employees_array->employees[i].leaving_date->year >= year_now)
		{
			total_employees++;
		}

		if (years_difference >= EMPLOYEE_SENIORITY &&
			employees_array->employees[i].removed == 0 &&
			employees_array->employees[i].leaving_date->year >= year_now)
		{
			senior_employees++;
			printf(
					CYAN("%d | %s %s | %d Anos\n"),
					employees_array->employees[i].cod_employee,
					employees_array->employees[i].first_name,
					employees_array->employees[i].last_name,
					years_difference);
		}
	}

	printf("Porcentagem: %.2f%%\n", (float)senior_employees / (float)total_employees);
}

void h_reports_marital_status(s_arr_employees* employees_array)
{
	int i = 0;
	int married_employees = 0;
	int single_employees = 0;
	int widowed_employees = 0;
	int divorced_employees = 0;

	if (employees_array->used == 0)
	{
		puts(RED("[!] Nenhum funcionário encontrado"));
		return;
	}

	puts(CYAN("Relatório estado civil dos funcionários"));

	while (i < employees_array->used && employees_array->employees[i].removed == 0)
	{
		if (employees_array->employees[i].marital_status == MARRIED)
		{
			printf(
					YELLOW("[%d] %s %s | Estado Civil Atual: %s\n"),
					employees_array->employees[i].cod_employee,
					employees_array->employees[i].first_name,
					employees_array->employees[i].last_name,
					h_employees_str_from_marital_status(employees_array->employees[i].marital_status, 1)
			);

			married_employees++;
		}

		if (employees_array->employees[i].marital_status == SINGLE)
		{
			printf(
					YELLOW("[%d] %s %s | Estado Civil Atual: %s\n"),
					employees_array->employees[i].cod_employee,
					employees_array->employees[i].first_name,
					employees_array->employees[i].last_name,
					h_employees_str_from_marital_status(employees_array->employees[i].marital_status, 1)
			);

			single_employees++;
		}

		if (employees_array->employees[i].marital_status == WIDOWED)
		{
			printf(
					YELLOW("[%d] %s %s | Estado Civil Atual: %s\n"),
					employees_array->employees[i].cod_employee,
					employees_array->employees[i].first_name,
					employees_array->employees[i].last_name,
					h_employees_str_from_marital_status(employees_array->employees[i].marital_status, 1)
			);

			widowed_employees++;
		}

		if (employees_array->employees[i].marital_status == DIVORCED)
		{
			printf(
					YELLOW("[%d] %s %s | Estado Civil Atual: %s\n"),
					employees_array->employees[i].cod_employee,
					employees_array->employees[i].first_name,
					employees_array->employees[i].last_name,
					h_employees_str_from_marital_status(employees_array->employees[i].marital_status, 1)
			);

			divorced_employees++;
		}

		i++;
	}

	printf("Casados %.2f%%\n", (float)married_employees / (float)i);
	printf("Solteiros %.2f%%\n", (float)single_employees / (float)i);
	printf("Viúvos %.2f%%\n", (float)widowed_employees / (float)i);
	printf("Divorciados %.2f%%\n", (float)divorced_employees / (float)i);
}

void h_reports_bonus(s_spreadsheet* spreadsheet, s_arr_employees* employees_array)
{
	int i;
	int j, k;
	int l, m;
	int x, y;

	int* employees_base_bonus;
	int base_bonus_counter = 0;

	int* employees_seventeen_days_bonus;
	int seventeen_days_bonus_counter = 0;

	int* employees_twenty_days_bonus;
	int twenty_days_bonus_counter = 0;

	if (spreadsheet->used == 0 || employees_array->used == 0)
	{
		puts(H_STRS_EMPLOYEES_NOT_FOUND);
		return;
	}
	else if (spreadsheet->month_is_set == 0)
	{
		puts(H_STRS_MONTH_NOT_CREATED);
		return;
	}
	else if (spreadsheet->is_processed == 0)
	{
		puts(RED("[!] Nenhum mês foi ainda processado"));
		return;
	}

	employees_base_bonus = malloc(employees_array->used * sizeof(int));
	if (employees_base_bonus == NULL)
	{
		puts(H_STRS_MALLOC_FAILED);
		return;
	}

	employees_seventeen_days_bonus = malloc(employees_array->used * sizeof(int));
	if (employees_seventeen_days_bonus == NULL)
	{
		free(employees_base_bonus);
		puts(H_STRS_MALLOC_FAILED);
		return;
	}

	employees_twenty_days_bonus = malloc(employees_array->used * sizeof(int));
	if (employees_twenty_days_bonus == NULL)
	{
		free(employees_base_bonus);
		free(employees_seventeen_days_bonus);
		puts(H_STRS_MALLOC_FAILED);
		return;
	}

	for (i = 0; i < spreadsheet->used; i++)
	{
		if (spreadsheet->details[i].bonus == BASE_BONUS)
		{
			employees_base_bonus[base_bonus_counter] = spreadsheet->details[i].cod_employee;
			base_bonus_counter++;
		}

		if (spreadsheet->details[i].bonus == BONUS_17_DAYS)
		{
			employees_seventeen_days_bonus[seventeen_days_bonus_counter] = spreadsheet->details[i].cod_employee;
			seventeen_days_bonus_counter++;
		}

		if (spreadsheet->details[i].bonus == BONUS_20_DAYS)
		{
			employees_twenty_days_bonus[twenty_days_bonus_counter] = spreadsheet->details[i].cod_employee;
			twenty_days_bonus_counter++;
		}
	}

	printf(YELLOW("** Relatório de bónus do mês %s           **\n"), h_calendar_str_from_month(spreadsheet->month));
	printf(YELLOW("* Total funcionários processados -> %d       *\n"), i);
	printf(YELLOW("* Total funcionários com bonus base -> %d    *\n"), base_bonus_counter);
	printf(YELLOW("* Total funcionários com bonus 17 dias -> %d *\n"), seventeen_days_bonus_counter);
	printf(YELLOW("* Total funcionários com bonus 20 dias -> %d *\n"), twenty_days_bonus_counter);
	printf(YELLOW("**********************************************\n"));

	for (j = 0; j < base_bonus_counter; j++)
	{
		for (k = 0; k < employees_array->used; k++)
		{
			if (employees_base_bonus[j] == employees_array->employees[i].cod_employee)
			{
				printf(GREEN("[Bónus Base] "));
				printf(
						CYAN("[%d] %s %s\n"),
						employees_array->employees[i].cod_employee,
						employees_array->employees[i].first_name,
						employees_array->employees[i].last_name);
			}
		}
	}

	if (base_bonus_counter != 0)
	{
		printf(CYAN("Porcentagem bónus base -> %.2f%%\n"), (float)base_bonus_counter / (float)i);
	}

	for (l = 0; l < seventeen_days_bonus_counter; l++)
	{
		for (m = 0; m < employees_array->used; m++)
		{
			if (employees_seventeen_days_bonus[l] == employees_array->employees[m].cod_employee)
			{
				printf(GREEN("[Bónus 17 dias] "));
				printf(
						CYAN("[%d] %s %s\n"),
						employees_array->employees[m].cod_employee,
						employees_array->employees[m].first_name,
						employees_array->employees[m].last_name);
			}
		}
	}

	if (seventeen_days_bonus_counter != 0)
	{
		printf(CYAN("Porcentagem bónus 17 dias -> %.2f%%\n"), (float)seventeen_days_bonus_counter / (float)i);
	}

	for (x = 0; x < twenty_days_bonus_counter; x++)
	{
		for (y = 0; y < employees_array->used; y++)
		{
			if (employees_twenty_days_bonus[x] == employees_array->employees[y].cod_employee)
			{
				printf(GREEN("[Bónus 20 dias] "));
				printf(
						CYAN("[Bónus 20 dias] [%d] %s %s\n"),
						employees_array->employees[y].cod_employee,
						employees_array->employees[y].first_name,
						employees_array->employees[y].last_name);
			}
		}
	}

	if (twenty_days_bonus_counter != 0)
	{
		printf(CYAN("Porcentagem bónus 20 dias -> %.2f%%\n"), (float)twenty_days_bonus_counter / (float)i);
	}

	free(employees_base_bonus);
	free(employees_seventeen_days_bonus);
	free(employees_twenty_days_bonus);
}