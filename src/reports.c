#include <time.h>

#include "reports.h"
#include "calendar.h"

void h_reports_senior_employees(s_arr_employees* employees_array)
{
	int i;
	int year_now;
	int years_difference;
	struct tm* local_time;

	if (employees_array == NULL || employees_array->used == 0)
	{
		puts(RED("[!] Employees vazio ou não inicializado"));
		return;
	}

	local_time = h_calendar_init_local_time();
	year_now = h_calendar_get_year(local_time);

	printf(YELLOW("Antiguidades dos funcionários\n"));

	for (i = 0; i < employees_array->used; i++)
	{
		years_difference = year_now - employees_array->employees[i].entry_date->year;

		if (years_difference >= EMPLOYEE_SENIORITY &&
			employees_array->employees[i].removed == 0 &&
			employees_array->employees[i].leaving_date->year >= year_now)
		{
			printf(CYAN("%d | %s %s | %d Anos\n"),
				employees_array->employees[i].code,
				employees_array->employees[i].first_name,
				employees_array->employees[i].last_name,
				years_difference);
		}
	}
}

void h_reports_marital_percentage(s_arr_employees* employees_array)
{
	int i = 0;
	int married_employees = 0;
	int single_employees = 0;
	int widowed_employees = 0;
	int divorced_employees = 0;

	if (employees_array == NULL || employees_array->used == 0)
	{
		puts(RED("[!] Employees vazio ou não inicializado"));
		return;
	}

	while (i < employees_array->used && employees_array->employees[i].removed == 0)
	{
		if (employees_array->employees[i].marital_status == MARRIED)
		{
			married_employees++;
		}

		if (employees_array->employees[i].marital_status == SINGLE)
		{
			single_employees++;
		}

		if (employees_array->employees[i].marital_status == WIDOWED)
		{
			widowed_employees++;
		}

		if (employees_array->employees[i].marital_status == DIVORCED)
		{
			divorced_employees++;
		}

		i++;
	}

	puts(CYAN("Percentagem de funcionários"));
	printf("Casados %.2f%%\n", (float)married_employees / (float)i);
	printf("Solteiros %.2f%%\n", (float)single_employees / (float)i);
	printf("Viúvos %.2f%%\n", (float)widowed_employees / (float)i);
	printf("Divorciados %.2f%%\n", (float)divorced_employees / (float)i);
}
